package com.example.guiex1.domain;

public class FriendshipRequestValidator implements Validator<FriendshipRequest> {
    @Override
    public void validate(FriendshipRequest entity) throws ValidationException {
        if (entity.getSenderId() == null || entity.getReceiverId() == null) {
            throw new ValidationException("Id-ul nu poate fi null");
        }
        if (entity.getSenderId().equals(entity.getReceiverId())) {
            throw new ValidationException("Id-urile trebuie sa fie diferite");
        }
        if(entity.getStatus() == null){
            throw new ValidationException("Status-ul nu poate fi null");
        }
        if(entity.getRequestDate() == null){
            throw new ValidationException("Data nu poate fi null");
        }
    }
}
