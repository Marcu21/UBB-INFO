package com.example.practic_erou.domain;

public enum Oras {
    CLUJ_NAPOCA,
    BUCURESTI,
    TIMISOARA,
    IASI,
    CONSTANTA,
    BRASOV;

    @Override
    public String toString() {
        return name().replace("_", " ");
    }
}
