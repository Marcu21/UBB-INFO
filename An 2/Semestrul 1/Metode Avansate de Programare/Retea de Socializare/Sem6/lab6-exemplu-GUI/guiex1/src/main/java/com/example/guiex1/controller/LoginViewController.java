package com.example.guiex1.controller;

import com.example.guiex1.domain.FriendshipRequest;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;

public class LoginViewController {
    private UtilizatorService service;
    private PrietenieService prietenieService;
    private FriendshipRequestService friendshipRequestService;
    private MessageService messageService;
    @FXML
    TextField fieldEmailLogin;
    @FXML
    TextField fieldPasswordLogin;
    @FXML
    TextField fieldEmailSignUp;
    @FXML
    TextField fieldPasswordSignUp;
    @FXML
    TextField fieldNumeSignUp;
    @FXML
    TextField fieldPrenumeSignUp;

    public void setLoginService(UtilizatorService service, PrietenieService prietenieService, FriendshipRequestService friendshipRequestService, MessageService messageService) {
        this.service = service;
        this.prietenieService = prietenieService;
        this.friendshipRequestService = friendshipRequestService;
        this.messageService = messageService;
    }

    public void handleSignUp(ActionEvent actionEvent) {
        String nume = fieldNumeSignUp.getText();
        String prenume = fieldPrenumeSignUp.getText();
        String email = fieldEmailSignUp.getText();
        String password = fieldPasswordSignUp.getText();
        Utilizator user = new Utilizator(prenume, nume, email, password, null, null);
        try {
            if(service.addUtilizator(user) == null) {
                System.out.println("Utilizatorul a fost adaugat cu succes!");
                try {
                    user = service.login(email, password);
                    FXMLLoader loader = new FXMLLoader();
                    System.out.println("Classpath location: " + getClass().getProtectionDomain().getCodeSource().getLocation());
                    URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/FriendsView.fxml");
                    System.out.println("Loading FXML from: " + fxmlUrl);
                    if (fxmlUrl == null) {
                        throw new IOException("Cannot find FXML resource");
                    }
                    loader.setLocation(fxmlUrl);
                    AnchorPane root = loader.load();

                    FriendsController controller = loader.getController();
                    controller.setPrietenieService(prietenieService, service, friendshipRequestService, messageService);
                    controller.setUtilizator(user);

                    Stage stage = new Stage();
                    stage.setTitle("Prietenii lui " + user.getFirstName() + " " + user.getLastName());
                    stage.setScene(new Scene(root, 700, 500));
                    stage.show();
                } catch (IOException e) {
                    e.printStackTrace();
                    MessageAlert.showErrorMessage(null, "Eroare la deschiderea ferestrei de prieteni: " + e.getMessage());
                }
            }
        } catch (RuntimeException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    public void handleLogin(ActionEvent actionEvent) {
        String email = fieldEmailLogin.getText();
        String password = fieldPasswordLogin.getText();
        System.out.println("Email: " + email + " Password: " + password);
        Utilizator user = service.login(email, password);
        System.out.println();
        if (user != null) {
            System.out.println("Login reusit");
            try {
                FXMLLoader loader = new FXMLLoader();
                System.out.println("Classpath location: " + getClass().getProtectionDomain().getCodeSource().getLocation());
                URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/FriendsView.fxml");
                System.out.println("Loading FXML from: " + fxmlUrl);
                if (fxmlUrl == null) {
                    throw new IOException("Cannot find FXML resource");
                }
                loader.setLocation(fxmlUrl);
                AnchorPane root = loader.load();

                FriendsController controller = loader.getController();
                controller.setPrietenieService(prietenieService, service, friendshipRequestService, messageService);
                controller.setUtilizator(user);

                Stage stage = new Stage();
                stage.setTitle("Prietenii lui " + user.getFirstName() + " " + user.getLastName());
                stage.setScene(new Scene(root, 700, 500));
                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
                MessageAlert.showErrorMessage(null, "Eroare la deschiderea ferestrei de prieteni: " + e.getMessage());
            }
        } else {
            MessageAlert.showErrorMessage(null, "Datele de autentificare sunt gresite!");
        }
    }
}
