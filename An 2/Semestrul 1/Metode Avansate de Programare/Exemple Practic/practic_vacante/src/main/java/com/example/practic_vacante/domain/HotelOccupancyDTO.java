package com.example.practic_vacante.domain;

public class HotelOccupancyDTO {
    private String hotelName;
    private double occupancyRate;
    private double pricePerNight;

    public HotelOccupancyDTO(String hotelName, double occupancyRate, double pricePerNight) {
        this.hotelName = hotelName;
        this.occupancyRate = occupancyRate;
        this.pricePerNight = pricePerNight;
    }

    public String getHotelName() {
        return hotelName;
    }

    public double getOccupancyRate() {
        return occupancyRate;
    }

    public double getPricePerNight() {
        return pricePerNight;
    }
}
