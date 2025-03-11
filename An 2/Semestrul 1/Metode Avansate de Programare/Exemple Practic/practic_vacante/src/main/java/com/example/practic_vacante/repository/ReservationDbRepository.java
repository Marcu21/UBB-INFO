package com.example.practic_vacante.repository;

import com.example.practic_vacante.domain.Reservation;
import com.example.practic_vacante.domain.validators.Validator;
import com.example.practic_vacante.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class ReservationDbRepository implements Repository<Double, Reservation> {
    private String url;
    private String username;
    private String password;
    private Validator<Reservation> validator;
    private Connection connection;

    public ReservationDbRepository(String url, String username, String password, Validator<Reservation> validator) {
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

    private Reservation createReservationFromResultSet(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("reservation_id");
        Long clientId = resultSet.getLong("client_id");
        Double hotelId = resultSet.getDouble("hotel_id");
        Timestamp startDate = resultSet.getTimestamp("start_date");
        int noNights = resultSet.getInt("no_nights");

        Reservation reservation = new Reservation(id, clientId, hotelId, startDate.toLocalDateTime(), noNights);
        reservation.setId(id);
        return reservation;
    }

    @Override
    public Optional<Reservation> findOne(Double id) {
        String sql = "SELECT * FROM reservations WHERE reservation_id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setDouble(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createReservationFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Reservation> findAll() {
        Set<Reservation> reservations = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM reservations")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                reservations.add(createReservationFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reservations;
    }

    @Override
    public Optional<Reservation> save(Reservation entity) {
        validator.validate(entity);
        String sql = "INSERT INTO reservations (reservation_id, client_id, hotel_id, start_date, no_nights) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setDouble(1, entity.getId());
            ps.setLong(2, entity.getClientId());
            ps.setDouble(3, entity.getHotelId());
            ps.setTimestamp(4, Timestamp.valueOf(entity.getStartDate()));
            ps.setInt(5, entity.getNoNights());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Reservation> delete(Double id) {
        Optional<Reservation> reservation = findOne(id);
        if (reservation.isPresent()) {
            String sql = "DELETE FROM reservations WHERE reservation_id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setDouble(1, id);
                ps.executeUpdate();
                return reservation;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Reservation> update(Reservation entity) {
        validator.validate(entity);
        String sql = "UPDATE reservations SET client_id = ?, hotel_id = ?, start_date = ?, no_nights = ? WHERE reservation_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getClientId());
            ps.setDouble(2, entity.getHotelId());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getStartDate()));
            ps.setInt(4, entity.getNoNights());
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

