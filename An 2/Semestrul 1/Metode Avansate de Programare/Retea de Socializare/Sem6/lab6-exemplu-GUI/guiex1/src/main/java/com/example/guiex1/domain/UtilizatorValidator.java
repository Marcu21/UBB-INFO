package com.example.guiex1.domain;

public class UtilizatorValidator implements Validator<Utilizator> {
    @Override
    public void validate(Utilizator entity) throws ValidationException {
        //TODO: implement method validate
        if(entity.getFirstName() == null || entity.getLastName() == null)
            throw new ValidationException("Names cannot be null");
        if(entity.getEmail() == null || entity.getPassword() == null)
            throw new ValidationException("Email and password cannot be null");
    }
}
