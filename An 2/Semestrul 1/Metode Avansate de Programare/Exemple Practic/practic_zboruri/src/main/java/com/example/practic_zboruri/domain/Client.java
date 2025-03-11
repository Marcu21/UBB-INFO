package com.example.practic_zboruri.domain;

public class Client extends Entity<Long> {
    private String username;
    private String name;

    public Client() {}

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Client{" +
                "id=" + getId() +
                ", username='" + username + '\'' +
                ", name='" + name + '\'' +
                '}';
    }
}
