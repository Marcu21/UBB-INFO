package com.example.practic_restaurant.utils.events;

import com.example.practic_restaurant.domain.Order;

public class OrderChangeEvent implements Event {
    private ChangeEventType type;
    private Order data, oldData;

    public OrderChangeEvent(ChangeEventType type, Order data) {
        this.type = type;
        this.data = data;
    }
    public OrderChangeEvent(ChangeEventType type, Order data, Order oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Order getData() {
        return data;
    }

    public Order getOldData() {
        return oldData;
    }
}