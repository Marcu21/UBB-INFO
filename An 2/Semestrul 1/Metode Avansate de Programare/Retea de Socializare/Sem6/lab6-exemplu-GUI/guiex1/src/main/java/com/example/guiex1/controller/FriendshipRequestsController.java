package com.example.guiex1.controller;

import com.example.guiex1.domain.FriendDetail;
import com.example.guiex1.domain.FriendRequestsDetail;
import com.example.guiex1.domain.FriendshipRequest;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.FriendshipRequestsEntityChangeEvent;
import com.example.guiex1.utils.events.PrietenieEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.format.DateTimeFormatter;
import java.util.List;

public class FriendshipRequestsController implements Observer<FriendshipRequestsEntityChangeEvent> {

    FriendshipRequestService service;
    PrietenieService prietenieService;
    UtilizatorService utilizatorService;
    Utilizator user;

    @FXML
    private TableView<FriendRequestsDetail> tableView;
    @FXML
    TableColumn<Utilizator,String> tableColumnFirstName;
    @FXML
    TableColumn<Utilizator,String> tableColumnLastName;
    @FXML
    private TableColumn<FriendshipRequest, String> statusColumn;
    @FXML
    private TableColumn<FriendshipRequest, String> dateColumn;
    @FXML
    TextField fieldNume;
    @FXML
    TextField fieldPrenume;

    private ObservableList<FriendRequestsDetail> model = FXCollections.observableArrayList();

    public void setUtilizator(Utilizator user) {
        this.user = user;
        initModel();
    }

    public void setFriendshipRequestService(FriendshipRequestService friendshipRequestService, PrietenieService prietenieService, UtilizatorService utilizatorService) {
        this.service = friendshipRequestService;
        this.utilizatorService = utilizatorService;
        this.prietenieService = prietenieService;
        initModel();
        this.service.addObserver(this);
    }

    public void initialize() {
        tableColumnFirstName.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        tableColumnLastName.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        statusColumn.setCellValueFactory(new PropertyValueFactory<>("status"));
        dateColumn.setCellValueFactory(new PropertyValueFactory<>("date"));
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

    public void initModel() {
        if (this.user == null) {
            System.out.println("User is null, model cannot be initialized.");
            return;
        }

        List<FriendRequestsDetail> requestsDetails = service.getFriendRequestsDetailsForUser(user.getId());
        model.setAll(requestsDetails);
    }

    @Override
    public void update(FriendshipRequestsEntityChangeEvent friendshipRequestsEntityChangeEvent) {
        initModel();
    }

    public void handleAcceptFriendRequest(ActionEvent actionEvent) {
        FriendRequestsDetail detail = tableView.getSelectionModel().getSelectedItem();
        if (detail != null) {
            Utilizator otherUser = detail.getUser();
            if (service.acceptFriendRequest(otherUser.getId(), user.getId())) {
                System.out.println("Friend request accepted.");
            }
            else {
                MessageAlert.showErrorMessage(null, "Could not accept friend request.");
            }
        }
        else {
            MessageAlert.showErrorMessage(null, "No friend request selected.");
        }
    }
}
