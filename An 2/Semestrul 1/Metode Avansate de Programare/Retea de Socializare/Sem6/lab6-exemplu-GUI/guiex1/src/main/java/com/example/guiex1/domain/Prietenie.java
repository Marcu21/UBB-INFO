package com.example.guiex1.domain;

import com.example.guiex1.utils.events.Event;
import java.time.LocalDateTime;

public class Prietenie extends Entity<Long> {
    private Long firstUserId;
    private Long secondUserId;
    private LocalDateTime friendsFrom;

    public Prietenie(Long firstUserId, Long secondUserId, LocalDateTime friendsFrom) {
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
        this.friendsFrom = friendsFrom;
    }

    public Long getFirstUserId() {
        return firstUserId;
    }

    public void setFirstUserId(Long firstUserId) {
        this.firstUserId = firstUserId;
    }

    public Long getSecondUserId() {
        return secondUserId;
    }

    public void setSecondUserId(Long secondUserId) {
        this.secondUserId = secondUserId;
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    public void setFriendsFrom(LocalDateTime friendsFrom) {
        this.friendsFrom = friendsFrom;
    }

    @Override
    public String toString() {
        return "Prietenie{" +
                "firstUserId=" + firstUserId +
                ", secondUserId=" + secondUserId +
                ", friendsFrom=" + friendsFrom +
                '}';
    }
}
