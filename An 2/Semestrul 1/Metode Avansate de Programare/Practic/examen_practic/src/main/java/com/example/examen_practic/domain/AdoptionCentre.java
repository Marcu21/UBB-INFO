package com.example.examen_practic.domain;

public class AdoptionCentre extends Entity<Integer> {
    private String name;
    private String location;
    private int capacity;

    public AdoptionCentre(Integer id, String name, String location, int capacity) {
        this.setId(id);
        this.name = name;
        this.location = location;
        this.capacity = capacity;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }
}
