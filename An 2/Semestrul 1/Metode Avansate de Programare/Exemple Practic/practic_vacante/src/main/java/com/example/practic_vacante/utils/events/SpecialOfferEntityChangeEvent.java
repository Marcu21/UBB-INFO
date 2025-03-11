package com.example.practic_vacante.utils.events;

import com.example.practic_vacante.domain.SpecialOffer;

public class SpecialOfferEntityChangeEvent implements Event {
    private ChangeEventType type;
    private SpecialOffer data, oldData;

    public SpecialOfferEntityChangeEvent(ChangeEventType type, SpecialOffer data) {
        this.type = type;
        this.data = data;
    }
    public SpecialOfferEntityChangeEvent(ChangeEventType type, SpecialOffer data, SpecialOffer oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public SpecialOffer getData() {
        return data;
    }

    public SpecialOffer getOldData() {
        return oldData;
    }
}