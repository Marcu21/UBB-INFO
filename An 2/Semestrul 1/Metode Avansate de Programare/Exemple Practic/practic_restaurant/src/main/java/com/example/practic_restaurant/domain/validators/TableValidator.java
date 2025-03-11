package com.example.practic_restaurant.domain.validators;

import com.example.practic_restaurant.domain.Table;

public class TableValidator implements Validator<Table> {
    @Override
    public void validate(Table table) throws ValidationException {
        if (table.getId() <= 0) {
            throw new ValidationException("Table ID must be positive.");
        }
    }
}
