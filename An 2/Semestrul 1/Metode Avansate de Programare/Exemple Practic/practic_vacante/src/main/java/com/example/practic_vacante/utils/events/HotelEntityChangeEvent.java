package com.example.practic_vacante.utils.events;

import com.example.practic_vacante.domain.Hotel;

public class HotelEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Hotel data, oldData;

    public HotelEntityChangeEvent(ChangeEventType type, Hotel data) {
        this.type = type;
        this.data = data;
    }
    public HotelEntityChangeEvent(ChangeEventType type, Hotel data, Hotel oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Hotel getData() {
        return data;
    }

    public Hotel getOldData() {
        return oldData;
    }
}