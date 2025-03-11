package com.example.examen_practic.domain.validators;

import com.example.examen_practic.domain.Animal;

public class AnimalValidator implements Validator<Animal> {
    @Override
    public void validate(Animal entity) {
        if (entity.getName() == null) {
            throw new ValidationException("Animal name cannot be empty.");
        }
        if (entity.getCentreId() <= 0) {
            throw new ValidationException("Invalid Adoption Centre ID.");
        }
        if (entity.getType() == null) {
            throw new ValidationException("Animal type cannot be null.");
        }
    }
}
