package com.example.practic_zboruri.repository;

import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.domain.Flight;
import com.example.practic_zboruri.domain.validators.Validator;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FlightDbRepository implements Repository<Long, Flight> {
    private String url;
    private String username;
    private String password;
    private Validator<Flight> validator;
    private Connection connection;

    public FlightDbRepository(String url, String username, String password, Validator<Flight> validator) {
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

    private Flight createFlightFromResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String from = resultSet.getString("from_location");
        String to = resultSet.getString("to_location");
        Timestamp departureTime = resultSet.getTimestamp("departure_time");
        Timestamp landingTime = resultSet.getTimestamp("landing_time");
        int seats = resultSet.getInt("seats");

        Flight flight = new Flight();
        flight.setId(id);
        flight.setFrom(from);
        flight.setTo(to);
        flight.setDepartureTime(departureTime.toLocalDateTime());
        flight.setLandingTime(landingTime.toLocalDateTime());
        flight.setSeats(seats);
        return flight;
    }

    @Override
    public Optional<Flight> findOne(Long id) {
        String sql = "SELECT * FROM flights WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createFlightFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Flight> findAll() {
        Set<Flight> flights = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM flights")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                flights.add(createFlightFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return flights;
    }

    @Override
    public Optional<Flight> save(Flight entity) {
        validator.validate(entity);
        String sql = "INSERT INTO flights (id, from_location, to_location, departure_time, landing_time, seats) VALUES (?, ?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getId());
            ps.setString(2, entity.getFrom());
            ps.setString(3, entity.getTo());
            ps.setTimestamp(4, Timestamp.valueOf(entity.getDepartureTime()));
            ps.setTimestamp(5, Timestamp.valueOf(entity.getLandingTime()));
            ps.setInt(6, entity.getSeats());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Flight> delete(Long id) {
        Optional<Flight> flight = findOne(id);
        if (flight.isPresent()) {
            String sql = "DELETE FROM flights WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setLong(1, id);
                ps.executeUpdate();
                return flight;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Flight> update(Flight entity) {
        validator.validate(entity);
        String sql = "UPDATE flights SET from_location = ?, to_location = ?, departure_time = ?, landing_time = ?, seats = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getFrom());
            ps.setString(2, entity.getTo());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getDepartureTime()));
            ps.setTimestamp(4, Timestamp.valueOf(entity.getLandingTime()));
            ps.setInt(5, entity.getSeats());
            ps.setLong(6, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }
}
