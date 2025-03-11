package com.example.practic_vacante.controller;

import com.example.practic_vacante.domain.*;
import com.example.practic_vacante.service.HotelService;
import com.example.practic_vacante.service.ReservationService;
import com.example.practic_vacante.service.SpecialOfferService;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDate;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientController {

    @FXML
    private ComboBox<String> locationComboBox;

    @FXML
    private DatePicker startDatePicker;

    @FXML
    private DatePicker endDatePicker;

    @FXML
    private Button searchHotelsButton;

    @FXML
    private TableView<HotelOccupancyDTO> hotelsTable;

    @FXML
    private TableColumn<HotelOccupancyDTO, String> hotelNameColumn;

    @FXML
    private TableColumn<HotelOccupancyDTO, Double> occupancyRateColumn;

    @FXML
    private TableColumn<HotelOccupancyDTO, Double> pricePerNightColumn;

    @FXML
    private Button bookButton;

    @FXML
    private Label usersWatchingLabel;


    private HotelService hotelService;
    private ReservationService reservationService;
    private SpecialOfferService specialOfferService;
    private Client currentClient;

    public void setClient(Client client, HotelService hotelService, ReservationService reservationService, SpecialOfferService specialOfferService) {
        this.currentClient = client;
        this.hotelService = hotelService;
        this.reservationService = reservationService;
        this.specialOfferService = specialOfferService;

        if (this.hotelService != null) {
            loadTableColumns(); // Configurăm coloanele tabelului
            loadLocations(); // Încărcăm locațiile disponibile
        }

        // Adăugăm un observer pentru a detecta când alți utilizatori caută aceleași filtre
        specialOfferService.addObserver(event -> updateUsersWatching());
    }


    private void loadTableColumns() {
        hotelNameColumn.setCellValueFactory(new PropertyValueFactory<>("hotelName"));
        occupancyRateColumn.setCellValueFactory(new PropertyValueFactory<>("occupancyRate"));
        pricePerNightColumn.setCellValueFactory(new PropertyValueFactory<>("pricePerNight"));

        searchHotelsButton.setOnAction(event -> searchHotels());
        bookButton.setOnAction(event -> bookHotel());
    }


    private void loadLocations() {
        if (hotelService == null) {
            showAlert("Error", "Hotel service is not initialized.");
            return;
        }

        List<String> locations = hotelService.getAllLocations();
        locationComboBox.setItems(FXCollections.observableArrayList(locations));
    }

    private void searchHotels() {
        String selectedLocation = locationComboBox.getValue();
        LocalDate startDate = startDatePicker.getValue();
        LocalDate endDate = endDatePicker.getValue();

        if (selectedLocation == null || startDate == null || endDate == null) {
            showAlert("Error", "Please select a location and a valid date range.");
            return;
        }

        if (currentClient == null) {
            showAlert("Error", "Client details not available.");
            return;
        }

        // Înregistrăm noua căutare
        specialOfferService.recordSearch(selectedLocation, startDate, endDate);

        // Apelăm metoda getHotelsWithOccupancy pentru a obține rezultatele
        List<HotelOccupancyDTO> results = getHotelsWithOccupancy(selectedLocation, startDate, endDate);

        // Populăm tabelul cu rezultatele
        hotelsTable.setItems(FXCollections.observableArrayList(results));

        // Actualizăm numărul utilizatorilor care caută aceleași filtre
        updateUsersWatching();
    }



    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private List<HotelOccupancyDTO> getHotelsWithOccupancy(String location, LocalDate startDate, LocalDate endDate) {
        List<Hotel> hotels = StreamSupport.stream(hotelService.getAllHotels().spliterator(), false)
                .filter(hotel -> hotel.getLocationName().equals(location)) // Filtrăm hotelurile după locație
                .filter(hotel -> {
                    // Verificăm dacă există o ofertă valabilă pentru acest hotel
                    return getSpecialOffersForHotel(hotel.getId()).stream()
                            .anyMatch(offer ->
                                    currentClient.getFidelityGrade() > offer.getPercents() && // FidelityGrade > percents
                                            endDate.isBefore(offer.getEndDate().plusDays(1))); // EndDate <= oferta's EndDate
                })
                .toList();

        return hotels.stream()
                .map(hotel -> {
                    double occupancyRate = calculateOccupancyRate(hotel, startDate, endDate); // Calculăm gradul de ocupare
                    return new HotelOccupancyDTO(hotel.getHotelName(), occupancyRate, hotel.getPricePerNight());
                })
                .collect(Collectors.toList());
    }


    public List<SpecialOffer> getSpecialOffersForHotel(Double hotelId) {
        return StreamSupport.stream(specialOfferService.getAllSpecialOffers().spliterator(), false)
                .filter(offer -> offer.getHotelId().equals(hotelId))
                .toList();
    }

    private double calculateOccupancyRate(Hotel hotel, LocalDate startDate, LocalDate endDate) {
        int totalRooms = hotel.getNoRooms(); // Total camere din hotel
        int totalOccupiedNights = 0; // Total nopți ocupate în perioada selectată

        for (Reservation reservation : reservationService.getAllReservations()) {
            // Verificăm dacă rezervarea aparține hotelului curent și suprapune perioada selectată
            if (reservation.getHotelId().equals(hotel.getId()) &&
                    (reservation.getStartDate().toLocalDate().isBefore(endDate) &&
                            reservation.getStartDate().toLocalDate().plusDays(reservation.getNoNights()).isAfter(startDate))) {
                // Calculăm nopțile ocupate care se suprapun cu perioada selectată
                LocalDate reservationStart = reservation.getStartDate().toLocalDate();
                LocalDate reservationEnd = reservationStart.plusDays(reservation.getNoNights());

                LocalDate overlapStart = reservationStart.isAfter(startDate) ? reservationStart : startDate;
                LocalDate overlapEnd = reservationEnd.isBefore(endDate) ? reservationEnd : endDate;

                long overlapDays = overlapStart.until(overlapEnd).getDays();
                totalOccupiedNights += overlapDays;
            }
        }

        // Calculăm numărul total de nopți disponibile în hotel
        long totalAvailableNights = startDate.until(endDate).getDays() * totalRooms;

        if (totalAvailableNights == 0) return 0.0; // Evităm împărțirea la 0

        // Calculăm gradul de ocupare
        return (double) totalOccupiedNights / totalAvailableNights;
    }

    private void bookHotel() {
        HotelOccupancyDTO selectedHotel = hotelsTable.getSelectionModel().getSelectedItem();

        if (selectedHotel == null) {
            showAlert("Error", "Please select a hotel from the list.");
            return;
        }

        LocalDate startDate = startDatePicker.getValue();
        LocalDate endDate = endDatePicker.getValue();

        if (startDate == null || endDate == null) {
            showAlert("Error", "Please select a valid period.");
            return;
        }

        if (startDate.isAfter(endDate)) {
            showAlert("Error", "Start date cannot be after end date.");
            return;
        }

        // Verificăm dacă clientul este setat
        if (currentClient == null) {
            showAlert("Error", "No authenticated client found.");
            return;
        }

        // Creăm rezervarea și o adăugăm în baza de date
        Reservation reservation = new Reservation(
                generateReservationId(), // Generăm un ID unic pentru rezervare
                currentClient.getId(),
                getHotelIdByName(selectedHotel.getHotelName()), // Obținem ID-ul hotelului
                startDate.atStartOfDay(),
                (int) (startDate.until(endDate).getDays())
        );

        reservationService.addReservation(reservation);

        showAlert(Alert.AlertType.INFORMATION, "Success", "Reservation successfully created!");
    }

    private Double getHotelIdByName(String hotelName) {
        return StreamSupport.stream(hotelService.getAllHotels().spliterator(), false)
                .filter(hotel -> hotel.getHotelName().equals(hotelName))
                .findFirst()
                .map(Hotel::getId)
                .orElse(null);
    }


    private Double generateReservationId() {
        return Math.random() * 10000; // ID unic random
    }

    private void showAlert(Alert.AlertType alertType, String title, String message) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }



    private void updateUsersWatching() {
        if (currentClient == null) return;

        String selectedLocation = locationComboBox.getValue();
        LocalDate startDate = startDatePicker.getValue();
        LocalDate endDate = endDatePicker.getValue();

        if (selectedLocation == null || startDate == null || endDate == null) {
            usersWatchingLabel.setText("0 other user(s) are looking at the same location.");
            return;
        }

        // Obținem numărul de utilizatori care caută aceleași filtre
        long usersWatching = specialOfferService.getMatchingUsers(selectedLocation, startDate, endDate);

        usersWatchingLabel.setText(usersWatching + " other user(s) are looking at the same location.");
    }



}
