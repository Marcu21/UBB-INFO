package com.example.guiex1.utils.events;

import com.example.guiex1.domain.FriendshipRequest;

public class FriendshipRequestsEntityChangeEvent implements Event{
    private ChangeEventType type;
    private FriendshipRequest data;

    public FriendshipRequestsEntityChangeEvent(ChangeEventType type, FriendshipRequest data) {
        this.type = type;
        this.data = data;
    }

    public ChangeEventType getType() {
        return type;
    }

    public FriendshipRequest getData() {
        return data;
    }
}
