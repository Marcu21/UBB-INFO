package com.example.guiex1.domain;

import java.time.LocalDateTime;

public class FriendshipRequest extends Entity<Long> {
    private Long senderId;
    private Long receiverId;
    private String status;
    private LocalDateTime requestDate;

    public FriendshipRequest(Long senderId, Long receiverId, String status, LocalDateTime requestDate) {
        this.senderId = senderId;
        this.receiverId = receiverId;
        this.status = status;
        this.requestDate = requestDate;
    }

    public Long getSenderId() {
        return senderId;
    }

    public void setSenderId(Long senderId) {
        this.senderId = senderId;
    }

    public Long getReceiverId() {
        return receiverId;
    }

    public void setReceiverId(Long receiverId) {
        this.receiverId = receiverId;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public LocalDateTime getRequestDate() {
        return requestDate;
    }

    public void setRequestDate(LocalDateTime requestDate) {
        this.requestDate = requestDate;
    }
}
