package com.example.practic_vacante.repository;

import com.example.practic_vacante.domain.Hotel;
import com.example.practic_vacante.domain.validators.Validator;
import com.example.practic_vacante.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class HotelDbRepository implements Repository<Double, Hotel> {
    private String url;
    private String username;
    private String password;
    private Validator<Hotel> validator;
    private Connection connection;

    public HotelDbRepository(String url, String username, String password, Validator<Hotel> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
        try {
            connection = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private Hotel createHotelFromResultSet(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("hotel_id");
        String locationName = resultSet.getString("location_name");
        String hotelName = resultSet.getString("hotel_name");
        int noRooms = resultSet.getInt("no_rooms");
        double pricePerNight = resultSet.getDouble("price_per_night");

        Hotel hotel = new Hotel(id, locationName, hotelName, noRooms, pricePerNight);
        hotel.setId(id);
        return hotel;
    }

    @Override
    public Optional<Hotel> findOne(Double id) {
        String sql = "SELECT * FROM hotels WHERE hotel_id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setDouble(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createHotelFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Hotel> findAll() {
        Set<Hotel> hotels = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM hotels")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                hotels.add(createHotelFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return hotels;
    }

    @Override
    public Optional<Hotel> save(Hotel entity) {
        validator.validate(entity);
        String sql = "INSERT INTO hotels (hotel_id, location_name, hotel_name, no_rooms, price_per_night) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setDouble(1, entity.getId());
            ps.setString(2, entity.getLocationName());
            ps.setString(3, entity.getHotelName());
            ps.setInt(4, entity.getNoRooms());
            ps.setDouble(5, entity.getPricePerNight());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Hotel> delete(Double id) {
        Optional<Hotel> hotel = findOne(id);
        if (hotel.isPresent()) {
            String sql = "DELETE FROM hotels WHERE hotel_id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setDouble(1, id);
                ps.executeUpdate();
                return hotel;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Hotel> update(Hotel entity) {
        validator.validate(entity);
        String sql = "UPDATE hotels SET location_name = ?, hotel_name = ?, no_rooms = ?, price_per_night = ? WHERE hotel_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getLocationName());
            ps.setString(2, entity.getHotelName());
            ps.setInt(3, entity.getNoRooms());
            ps.setDouble(4, entity.getPricePerNight());
            ps.setDouble(5, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }
}
