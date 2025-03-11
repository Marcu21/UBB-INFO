package com.example.practic_zboruri.controller;

import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.domain.Flight;
import com.example.practic_zboruri.domain.Ticket;
import com.example.practic_zboruri.service.ClientService;
import com.example.practic_zboruri.service.FlightService;
import com.example.practic_zboruri.service.TicketService;
import com.example.practic_zboruri.utils.Observer;
import com.example.practic_zboruri.utils.events.FlightChangeEventType;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class ClientController implements Observer<FlightChangeEventType> {
    private ClientService clientService;
    private FlightService flightService;
    private TicketService ticketService;
    private Client user;

    @FXML
    private Label loggedUserLabel;

    @FXML
    private TableView<Ticket> userTicketsTable;

    @FXML
    private TableColumn<Ticket, String> userTicketsUsernameColumn;

    @FXML
    private TableColumn<Ticket, Long> userTicketsFlightIdColumn;

    @FXML
    private TableColumn<Ticket, LocalDateTime> userTicketsPurchaseTimeColumn;

    @FXML
    private TableView<Ticket> allSoldTicketsTable;

    @FXML
    private TableColumn<Ticket, String> allSoldTicketsUsernameColumn;

    @FXML
    private TableColumn<Ticket, Long> allSoldTicketsFlightIdColumn;

    @FXML
    private TableColumn<Ticket, LocalDateTime> allSoldTicketsPurchaseTimeColumn;


    @FXML
    private ComboBox<String> fromLocationComboBox;

    @FXML
    private ComboBox<String> toLocationComboBox;

    @FXML
    private DatePicker departureDatePicker;

    @FXML
    private Button filterFlightsButton;

    @FXML
    private TableView<Flight> filteredFlightsTable;

    @FXML
    private TableColumn<Flight, String> filteredFlightsFromColumn;

    @FXML
    private TableColumn<Flight, String> filteredFlightsToColumn;

    @FXML
    private TableColumn<Flight, LocalDateTime> filteredFlightsDepartureColumn;

    @FXML
    private TableColumn<Flight, LocalDateTime> filteredFlightsLandingColumn;

    @FXML
    private TableColumn<Flight, Integer> filteredFlightsSeatsColumn;

    public void setClientService(Client user, ClientService clientService, FlightService flightService, TicketService ticketService) {
        this.user = user;
        this.clientService = clientService;
        this.flightService = flightService;
        this.ticketService = ticketService;
        this.flightService.addObserver(this);

        initializeUserDetails();
        loadUserTickets();
        loadAllSoldTickets();
        loadFlights();
        loadFromLocations();
        loadToLocations();
    }

    public void loadToLocations() {
        List<String> toLocations = flightService.getToLocations();
        toLocationComboBox.getItems().clear();
        toLocationComboBox.getItems().addAll(toLocations);
    }

    public void loadFromLocations() {
        List<String> fromLocations = flightService.getFromLocations();
        fromLocationComboBox.getItems().clear();
        fromLocationComboBox.getItems().addAll(fromLocations);
    }


    private void initializeUserDetails() {
        if (user != null) {
            loggedUserLabel.setText("Utilizator logat: " + user.getUsername());
        }
    }


    private void loadUserTickets() {
        userTicketsUsernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        userTicketsFlightIdColumn.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        userTicketsPurchaseTimeColumn.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));

        List<Ticket> userTickets = ticketService.getTicketsByUsername(user.getUsername());

        userTicketsTable.getItems().clear();
        userTicketsTable.getItems().addAll(userTickets);
    }


    private void loadAllSoldTickets() {
        allSoldTicketsUsernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        allSoldTicketsFlightIdColumn.setCellValueFactory(new PropertyValueFactory<>("flightId"));
        allSoldTicketsPurchaseTimeColumn.setCellValueFactory(new PropertyValueFactory<>("purchaseTime"));

        LocalDate targetDate = LocalDate.of(2024, 1, 24);
        List<Ticket> soldTicketsOnDate = ticketService.getTicketsByDate(targetDate);

        allSoldTicketsTable.getItems().clear();
        allSoldTicketsTable.getItems().addAll(soldTicketsOnDate);
    }


    private void loadFlights() {
        filteredFlightsFromColumn.setCellValueFactory(new PropertyValueFactory<>("from"));
        filteredFlightsToColumn.setCellValueFactory(new PropertyValueFactory<>("to"));
        filteredFlightsDepartureColumn.setCellValueFactory(new PropertyValueFactory<>("departureTime"));
        filteredFlightsLandingColumn.setCellValueFactory(new PropertyValueFactory<>("landingTime"));
        filteredFlightsSeatsColumn.setCellValueFactory(new PropertyValueFactory<>("seats"));

        filterFlightsButton.setOnAction(event -> filterFlights());
    }

    private void filterFlights() {
        String fromLocation = fromLocationComboBox.getValue();
        String toLocation = toLocationComboBox.getValue();
        LocalDate departureDate = departureDatePicker.getValue();

        List<Flight> filteredFlights = flightService.getFlightsByFilter(fromLocation, toLocation, departureDate);

        filteredFlightsTable.getItems().clear();
        filteredFlightsTable.getItems().addAll(filteredFlights);
    }

    public void handleCumpara()
    {
        if(filteredFlightsTable.getSelectionModel().getSelectedItem() != null)
        {
            if(filteredFlightsTable.getSelectionModel().getSelectedItem().getSeats() > 0)
            {
                Ticket ticket = new Ticket();
                ticket.setId(System.currentTimeMillis());
                ticket.setUsername(user.getUsername());
                ticket.setFlightId(filteredFlightsTable.getSelectionModel().getSelectedItem().getId());
                ticket.setPurchaseTime(LocalDateTime.now());
                ticketService.addTicket(ticket);
                Flight flight = filteredFlightsTable.getSelectionModel().getSelectedItem();
                flight.setSeats(flight.getSeats() - 1);
                flightService.updateFlight(flight);
                loadUserTickets();
                loadAllSoldTickets();
                loadFlights();
            }
            else
            {
                showAlert("Eroare", "Nu mai sunt locuri disponibile pentru acest zbor!");
            }
        }
        else
        {
            showAlert("Eroare", "Selectati un zbor pentru a cumpara un bilet!");
        }
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void updateTables() {
        loadUserTickets();
        loadAllSoldTickets();
        loadFlights();
    }

    @Override
    public void update(FlightChangeEventType event) {
        switch (event.getType()) {
            case UPDATE:
                updateFlightInTable(event.getData());
                break;
            default:
                updateTables();
        }
    }

    private void updateFlightInTable(Flight updatedFlight) {
        for (Flight flight : filteredFlightsTable.getItems()) {
            if (flight.getId().equals(updatedFlight.getId())) {
                flight.setSeats(updatedFlight.getSeats());
                filteredFlightsTable.refresh();
                break;
            }
        }
    }


}