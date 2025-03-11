package com.example.guiex1.domain;

import java.time.LocalDateTime;

public class FriendRequestsDetail {
    private Utilizator user;
    private String status;
    private LocalDateTime date;

    public FriendRequestsDetail(Utilizator user, String status, LocalDateTime date) {
        this.user = user;
        this.status = status;
        this.date = date;
    }

    public String getFirstName() {
        return user.getFirstName();
    }

    public String getLastName() {
        return user.getLastName();
    }

    public String getStatus() {
        return status;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public Utilizator getUser() {
        return user;
    }

    public void setUser(Utilizator user) {
        this.user = user;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }
}
