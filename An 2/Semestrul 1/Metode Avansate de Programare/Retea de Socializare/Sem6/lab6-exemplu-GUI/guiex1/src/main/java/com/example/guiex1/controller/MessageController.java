package com.example.guiex1.controller;

import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.FriendshipRequestService;
import com.example.guiex1.services.MessageService;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.MessageEntityChangeEvent;
import com.example.guiex1.utils.observer.Observer;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.util.Duration;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Collections;
import java.util.List;

public class MessageController implements Observer<MessageEntityChangeEvent> {
    MessageService service;
    UtilizatorService utilizatorService;
    FriendshipRequestService friendshipRequestService;
    PrietenieService prietenieService;
    Utilizator user1;
    Utilizator user2;

    @FXML
    private ListView<String> messageList;
    @FXML
    private TextField messageInput;

    private ObservableList<String> observableMessages = FXCollections.observableArrayList();

    public void setMessageService(MessageService service, UtilizatorService utilizatorService,
                                  FriendshipRequestService friendshipRequestService, PrietenieService prietenieService) {
        this.service = service;
        this.utilizatorService = utilizatorService;
        this.friendshipRequestService = friendshipRequestService;
        this.prietenieService = prietenieService;
        this.service.addObserver(this);
    }

    public void setUtilizatori(Utilizator user1, Utilizator user2) {
        this.user1 = user1;
        this.user2 = user2;
        initModel();
    }


    @FXML
    public void initialize() {
        messageList.setItems(observableMessages);
    }

    private void initModel() {
        service.getMessagesBetween(user1.getId(), user2.getId()).forEach(message ->
                observableMessages.add(formatMessage(message))
        );
    }

    private String formatMessage(Message message) {
        StringBuilder formattedMessage = new StringBuilder();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
        String timestamp = message.getData().format(formatter);
        String sender = message.getFrom().getId().equals(user1.getId()) ? "You" : message.getFrom().getFirstName();

        formattedMessage.append(String.format("%s (%s): %s", sender, timestamp, message.getMessage()));

        if (message.getReply() != null) {
            Message originalMessage = message.getReply();
            if (originalMessage != null) {
                formattedMessage.append(" [Replying to: ")
                        .append(originalMessage.getFrom().getFirstName())
                        .append("(")
                        .append(originalMessage.getData().format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss")))
                        .append("): ")
                        .append(originalMessage.getMessage())
                        .append("]");
            }
        }

        System.out.println("Formatted message: " + formattedMessage.toString());

        return formattedMessage.toString();
    }



    @Override
    public void update(MessageEntityChangeEvent messageEntityChangeEvent) {
        if (messageEntityChangeEvent.getType() == ChangeEventType.ADD) {
            Message newMessage = messageEntityChangeEvent.getData();
            observableMessages.add(formatMessage(newMessage));
        }
    }

    @FXML
    public void handleSendMessage(ActionEvent actionEvent) {
        String content = messageInput.getText();
        if (!content.isEmpty()) {
            String selectedItem = messageList.getSelectionModel().getSelectedItem();
            if (selectedItem != null && !selectedItem.isEmpty()) {
                // "You (23-11-2024 17:16:00): Mesajul trimis"
                int startOfDate = selectedItem.indexOf('(') + 1;
                int endOfDate = selectedItem.indexOf(')');
                int startOfMessage = selectedItem.indexOf(')') + 3;
                String dateStr = selectedItem.substring(startOfDate, endOfDate);
                String messageStr = selectedItem.substring(startOfMessage);

                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
                LocalDateTime dateTime = LocalDateTime.parse(dateStr, formatter);

                System.out.println("Date: " + dateTime);
                System.out.println("Message: " + messageStr);

                Message replyTo = service.getMessage(user1.getId(), user2.getId(), messageStr, dateTime);
                Message newMessage = new Message(user1, Collections.singletonList(user2), content, LocalDateTime.now(), replyTo);
                service.addMessage(newMessage);
                messageInput.clear();
            }
            else {
                Message newMessage = new Message(user1, Collections.singletonList(user2), content, LocalDateTime.now());
                service.addMessage(newMessage);
                messageInput.clear();
            }
        }
    }

    private void resetInputField() {
        messageInput.setPromptText("Write a message");
        messageInput.setText("");
    }

    @FXML
    public void handleMessageSelect(MouseEvent mouseEvent) {
        if (mouseEvent.getClickCount() == 1) {
            resetInputField();
        }
        else
        if (mouseEvent.getClickCount() == 2) {
            String selectedMessage = messageList.getSelectionModel().getSelectedItem();
            if (selectedMessage != null) {
                messageInput.setPromptText("Reply to: " + selectedMessage);
                messageInput.requestFocus();
            }
        }
    }

}
