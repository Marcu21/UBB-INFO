/*
package com.example.guiex1.controller;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.ValidationException;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


import java.io.IOException;
import java.net.URL;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorController implements Observer<UtilizatorEntityChangeEvent> {
    UtilizatorService service;
    PrietenieService prietenieService;
    FriendshipRequestService friendshipRequestService;
    MessageService messageService;
    ObservableList<Utilizator> model = FXCollections.observableArrayList();

    @FXML
    TableView<Utilizator> tableView;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;
    @FXML
    TextField fieldNume;
    @FXML
    TextField fieldPrenume;

    public void setUtilizatorService(UtilizatorService service, PrietenieService prietenieService, FriendshipRequestService friendshipRequestService, MessageService messageService) {
        this.friendshipRequestService = friendshipRequestService;
        this.prietenieService = prietenieService;
        this.service = service;
        this.messageService = messageService;
        initModel();
        this.service.addObserver(this);
    }

    @FXML
    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableView.setItems(model);

        tableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                fieldNume.setText(newSelection.getLastName());
                fieldPrenume.setText(newSelection.getFirstName());
            }
            else {
                fieldNume.setText("");
                fieldPrenume.setText("");
            }
        });
    }

    private void initModel() {
        List<Utilizator> all_users = StreamSupport.stream(service.getAll().spliterator(), false)
                .collect(Collectors.toList());
        model.setAll(all_users);
    }

    @Override
    public void update(UtilizatorEntityChangeEvent utilizatorEntityChangeEvent) {
        initModel();
    }

    public void handleDeleteUtilizator(ActionEvent actionEvent) {
        Utilizator user=(Utilizator) tableView.getSelectionModel().getSelectedItem();
        if (user!=null) {
            Utilizator deleted= service.deleteUtilizator(user.getId());
            //initModel();
        }
    }

    public void handleUpdateUtilizator(ActionEvent actionEvent) {
        Utilizator user = tableView.getSelectionModel().getSelectedItem();
        if(user!=null)
        {
            Utilizator updatedUser = new Utilizator(fieldPrenume.getText(), fieldNume.getText());
            updatedUser.setId(user.getId());
            try
            {
                service.updateUtilizator(updatedUser);
                //initModel();
            }
            catch (ValidationException e)
            {
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
    }

    public void handleAddUtilizator(ActionEvent actionEvent) {
        String firstName = fieldPrenume.getText();
        String lastName = fieldNume.getText();
        try {
            Utilizator utilizator = new Utilizator(firstName, lastName);
            service.addUtilizator(utilizator);
            //initModel();
        }
        catch (ValidationException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    public void handleGestionarePrieteni(ActionEvent actionEvent) {
        Utilizator selected = tableView.getSelectionModel().getSelectedItem();
        if (selected != null) {
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
                controller.setUtilizator(service.findOne(selected.getId()));

                Stage stage = new Stage();
                stage.setTitle("Prieteni pentru " + selected.getFirstName() + " " + selected.getLastName());
                stage.setScene(new Scene(root, 700, 500));
                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
                MessageAlert.showErrorMessage(null, "Eroare la deschiderea ferestrei de prieteni: " + e.getMessage());
            }
        }
        else {
            MessageAlert.showErrorMessage(null, "Selectati un utilizator pentru a gestiona prietenii");
        }
    }

}
*/
