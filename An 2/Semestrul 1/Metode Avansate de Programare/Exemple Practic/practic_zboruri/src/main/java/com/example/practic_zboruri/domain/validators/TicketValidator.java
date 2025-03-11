package com.example.practic_zboruri.domain.validators;

import com.example.practic_zboruri.domain.Ticket;

public class TicketValidator implements Validator<Ticket> {
    @Override
    public void validate(Ticket entity) throws ValidationException {
        String errors = "";
        if (entity.getFlightId() == null || entity.getFlightId() < 0) {
            errors += "Flight id must be a positive integer!\n";
        }
        if (entity.getUsername() == null)
            errors += "Username must not be null!\n";
        if (entity.getPurchaseTime() == null)
            errors += "Purchase time must not be null!\n";
        if (!errors.isEmpty()) {
            throw new ValidationException(errors);
        }
    }
}
