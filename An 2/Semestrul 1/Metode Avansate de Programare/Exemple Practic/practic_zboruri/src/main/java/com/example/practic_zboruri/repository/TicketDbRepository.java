package com.example.practic_zboruri.repository;

import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.domain.Ticket;
import com.example.practic_zboruri.domain.validators.Validator;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class TicketDbRepository implements Repository<Long, Ticket> {
    private String url;
    private String username;
    private String password;
    private Validator<Ticket> validator;
    private Connection connection;

    public TicketDbRepository(String url, String username, String password, Validator<Ticket> validator) {
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

    private Ticket createTicketFromResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String username = resultSet.getString("username");
        Long flight_Id = resultSet.getLong("flight_id");
        LocalDateTime purchaseTime = resultSet.getTimestamp("purchase_time").toLocalDateTime();

        Ticket ticket = new Ticket();
        ticket.setId(id);
        ticket.setUsername(username);
        ticket.setFlightId(flight_Id);
        ticket.setPurchaseTime(purchaseTime);
        return ticket;
    }

    @Override
    public Optional<Ticket> findOne(Long id) {
        String sql = "SELECT * FROM tickets WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createTicketFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Ticket> findAll() {
        Set<Ticket> tickets = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM tickets")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                tickets.add(createTicketFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return tickets;
    }

    @Override
    public Optional<Ticket> save(Ticket entity) {
        String sql = "INSERT INTO tickets (id, username, flight_id, purchase_time) VALUES (?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getId());
            ps.setString(2, entity.getUsername());
            ps.setLong(3, entity.getFlightId());
            ps.setTimestamp(4, Timestamp.valueOf(entity.getPurchaseTime()));

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Ticket> delete(Long id) {
        Optional<Ticket> ticket = findOne(id);
        if (ticket.isPresent()) {
            String sql = "DELETE FROM tickets WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setLong(1, id);
                ps.executeUpdate();
                return ticket;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Ticket> update(Ticket entity) {
        String sql = "UPDATE tickets SET username = ?, flight_id = ?, purchase_time = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getUsername());
            ps.setLong(2, entity.getFlightId());
            ps.setTimestamp(3, Timestamp.valueOf(entity.getPurchaseTime()));
            ps.setLong(4, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }
}
