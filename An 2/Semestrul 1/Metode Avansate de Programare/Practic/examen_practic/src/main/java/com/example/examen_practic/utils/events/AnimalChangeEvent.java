package com.example.examen_practic.utils.events;

import com.example.examen_practic.domain.Animal;

public class AnimalChangeEvent implements Event {
    private ChangeEventType type;
    private Animal data, oldData;

    public AnimalChangeEvent(ChangeEventType type, Animal data) {
        this.type = type;
        this.data = data;
    }
    public AnimalChangeEvent(ChangeEventType type, Animal data, Animal oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Animal getData() {
        return data;
    }

    public Animal getOldData() {
        return oldData;
    }
}