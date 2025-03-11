package com.example.practic_vacante.repository;

import com.example.practic_vacante.domain.Client;
import com.example.practic_vacante.domain.Hobbies;
import com.example.practic_vacante.domain.validators.Validator;
import com.example.practic_vacante.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class ClientDbRepository implements Repository<Long, Client> {
    private String url;
    private String username;
    private String password;
    private Validator<Client> validator;
    private Connection connection;

    public ClientDbRepository(String url, String username, String password, Validator<Client> validator) {
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

    private Client createClientFromResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("client_id");
        String name = resultSet.getString("name");
        int fidelityGrade = resultSet.getInt("fidelity_grade");
        int age = resultSet.getInt("age");
        String hobby = resultSet.getString("hobby");

        Client client = new Client(id, name, fidelityGrade, age, Enum.valueOf(Hobbies.class, hobby));
        client.setId(id);
        return client;
    }

    @Override
    public Optional<Client> findOne(Long id) {
        String sql = "SELECT * FROM clients WHERE client_id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createClientFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Client> findAll() {
        Set<Client> clients = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM clients")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                clients.add(createClientFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return clients;
    }

    @Override
    public Optional<Client> save(Client entity) {
        validator.validate(entity);
        String sql = "INSERT INTO clients (client_id, name, fidelity_grade, age, hobby) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1, entity.getId());
            ps.setString(2, entity.getName());
            ps.setInt(3, entity.getFidelityGrade());
            ps.setInt(4, entity.getAge());
            ps.setString(5, entity.getHobby().name());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Client> delete(Long id) {
        Optional<Client> client = findOne(id);
        if (client.isPresent()) {
            String sql = "DELETE FROM clients WHERE client_id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setLong(1, id);
                ps.executeUpdate();
                return client;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Client> update(Client entity) {
        validator.validate(entity);
        String sql = "UPDATE clients SET name = ?, fidelity_grade = ?, age = ?, hobby = ? WHERE client_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getName());
            ps.setInt(2, entity.getFidelityGrade());
            ps.setInt(3, entity.getAge());
            ps.setString(4, entity.getHobby().name());
            ps.setLong(5, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }
}
