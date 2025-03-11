package com.example.practic_zboruri.controller;

import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.service.ClientService;
import com.example.practic_zboruri.service.FlightService;
import com.example.practic_zboruri.service.TicketService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
    private ClientService clientService;
    private FlightService flightService;
    private TicketService ticketService;

    @FXML
    private TextField usernameField;

    @FXML
    private Button loginButton;

    public void setLoginService(ClientService clientService, FlightService flightService, TicketService ticketService) {
        this.ticketService = ticketService;
        this.flightService = flightService;
        this.clientService = clientService;
    }

    @FXML
    private void handleLoginButtonAction(ActionEvent event) {
        String username = usernameField.getText();
        Client client = clientService.login(username);
        if (client == null) {
            showAlert("Login failed", "Client not found");
        } else {
            System.out.println("Client found: " + client);
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/practic_zboruri/client.fxml"));
                Scene scene = new Scene(loader.load());
                ClientController clientController = loader.getController();
                clientController.setClientService(client, clientService, flightService, ticketService);
                Stage newStage = new Stage();
                newStage.setTitle("Client!");
                newStage.setScene(scene);
                newStage.show();
            } catch (IOException e) {
                showAlert("Error", "Error while opening main window");
            }
        }
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }


}
