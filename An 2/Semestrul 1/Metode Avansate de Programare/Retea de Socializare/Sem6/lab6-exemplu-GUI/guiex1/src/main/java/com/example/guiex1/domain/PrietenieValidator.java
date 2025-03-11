package com.example.guiex1.domain;

public class PrietenieValidator implements Validator<Prietenie> {
    @Override
    public void validate(Prietenie entity) throws ValidationException {
        if (entity.getFirstUserId() == null || entity.getSecondUserId() == null) {
            throw new ValidationException("Id-ul nu poate fi null");
        }
        if (entity.getFirstUserId().equals(entity.getSecondUserId())) {
            throw new ValidationException("Id-urile trebuie sa fie diferite");
        }
    }
}
