package com.example.guiex1.domain;

import java.time.LocalDateTime;
import java.util.Date;

public class FriendDetail {
    private Utilizator user;
    private LocalDateTime friendsFrom;

    public FriendDetail(Utilizator user, LocalDateTime friendsFrom) {
        this.user = user;
        this.friendsFrom = friendsFrom;
    }

    public String getFirstName() {
        return user.getFirstName();
    }

    public String getLastName() {
        return user.getLastName();
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }
}

