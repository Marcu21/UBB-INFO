package com.example.practic_vacante;

import com.example.practic_vacante.controller.ClientController;
import com.example.practic_vacante.domain.Client;
import com.example.practic_vacante.domain.Hobbies;
import com.example.practic_vacante.domain.Hotel;
import com.example.practic_vacante.domain.SpecialOffer;
import com.example.practic_vacante.domain.validators.ClientValidator;
import com.example.practic_vacante.domain.validators.HotelValidator;
import com.example.practic_vacante.domain.validators.ReservationValidator;
import com.example.practic_vacante.domain.validators.SpecialOfferValidator;
import com.example.practic_vacante.repository.ClientDbRepository;
import com.example.practic_vacante.repository.HotelDbRepository;
import com.example.practic_vacante.repository.ReservationDbRepository;
import com.example.practic_vacante.repository.SpecialOfferDbRepository;
import com.example.practic_vacante.service.ClientService;
import com.example.practic_vacante.service.HotelService;
import com.example.practic_vacante.service.ReservationService;
import com.example.practic_vacante.service.SpecialOfferService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

public class HelloApplication extends Application {
    private static Map<Long, String> clientsFromArgs = new HashMap<>();
    private static ClientService clientService;
    private static SpecialOfferService specialOfferService;
    private static HotelService hotelService;
    private static ReservationService reservationService;

    @Override
    public void start(Stage primaryStage) throws IOException {
        for (Map.Entry<Long, String> entry : clientsFromArgs.entrySet()) {
            Long clientId = entry.getKey();
            Client client = clientService.getClient(clientId); // Obținem obiectul Client

            if (client != null) {
                openClientWindow(client); // Trimitem obiectul Client, nu doar ID-ul și numele
            }
        }
    }

    public static void main(String[] args) {
        String dbUrl = "jdbc:postgresql://localhost:5432/vacante";
        String dbUsername = "postgres";
        String dbPassword = "skerdix";

        ClientDbRepository clientRepo = new ClientDbRepository(dbUrl, dbUsername, dbPassword, new ClientValidator());

        SpecialOfferDbRepository specialOfferRepo = new SpecialOfferDbRepository(dbUrl, dbUsername, dbPassword, new SpecialOfferValidator());

        HotelDbRepository hotelRepo = new HotelDbRepository(dbUrl, dbUsername, dbPassword, new HotelValidator());

        ReservationDbRepository reservationRepo = new ReservationDbRepository(dbUrl, dbUsername, dbPassword, new ReservationValidator());

        clientService = new ClientService(clientRepo);

        specialOfferService = new SpecialOfferService(specialOfferRepo);

        hotelService = new HotelService(hotelRepo);

        reservationService = new ReservationService(reservationRepo);

        //insertClients();

        //insertSpecialOffers();

        //insertHotels();

        for (String arg : args) {
            if (arg.startsWith("client:")) {
                String[] parts = arg.split(":");
                Long clientId = Long.valueOf(parts[1]);
                Client client = clientService.getClient(clientId);
                if (client != null) {
                    clientsFromArgs.put(clientId, client.getName());
                }
            }
        }

        launch(args);
    }

    private static void insertHotels() {
        Hotel hotel1 = new Hotel(1.0, "Paris", "Eiffel Hotel", 100, 200.0);
        Hotel hotel2 = new Hotel(2.0, "Rome", "Colosseum Suites", 50, 150.0);
        Hotel hotel3 = new Hotel(3.0, "New York", "Central Park Inn", 80, 300.0);

        hotelService.addHotel(hotel1);
        hotelService.addHotel(hotel2);
        hotelService.addHotel(hotel3);

        System.out.println("Hotelurile au fost inserate cu succes în baza de date!");
    }

    private static void insertSpecialOffers() {
        SpecialOffer offer1 = new SpecialOffer(1.0, 1.0, LocalDate.now().plusDays(1), LocalDate.now().plusDays(10), 80);
        SpecialOffer offer2 = new SpecialOffer(2.0, 2.0, LocalDate.now().plusDays(5), LocalDate.now().plusDays(15), 70);
        SpecialOffer offer3 = new SpecialOffer(3.0, 3.0, LocalDate.now().minusDays(5), LocalDate.now().plusDays(20), 90);
        SpecialOffer offer4 = new SpecialOffer(4.0, 2.0, LocalDate.now().plusDays(3), LocalDate.now().plusDays(12), 50);

        specialOfferService.addSpecialOffer(offer1);
        specialOfferService.addSpecialOffer(offer2);
        specialOfferService.addSpecialOffer(offer3);
        specialOfferService.addSpecialOffer(offer4);

        System.out.println("Ofertele speciale au fost inserate cu succes în baza de date!");
    }

    private static void insertClients() {
        Client client1 = new Client(1L, "John Doe", 85, 30, Hobbies.READING);
        Client client2 = new Client(2L, "Jane Smith", 90, 25, Hobbies.MUSIC);
        Client client3 = new Client(3L, "Alice Johnson", 95, 28, Hobbies.HIKING);

        clientService.addClient(client1);
        clientService.addClient(client2);
        clientService.addClient(client3);

        System.out.println("Clienții au fost inserați cu succes în baza de date!");
    }

    private void openClientWindow(Client client) throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/practic_vacante/client_view.fxml"));
        Stage stage = new Stage();
        stage.setTitle(client.getName());
        stage.setScene(new Scene(loader.load()));

        ClientController controller = loader.getController();
        controller.setClient(client, hotelService, reservationService, specialOfferService); // Setăm toate serviciile

        stage.show();
    }




}
