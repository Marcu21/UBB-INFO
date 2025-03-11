package com.example.practic_vacante.domain.validators;

import com.example.practic_vacante.domain.Reservation;

import java.time.LocalDateTime;

public class ReservationValidator implements Validator<Reservation> {
    @Override
    public void validate(Reservation entity) throws ValidationException {
        if (entity.getClientId() == null) {
            throw new ValidationException("Reservation must have a valid client ID.");
        }
        if (entity.getHotelId() == null) {
            throw new ValidationException("Reservation must have a valid hotel ID.");
        }
        if (entity.getStartDate() == null || entity.getStartDate().isBefore(LocalDateTime.now())) {
            throw new ValidationException("Reservation start date must be in the future.");
        }
        if (entity.getNoNights() <= 0) {
            throw new ValidationException("Number of nights must be greater than 0.");
        }
    }
}
