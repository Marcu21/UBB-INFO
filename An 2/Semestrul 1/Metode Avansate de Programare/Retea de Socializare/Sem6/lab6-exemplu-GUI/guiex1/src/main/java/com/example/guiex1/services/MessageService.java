package com.example.guiex1.services;

import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.MessageEntityChangeEvent;
import com.example.guiex1.utils.events.PrietenieEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

public class MessageService implements Observable<MessageEntityChangeEvent> {
    private Repository<Long, Message> messageRepository;
    private UtilizatorService utilizatorService;
    private List<Observer<MessageEntityChangeEvent>> observers = new ArrayList<>();

    public MessageService(Repository<Long, Message> messageRepository, UtilizatorService utilizatorService) {
        this.messageRepository = messageRepository;
        this.utilizatorService = utilizatorService;
    }

    public Message addMessage(Message message) {
        if (messageRepository.save(message).isEmpty()) {
            notifyObservers(new MessageEntityChangeEvent(ChangeEventType.ADD, message));
            return null;
        }
        return message;
    }

    public ArrayList<Message> getMessagesBetween(Long id1, Long id2) {
        Utilizator user1 = utilizatorService.findOne(id1);
        Utilizator user2 = utilizatorService.findOne(id2);

        Collection<Message> messages = (Collection<Message>) messageRepository.findAll();
//        System.out.println(messages);
        return messages.stream()
                .filter(msg -> ((msg.getFrom().getId().equals(id1)) && msg.getTo().get(0).getId().equals(id2)) ||
                        (msg.getFrom().getId().equals(id2) && msg.getTo().get(0).getId().equals(id1)))
                .sorted(Comparator.comparing(Message::getData))
                .collect(Collectors.toCollection(ArrayList::new));


    }

    public Message getMessage(Long id1, Long id2, String message, LocalDateTime date) {
        ArrayList<Message> messages = getMessagesBetween(id1, id2);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String formattedDate = date.format(formatter);

        for (Message msg : messages) {
            String formattedMsgDate = msg.getData().format(formatter);
            if (msg.getMessage().equals(message) && formattedMsgDate.equals(formattedDate)) {
                return msg;
            }
        }
        return null;
    }

    public Iterable<Message> getAllMessages() {
        return messageRepository.findAll();
    }

    @Override
    public void addObserver(Observer<MessageEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<MessageEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(MessageEntityChangeEvent t) {
        observers.forEach(observer -> observer.update(t));
    }
}
