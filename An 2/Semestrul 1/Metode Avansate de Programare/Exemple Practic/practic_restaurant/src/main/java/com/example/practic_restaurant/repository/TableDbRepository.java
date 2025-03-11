package com.example.practic_restaurant.repository;

import com.example.practic_restaurant.domain.Table;
import com.example.practic_restaurant.domain.validators.Validator;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class TableDbRepository implements Repository<Integer, Table> {
    private String url;
    private String username;
    private String password;
    private Validator<Table> validator;
    private Connection connection;

    public TableDbRepository(String url, String username, String password, Validator<Table> validator) {
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

    @Override
    public Optional<Table> findOne(Integer id) {
        try (PreparedStatement ps = connection.prepareStatement("SELECT * FROM tables WHERE id = ?")) {
            ps.setInt(1, id);
            ResultSet resultSet = ps.executeQuery();
            if (resultSet.next()) {
                Table table = new Table(resultSet.getInt("id"));
                return Optional.of(table);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Table> findAll() {
        Set<Table> tables = new HashSet<>();
        try (PreparedStatement ps = connection.prepareStatement("SELECT * FROM tables")) {
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                Table table = new Table(resultSet.getInt("id"));
                tables.add(table);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return tables;
    }

    @Override
    public Optional<Table> save(Table entity) {
        validator.validate(entity);
        String sql = "INSERT INTO tables (id) VALUES (?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getId());
            ps.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<Table> delete(Integer id) {
        String sql = "DELETE FROM tables WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            Optional<Table> table = findOne(id);
            if (table.isPresent()) {
                ps.setInt(1, id);
                ps.executeUpdate();
                return table;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Table> update(Table entity) {
        validator.validate(entity);
        String sql = "UPDATE tables SET id = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getId());
            ps.setInt(2, entity.getId());
            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }
}