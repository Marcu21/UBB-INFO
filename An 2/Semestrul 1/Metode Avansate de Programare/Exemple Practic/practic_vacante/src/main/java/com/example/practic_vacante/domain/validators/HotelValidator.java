package com.example.practic_vacante.domain.validators;

import com.example.practic_vacante.domain.Hotel;

public class HotelValidator implements Validator<Hotel> {
    @Override
    public void validate(Hotel entity) throws ValidationException {
        if (entity.getHotelName() == null || entity.getHotelName().isEmpty()) {
            throw new ValidationException("Hotel name cannot be empty.");
        }
        if (entity.getLocationName() == null || entity.getLocationName().isEmpty()) {
            throw new ValidationException("Location name cannot be empty.");
        }
        if (entity.getNoRooms() <= 0) {
            throw new ValidationException("Number of rooms must be greater than 0.");
        }
        if (entity.getPricePerNight() <= 0) {
            throw new ValidationException("Price per night must be greater than 0.");
        }
    }
}
