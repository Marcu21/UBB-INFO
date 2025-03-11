package com.example.practic_vacante.domain;

import java.time.LocalDate;

public class SpecialOfferDTO {
    private String hotelName;
    private String locationName;
    private LocalDate startDate;
    private LocalDate endDate;

    public SpecialOfferDTO(String hotelName, String locationName, LocalDate startDate, LocalDate endDate) {
        this.hotelName = hotelName;
        this.locationName = locationName;
        this.startDate = startDate;
        this.endDate = endDate;
    }

    public String getHotelName() {
        return hotelName;
    }

    public String getLocationName() {
        return locationName;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }
}
