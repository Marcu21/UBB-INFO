package com.example.practic_vacante.domain.validators;

import com.example.practic_vacante.domain.Client;

public class ClientValidator implements Validator<Client> {
    @Override
    public void validate(Client entity) throws ValidationException {
        if (entity.getName() == null || entity.getName().isEmpty()) {
            throw new ValidationException("Client's name cannot be empty.");
        }
        if (entity.getFidelityGrade() < 1 || entity.getFidelityGrade() > 100) {
            throw new ValidationException("Fidelity grade must be between 1 and 100.");
        }
        if (entity.getAge() <= 0) {
            throw new ValidationException("Age must be greater than 0.");
        }
        if (entity.getHobby() == null) {
            throw new ValidationException("Hobby must not be null.");
        }
    }
}
