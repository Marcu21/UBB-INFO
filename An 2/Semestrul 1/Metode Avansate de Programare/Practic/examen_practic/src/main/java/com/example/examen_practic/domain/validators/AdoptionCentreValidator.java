package com.example.examen_practic.domain.validators;

import com.example.examen_practic.domain.AdoptionCentre;

public class AdoptionCentreValidator implements Validator<AdoptionCentre> {
    @Override
    public void validate(AdoptionCentre entity) {
        if (entity.getName() == null) {
            throw new ValidationException("Name cannot be empty.");
        }
        if (entity.getLocation() == null) {
            throw new ValidationException("Location cannot be empty.");
        }
        if (entity.getCapacity() <= 0) {
            throw new ValidationException("Capacity must be greater than zero.");
        }
    }
}
