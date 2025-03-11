package com.example.examen_practic.domain;

public class Animal extends Entity<Integer> {
    private String name;
    private int centreId;
    private AnimalType type;

    public Animal(Integer id, String name, int centreId, AnimalType type) {
        this.setId(id);
        this.name = name;
        this.centreId = centreId;
        this.type = type;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCentreId() {
        return centreId;
    }

    public void setCentreId(int centreId) {
        this.centreId = centreId;
    }

    public AnimalType getType() {
        return type;
    }

    public void setType(AnimalType type) {
        this.type = type;
    }
}
