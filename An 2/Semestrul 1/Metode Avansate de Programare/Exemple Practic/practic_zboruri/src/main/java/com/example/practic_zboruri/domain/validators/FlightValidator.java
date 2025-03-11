package com.example.practic_zboruri.domain.validators;

import com.example.practic_zboruri.domain.Flight;

public class FlightValidator implements Validator<Flight>{
    @Override
    public void validate(Flight entity) throws ValidationException {
        if(entity.getFrom().equals(entity.getTo()))
            throw new ValidationException("From and to cannot be the same");
        if(entity.getFrom() == null)
            throw new ValidationException("From cannot be null");
        if(entity.getTo() == null)
            throw new ValidationException("To cannot be null");
        if(entity.getDepartureTime() == null)
            throw new ValidationException("Departure time cannot be null");
        if(entity.getLandingTime() == null)
            throw new ValidationException("Landing time cannot be null");
        if(entity.getDepartureTime().isAfter(entity.getLandingTime()))
            throw new ValidationException("Departure time cannot be after landing time");
        if(entity.getSeats() < 0)
            throw new ValidationException("Seats cannot be negative");
    }
}
