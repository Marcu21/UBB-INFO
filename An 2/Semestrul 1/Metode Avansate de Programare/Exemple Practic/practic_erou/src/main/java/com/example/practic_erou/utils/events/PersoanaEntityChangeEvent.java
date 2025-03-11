package com.example.practic_erou.utils.events;

import com.example.practic_erou.domain.Persoana;

public class PersoanaEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Persoana data, oldData;

    public PersoanaEntityChangeEvent(ChangeEventType type, Persoana data) {
        this.type = type;
        this.data = data;
    }
    public PersoanaEntityChangeEvent(ChangeEventType type, Persoana data, Persoana oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Persoana getData() {
        return data;
    }

    public Persoana getOldData() {
        return oldData;
    }
}