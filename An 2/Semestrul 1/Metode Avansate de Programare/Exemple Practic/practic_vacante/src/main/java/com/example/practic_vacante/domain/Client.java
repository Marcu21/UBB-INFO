package com.example.practic_vacante.domain;

public class Client extends Entity<Long> {
    private String name;
    private int fidelityGrade;
    private int age;
    private Hobbies hobby;

    public Client(Long clientId, String name, int fidelityGrade, int age, Hobbies hobby) {
        setId(clientId);
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.age = age;
        this.hobby = hobby;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public void setFidelityGrade(int fidelityGrade) {
        this.fidelityGrade = fidelityGrade;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public Hobbies getHobby() {
        return hobby;
    }

    public void setHobby(Hobbies hobby) {
        this.hobby = hobby;
    }
}
