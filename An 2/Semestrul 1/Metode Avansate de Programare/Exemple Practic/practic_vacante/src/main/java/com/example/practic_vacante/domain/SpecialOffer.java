package com.example.practic_vacante.domain;

import java.time.LocalDate;

public class SpecialOffer extends Entity<Double> {
    private Double hotelId;
    private LocalDate startDate;
    private LocalDate endDate;
    private int percents;

    public SpecialOffer(Double specialOfferId, Double hotelId, LocalDate startDate, LocalDate endDate, int percents) {
        setId(specialOfferId);
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public Double getHotelId() {
        return hotelId;
    }

    public void setHotelId(Double hotelId) {
        this.hotelId = hotelId;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }

    public int getPercents() {
        return percents;
    }

    public void setPercents(int percents) {
        this.percents = percents;
    }
}
