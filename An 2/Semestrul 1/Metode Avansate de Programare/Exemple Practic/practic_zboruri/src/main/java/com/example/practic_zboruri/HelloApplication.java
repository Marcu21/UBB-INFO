package com.example.practic_zboruri;

import com.example.practic_zboruri.controller.LoginController;
import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.domain.Flight;
import com.example.practic_zboruri.domain.Ticket;
import com.example.practic_zboruri.domain.validators.ClientValidator;
import com.example.practic_zboruri.domain.validators.FlightValidator;
import com.example.practic_zboruri.domain.validators.TicketValidator;
import com.example.practic_zboruri.repository.ClientDbRepository;
import com.example.practic_zboruri.repository.FlightDbRepository;
import com.example.practic_zboruri.repository.Repository;
import com.example.practic_zboruri.repository.TicketDbRepository;
import com.example.practic_zboruri.service.ClientService;
import com.example.practic_zboruri.service.FlightService;
import com.example.practic_zboruri.service.TicketService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDateTime;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        System.out.println("Hello, World!");
        System.out.println("Reading data from database");

        String username = "postgres";
        String password = "skerdix";
        String url = "jdbc:postgresql://localhost:5432/zboruri";

        Repository<Long, Client> clientRepository = new ClientDbRepository(url, username, password, new ClientValidator());
        Repository<Long, Flight> flightRepository = new FlightDbRepository(url, username, password, new FlightValidator());
        Repository<Long, Ticket> ticketRepository = new TicketDbRepository(url, username, password, new TicketValidator());

        ClientService clientService = new ClientService(clientRepository);
        FlightService flightService = new FlightService(flightRepository);
        TicketService ticketService = new TicketService(ticketRepository);

        /*Flight flight = new Flight();
        flight.setId(1L);
        flight.setTo("Bucuresti");
        flight.setFrom("Cluj");
        flight.setDepartureTime(LocalDateTime.parse("2024-01-24T12:00:00"));
        flight.setLandingTime(LocalDateTime.parse("2024-01-24T14:00:00"));
        flight.setSeats(100);

        Flight flight1 = new Flight();
        flight1.setId(2L);
        flight1.setTo("America");
        flight1.setFrom("Carei");
        flight1.setDepartureTime(LocalDateTime.parse("2024-01-24T01:00:00"));
        flight1.setLandingTime(LocalDateTime.parse("2024-01-25T14:00:00"));
        flight1.setSeats(100);

        Flight flight3 = new Flight();
        flight3.setId(3L);
        flight3.setTo("Pitesti");
        flight3.setFrom("Braila");
        flight3.setDepartureTime(LocalDateTime.parse("2024-05-20T12:00:00"));
        flight3.setLandingTime(LocalDateTime.parse("2024-05-20T14:00:00"));
        flight3.setSeats(55);

        flightService.addFlight(flight);
        flightService.addFlight(flight1);
        flightService.addFlight(flight3);

        Ticket ticket = new Ticket();
        ticket.setId(1L);
        ticket.setUsername("manu21");
        ticket.setFlightId(1L);
        ticket.setPurchaseTime(LocalDateTime.now());

        Ticket ticket1 = new Ticket();
        ticket1.setId(2L);
        ticket1.setUsername("john123");
        ticket1.setFlightId(2L);
        ticket1.setPurchaseTime(LocalDateTime.parse("2024-01-24T12:00:00"));

        ticketService.addTicket(ticket);
        ticketService.addTicket(ticket1);*/


        /*Flight flight3 = new Flight();
        flight3.setId(4L);
        flight3.setTo("Carei");
        flight3.setFrom("Moftin");
        flight3.setDepartureTime(LocalDateTime.parse("2025-01-30T12:00:00"));
        flight3.setLandingTime(LocalDateTime.parse("2025-01-31T14:00:00"));
        flight3.setSeats(2);

        flightService.addFlight(flight3);*/

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 350, 300);

        LoginController loginController = fxmlLoader.getController();
        loginController.setLoginService(clientService, flightService, ticketService);

        stage.setTitle("LOGIN");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}