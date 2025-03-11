package com.example.guiex1.controller;

import com.example.guiex1.domain.*;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.*;
import com.example.guiex1.utils.observer.Observer;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;
import javafx.application.Platform;
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
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class FriendsController implements Observer {
    PrietenieService service;
    UtilizatorService utilizatorService;
    FriendshipRequestService friendshipRequestService;
    MessageService messageService;
    Utilizator user;
    @FXML
    TableView<FriendDetail> tableView;
    @FXML
    TableColumn<Utilizator, String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator, String> tableColumnLastName;
    @FXML
    TableColumn<Prietenie, LocalDateTime> tableFriendsFrom;
    @FXML
    TextField fieldNume;
    @FXML
    TextField fieldPrenume;
    @FXML
    private Label pendingRequestsLabel;
    @FXML
    private Button nextButton;
    @FXML
    private Button prevButton;
    @FXML
    private Label pageNumber;

    private int currentPage = 0;
    private int pageSize = 2;
    private ObservableList<FriendDetail> model = FXCollections.observableArrayList();

    public void setUtilizator(Utilizator user) {
        this.user = user;
        initModel();
        updateFriendRequestsCount();
    }

    public void setPrietenieService(PrietenieService service, UtilizatorService utilizatorService, FriendshipRequestService friendshipRequestService, MessageService messageService) {
        this.service = service;
        this.utilizatorService = utilizatorService;
        this.friendshipRequestService = friendshipRequestService;
        this.messageService = messageService;
        this.service.addObserver(this);
        this.friendshipRequestService.addObserver(this);
        initModel();
        updateFriendRequestsCount();
    }

    @FXML
    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        tableFriendsFrom.setCellValueFactory(new PropertyValueFactory<>("friendsFrom"));
        tableView.setItems(model);

        tableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                fieldNume.setText(newSelection.getLastName());
                fieldPrenume.setText(newSelection.getFirstName());
            } else {
                fieldNume.setText("");
                fieldPrenume.setText("");
            }
        });
    }

    private void initModel() {
        if (this.user == null) {
            System.out.println("User is null, model cannot be initialized.");
            return;
        }

        Page<Prietenie> page = service.findFriendshipsForUserOnPage(user.getId(), new Pageable(currentPage, pageSize));
        List<Prietenie> prietenii = StreamSupport.stream(page.getElementsOnPage().spliterator(), false).toList();
        List<FriendDetail> friendDetails = new ArrayList<>();
        for (Prietenie p : prietenii) {
            Utilizator friend = utilizatorService.findOne(p.getFirstUserId().equals(user.getId()) ? p.getSecondUserId() : p.getFirstUserId());
            if (friend != null) {
                friendDetails.add(new FriendDetail(friend, p.getFriendsFrom()));
            }
        }
        model.setAll(friendDetails);
        prevButton.setDisable(currentPage == 0);
        int noOfPages = (int) (Math.ceil((double) page.getTotalNumberElements() / pageSize));
        nextButton.setDisable(currentPage + 1 >= noOfPages);
        if (noOfPages == 0) pageNumber.setText((currentPage + 1) + " / " + 1);
        else pageNumber.setText((currentPage + 1) + " / " + noOfPages);
    }

    @Override
    public void update(Event event) {
        if (event instanceof FriendshipRequestsEntityChangeEvent) {
            handleFriendshipRequestChangeEvent((FriendshipRequestsEntityChangeEvent) event);
        }
        initModel();
    }

    private void handleFriendshipRequestChangeEvent(FriendshipRequestsEntityChangeEvent event) {
        updateFriendRequestsCount();
        if (event.getType() == ChangeEventType.ADD && event.getData().getReceiverId().equals(user.getId())) {
            Platform.runLater(() -> {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("New Friend Request");
                alert.setHeaderText(null);
                alert.setContentText("Ai primit o noua cerere de prietenie de la " + utilizatorService.findOne(event.getData().getSenderId()).getFirstName() + " " + utilizatorService.findOne(event.getData().getSenderId()).getLastName());
                alert.showAndWait();
            });
        }
    }

    public void handleSendFriendRequest(ActionEvent actionEvent) {
        String firstName = fieldPrenume.getText();
        String lastName = fieldNume.getText();
        Utilizator utilizator = utilizatorService.getUtilizatorByFirstNameAndLastName(firstName, lastName);
        if (utilizator == null) {
            MessageAlert.showErrorMessage(null, "Utilizatorul nu exista");
            return;
        }

        try {
            friendshipRequestService.sendFriendRequest(user.getId(), utilizator.getId());
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Cerere trimisa", "Cererea de prietenie a fost trimisa cu succes");
        } catch (Exception e) {
            MessageAlert.showErrorMessage(null, "Eroare la trimiterea cererii de prietenie: " + e.getMessage());
        }
    }

    public void handleDeletePrieten(ActionEvent actionEvent) {
        FriendDetail friend = tableView.getSelectionModel().getSelectedItem();
        if (friend != null) {
            Utilizator prieten = utilizatorService.getUtilizatorByFirstNameAndLastName(friend.getFirstName(), friend.getLastName());
            for (Prietenie p : service.getAllPrietenii()) {
                if ((p.getFirstUserId().equals(user.getId()) && p.getSecondUserId().equals(prieten.getId())) ||
                        (p.getFirstUserId().equals(prieten.getId()) && p.getSecondUserId().equals(user.getId()))) {
                    service.deletePrietenie(p.getId());
                    break;
                }
            }
            //initModel();
        } else {
            MessageAlert.showErrorMessage(null, "Nu ati selectat nici un prieten");
        }
    }

    public void updateFriendRequestsCount() {
        Platform.runLater(() -> {
            int count = friendshipRequestService.getAllFriendRequestsForUser(user.getId()).stream()
                    .filter(friendshipRequest -> "pending".equals(friendshipRequest.getStatus()))
                    .collect(Collectors.toList()).size();
            pendingRequestsLabel.setText(String.valueOf(count));
        });
    }

    public void handleFriendRequests(ActionEvent actionEvent) {
        Utilizator selected = user;
        if (selected != null) {
            try {
                FXMLLoader loader = new FXMLLoader();
                System.out.println("Classpath location: " + getClass().getProtectionDomain().getCodeSource().getLocation());
                URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/FriendshipRequestsView.fxml");
                System.out.println("Loading FXML from: " + fxmlUrl);
                if (fxmlUrl == null) {
                    throw new IOException("Cannot find FXML resource");
                }
                loader.setLocation(fxmlUrl);
                AnchorPane root = loader.load();

                FriendshipRequestsController controller = loader.getController();
                controller.setFriendshipRequestService(friendshipRequestService, service, utilizatorService);
                controller.setUtilizator(selected);

                Stage stage = new Stage();
                stage.setTitle("Cereri de prietenie pentru " + selected.getFirstName() + " " + selected.getLastName());
                stage.setScene(new Scene(root, 700, 500));
                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
                MessageAlert.showErrorMessage(null, "Eroare la deschiderea ferestrei de friend requests: " + e.getMessage());
            }
        } else {
            MessageAlert.showErrorMessage(null, "Selectati un utilizator pentru a gestiona prietenii");
        }
    }

    public void handleMessage(ActionEvent actionEvent) {
        Utilizator selected = user;
        FriendDetail friend = tableView.getSelectionModel().getSelectedItem();
        Utilizator selected2 = utilizatorService.getUtilizatorByFirstNameAndLastName(friend.getFirstName(), friend.getLastName());
        if (selected != null && selected2 != null) {
            try {
                FXMLLoader loader = new FXMLLoader();
                System.out.println("Classpath location: " + getClass().getProtectionDomain().getCodeSource().getLocation());
                URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/MessageView.fxml");
                System.out.println("Loading FXML from: " + fxmlUrl);
                if (fxmlUrl == null) {
                    throw new IOException("Cannot find FXML resource");
                }
                loader.setLocation(fxmlUrl);
                AnchorPane root = loader.load();

                MessageController controller = loader.getController();
                controller.setMessageService(messageService, utilizatorService, friendshipRequestService, service);
                controller.setUtilizatori(selected, selected2);

                Stage stage = new Stage();
                stage.setTitle("Mesaje cu " + selected2.getFirstName() + " " + selected2.getLastName());
                stage.setScene(new Scene(root, 700, 500));
                stage.show();
            } catch (IOException e) {
                e.printStackTrace();
                MessageAlert.showErrorMessage(null, "Eroare la deschiderea ferestrei de mesaje: " + e.getMessage());
            }
        } else {
            MessageAlert.showErrorMessage(null, "Selectati un utilizator pentru a trimite mesaj");
        }
    }

    public void onPreviousPage(ActionEvent actionEvent) {
        currentPage--;
        initModel();
    }

    public void onNextPage(ActionEvent actionEvent) {
        currentPage++;
        initModel();
    }

    public void handleMyProfile(ActionEvent actionEvent) {
        try {
            FXMLLoader loader = new FXMLLoader();
            URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/ProfileView.fxml");
            if (fxmlUrl == null) {
                throw new IOException("Cannot find FXML resource for ProfileView.");
            }
            loader.setLocation(fxmlUrl);
            VBox root = loader.load();

            UserProfileController controller = loader.getController();
            controller.setServices(utilizatorService, service);
            controller.setUser(user);
            controller.enableEditing();

            Stage stage = new Stage();
            stage.setTitle("Profilul meu - " + user.getFirstName() + " " + user.getLastName());
            stage.setScene(new Scene(root, 700, 750));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
            MessageAlert.showErrorMessage(null, "Eroare la deschiderea profilului utilizatorului: " + e.getMessage());
        }
    }


    public void handleOpenUserProfile(ActionEvent actionEvent) {
        FriendDetail friend = tableView.getSelectionModel().getSelectedItem();
        if (friend == null) {
            MessageAlert.showErrorMessage(null, "Selectați un prieten pentru a-i vedea profilul.");
            return;
        }

        Utilizator friendUser = utilizatorService.getUtilizatorByFirstNameAndLastName(friend.getFirstName(), friend.getLastName());
        if (friendUser == null) {
            MessageAlert.showErrorMessage(null, "Nu s-a putut găsi utilizatorul selectat.");
            return;
        }

        try {
            FXMLLoader loader = new FXMLLoader();
            URL fxmlUrl = getClass().getResource("/com/example/guiex1/views/ProfileView.fxml");
            if (fxmlUrl == null) {
                throw new IOException("Cannot find FXML resource for ProfileView.");
            }
            loader.setLocation(fxmlUrl);
            VBox root = loader.load();

            UserProfileController controller = loader.getController();
            controller.setServices(utilizatorService, service);
            controller.setMainUser(user);
            controller.setUser(friendUser);
            controller.disableEditing();

            Stage stage = new Stage();
            stage.setTitle("Profilul lui " + friendUser.getFirstName() + " " + friendUser.getLastName());
            stage.setScene(new Scene(root, 700, 750));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
            MessageAlert.showErrorMessage(null, "Eroare la deschiderea profilului prietenului: " + e.getMessage());
        }
    }
}
