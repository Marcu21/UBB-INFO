package com.example.guiex1.domain;

public class MessageValidator implements Validator<Message> {
    @Override
    public void validate(Message entity) throws ValidationException {
        if (entity.getFrom() == null) {
            throw new ValidationException("From-ul nu poate fi null");
        }
        if (entity.getTo() == null) {
            throw new ValidationException("To-ul nu poate fi null");
        }
        if (entity.getMessage() == null) {
            throw new ValidationException("Mesajul nu poate fi null");
        }
        if (entity.getData() == null) {
            throw new ValidationException("Data nu poate fi null");
        }
    }
}
