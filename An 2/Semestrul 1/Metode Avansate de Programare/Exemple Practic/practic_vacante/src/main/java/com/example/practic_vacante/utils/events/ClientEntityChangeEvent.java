package com.example.practic_vacante.utils.events;

import com.example.practic_vacante.domain.Client;

public class ClientEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Client data, oldData;

    public ClientEntityChangeEvent(ChangeEventType type, Client data) {
        this.type = type;
        this.data = data;
    }
    public ClientEntityChangeEvent(ChangeEventType type, Client data, Client oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Client getData() {
        return data;
    }

    public Client getOldData() {
        return oldData;
    }
}