package com.example.guiex1.utils.events;

import com.example.guiex1.domain.Prietenie;

public class PrietenieEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Prietenie data;

    public PrietenieEntityChangeEvent(ChangeEventType type, Prietenie data) {
        this.type = type;
        this.data = data;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Prietenie getData() {
        return data;
    }
}
