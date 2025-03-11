package com.example.practic_vacante.utils.events;

import com.example.practic_vacante.domain.Reservation;

public class ReservationEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Reservation data, oldData;

    public ReservationEntityChangeEvent(ChangeEventType type, Reservation data) {
        this.type = type;
        this.data = data;
    }
    public ReservationEntityChangeEvent(ChangeEventType type, Reservation data, Reservation oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Reservation getData() {
        return data;
    }

    public Reservation getOldData() {
        return oldData;
    }
}