package com.example.guiex1.utils.events;

import com.example.guiex1.domain.Message;

public class MessageEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Message data;

    public MessageEntityChangeEvent(ChangeEventType type, Message data) {
        this.type = type;
        this.data = data;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Message getData() {
        return data;
    }
}
