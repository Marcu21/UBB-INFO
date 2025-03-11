package com.example.examen_practic.repository;

import com.example.examen_practic.domain.Animal;
import com.example.examen_practic.domain.AnimalType;
import com.example.examen_practic.domain.validators.Validator;

import java.sql.*;
import java.util.*;

public class AnimalDbRepository implements Repository<Integer, Animal> {
    private String url;
    private String username;
    private String password;
    private Validator<Animal> validator;
    private Connection connection;

    public AnimalDbRepository(String url, String username, String password, Validator<Animal> validator) {
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

    private Animal createFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        String name = resultSet.getString("name");
        int centreId = resultSet.getInt("centre_id");
        AnimalType type = AnimalType.valueOf(resultSet.getString("type"));

        Animal animal = new Animal(id, name, centreId, type);
        return animal;
    }

    @Override
    public Optional<Animal> findOne(Integer id) {
        String sql = "SELECT * FROM animal WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Animal> findAll() {
        Set<Animal> animals = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM animal")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                animals.add(createFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return animals;
    }

    @Override
    public Optional<Animal> save(Animal entity) {
        validator.validate(entity);
        String sql = "INSERT INTO animal (id, name, centre_id, type) VALUES (?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getId());
            ps.setString(2, entity.getName());
            ps.setInt(3, entity.getCentreId());
            ps.setString(4, entity.getType().name());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Animal> delete(Integer id) {
        Optional<Animal> animal = findOne(id);
        if (animal.isPresent()) {
            String sql = "DELETE FROM animal WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setInt(1, id);
                ps.executeUpdate();
                return animal;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<Animal> update(Animal entity) {
        validator.validate(entity);
        String sql = "UPDATE animal SET name = ?, centre_id = ?, type = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getName());
            ps.setInt(2, entity.getCentreId());
            ps.setString(3, entity.getType().name());
            ps.setInt(4, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    public List<Animal> findByCentreAndType(int centreId, AnimalType type) {
        List<Animal> animals = new ArrayList<>();
        String sql = "SELECT * FROM animal WHERE centre_id = ?";

        if (type != null) {
            sql += " AND type = ?";
        }

        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, centreId);
            if (type != null) {
                statement.setString(2, type.name());
            }

            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                animals.add(createFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return animals;
    }

}
