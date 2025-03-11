package com.example.practic_zboruri.domain.validators;

import com.example.practic_zboruri.domain.Client;

public class ClientValidator implements Validator<Client> {
    @Override
    public void validate(Client entity) throws ValidationException {
        String errors = "";
        if (entity.getName().equals("")) {
            errors += "Numele nu poate fi vid! ";
        }
        if (entity.getUsername().equals("")) {
            errors += "Username nu poate fi vid! ";
        }
        if (!errors.equals("")) {
            throw new ValidationException(errors);
        }
    }
}
