package com.example.practic_restaurant.domain.validators;

import com.example.practic_restaurant.domain.MenuItem;

public class MenuItemValidator implements Validator<MenuItem> {
    @Override
    public void validate(MenuItem menuItem) throws ValidationException {
        if (menuItem.getId() <= 0) {
            throw new ValidationException("Menu item ID must be positive.");
        }
        if (menuItem.getCategory() == null || menuItem.getCategory().trim().isEmpty()) {
            throw new ValidationException("Category cannot be null or empty.");
        }
        if (menuItem.getItem() == null || menuItem.getItem().trim().isEmpty()) {
            throw new ValidationException("Item name cannot be null or empty.");
        }
        if (menuItem.getPrice() <= 0) {
            throw new ValidationException("Price must be positive.");
        }
        if (menuItem.getCurrency() == null || menuItem.getCurrency().trim().isEmpty()) {
            throw new ValidationException("Currency cannot be null or empty.");
        }
    }
}
