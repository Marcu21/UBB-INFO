package com.example.practic_erou.utils.events;

import com.example.practic_erou.domain.Nevoie;

public class NevoieEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Nevoie data, oldData;

    public NevoieEntityChangeEvent(ChangeEventType type, Nevoie data) {
        this.type = type;
        this.data = data;
    }
    public NevoieEntityChangeEvent(ChangeEventType type, Nevoie data, Nevoie oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Nevoie getData() {
        return data;
    }

    public Nevoie getOldData() {
        return oldData;
    }
}