package com.example.practic_zboruri.utils.events;

import com.example.practic_zboruri.domain.Flight;

public class FlightChangeEventType implements Event {
    private ChangeEventType type;
    private Flight data, oldData;

    public FlightChangeEventType(ChangeEventType type, Flight data) {
        this.type = type;
        this.data = data;
    }
    public FlightChangeEventType(ChangeEventType type, Flight data, Flight oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Flight getData() {
        return data;
    }

    public Flight getOldData() {
        return oldData;
    }
}
