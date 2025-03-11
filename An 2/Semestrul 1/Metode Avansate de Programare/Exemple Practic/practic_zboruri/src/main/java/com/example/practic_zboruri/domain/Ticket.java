package com.example.practic_zboruri.domain;

import java.time.LocalDateTime;



public class Ticket extends Entity<Long>{
    private String username;
    private Long flightId;
    private LocalDateTime purchaseTime;

    public Ticket() {}

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Long getFlightId() {
        return flightId;
    }

    public void setFlightId(Long flightId) {
        this.flightId = flightId;
    }

    public LocalDateTime getPurchaseTime() {
        return purchaseTime;
    }

    public void setPurchaseTime(LocalDateTime purchaseTime) {
        this.purchaseTime = purchaseTime;
    }

    @Override
    public String toString() {
        return "Ticket{" +
                "id=" + getId() +
                ", username='" + username + '\'' +
                ", flightId=" + flightId +
                ", purchaseTime=" + purchaseTime +
                '}';
    }
}
