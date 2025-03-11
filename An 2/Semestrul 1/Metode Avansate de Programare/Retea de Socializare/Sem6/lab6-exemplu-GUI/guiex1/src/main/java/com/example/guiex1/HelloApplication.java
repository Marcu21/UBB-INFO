package com.example.guiex1;

import com.example.guiex1.controller.LoginViewController;
import com.example.guiex1.domain.*;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.FriendshipRequestDbRepository;
import com.example.guiex1.repository.dbrepo.MessageDbRepository;
import com.example.guiex1.repository.dbrepo.PrietenieDbRepository;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import java.io.IOException;

public class HelloApplication extends Application {
    UtilizatorService service;
    PrietenieService prietenieService;
    FriendshipRequestService friendshipRequestService;
    MessageService messageService;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        System.out.println("Reading data from database");
        String username="postgres";
        String pasword="skerdix";
        String url="jdbc:postgresql://localhost:5432/map_project";
        Repository<Long, Utilizator> utilizatorRepository =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());
        Repository<Long, Prietenie> prietenieRepository =
                new PrietenieDbRepository(url,username, pasword,  new PrietenieValidator());
        Repository<Long, FriendshipRequest> friendshipRequestRepository =
                new FriendshipRequestDbRepository(url,username, pasword,  new FriendshipRequestValidator());
        Repository<Long, Message> messageRepository =
                new MessageDbRepository(url,username, pasword,  new MessageValidator(), utilizatorRepository);
        service =new UtilizatorService(utilizatorRepository);
        prietenieService = new PrietenieService((PrietenieDbRepository) prietenieRepository,utilizatorRepository);
        friendshipRequestService = new FriendshipRequestService(friendshipRequestRepository, prietenieService, service);
        messageService = new MessageService(messageRepository, service);

        initView(primaryStage);
        primaryStage.setWidth(700);
        primaryStage.show();
    }

    private void initView(Stage primaryStage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("views/LoginView.fxml"));

        AnchorPane userLayout = fxmlLoader.load();
        primaryStage.setScene(new Scene(userLayout));

        LoginViewController userController = fxmlLoader.getController();
        userController.setLoginService(service, prietenieService, friendshipRequestService, messageService);
    }
}