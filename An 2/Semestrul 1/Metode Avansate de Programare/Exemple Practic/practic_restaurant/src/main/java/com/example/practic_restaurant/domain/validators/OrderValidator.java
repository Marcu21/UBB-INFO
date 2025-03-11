package com.example.practic_restaurant.domain.validators;

import com.example.practic_restaurant.domain.Order;
import com.example.practic_restaurant.domain.OrderStatus;

public class OrderValidator implements Validator<Order> {
    @Override
    public void validate(Order order) throws ValidationException {
        // Validare ID
        if (order.getId() != null && order.getId() <= 0) {
            throw new ValidationException("Order ID must be positive.");
        }

        // Validare masă
        if (order.getTable() == null) {
            throw new ValidationException("Table cannot be null.");
        }

        // Validare produse
        if (order.getMenuItems() == null || order.getMenuItems().isEmpty()) {
            throw new ValidationException("Order must have at least one menu item.");
        }

        // Validare dată
        if (order.getDate() == null) {
            throw new ValidationException("Order date cannot be null.");
        }

        // Validare status
        if (order.getStatus() == null) {
            throw new ValidationException("Order status cannot be null.");
        }

        // Validare status valid (ne asigurăm că statusul e un valor valid din enum-ul OrderStatus)
        if (!isValidStatus(order.getStatus())) {
            throw new ValidationException("Invalid order status.");
        }
    }

    // Verificăm dacă statusul este valid
    private boolean isValidStatus(OrderStatus status) {
        for (OrderStatus validStatus : OrderStatus.values()) {
            if (validStatus == status) {
                return true;
            }
        }
        return false;
    }
}
