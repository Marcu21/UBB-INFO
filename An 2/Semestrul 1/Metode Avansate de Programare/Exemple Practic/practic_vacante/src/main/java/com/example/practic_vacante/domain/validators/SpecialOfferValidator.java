package com.example.practic_vacante.domain.validators;

import com.example.practic_vacante.domain.SpecialOffer;

import java.time.LocalDate;

public class SpecialOfferValidator implements Validator<SpecialOffer> {
    @Override
    public void validate(SpecialOffer entity) throws ValidationException {
        if (entity.getHotelId() == null) {
            throw new ValidationException("Special offer must have a valid hotel ID.");
        }
        if (entity.getStartDate() == null || entity.getEndDate() == null || !entity.getEndDate().isAfter(entity.getStartDate())) {
            throw new ValidationException("Invalid start or end date for special offer.");
        }
        if (entity.getPercents() < 1 || entity.getPercents() > 100) {
            throw new ValidationException("Discount percentage must be between 1 and 100.");
        }
    }
}
