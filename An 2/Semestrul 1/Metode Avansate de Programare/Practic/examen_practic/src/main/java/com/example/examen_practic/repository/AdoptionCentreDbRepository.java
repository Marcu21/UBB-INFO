package com.example.examen_practic.repository;

import com.example.examen_practic.domain.AdoptionCentre;
import com.example.examen_practic.domain.validators.Validator;

import java.sql.*;
import java.util.*;

public class AdoptionCentreDbRepository implements Repository<Integer, AdoptionCentre> {
    private String url;
    private String username;
    private String password;
    private Validator<AdoptionCentre> validator;
    private Connection connection;

    public AdoptionCentreDbRepository(String url, String username, String password, Validator<AdoptionCentre> validator) {
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

    private AdoptionCentre createFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        String name = resultSet.getString("name");
        String location = resultSet.getString("location");
        int capacity = resultSet.getInt("capacity");

        AdoptionCentre centre = new AdoptionCentre(id, name, location, capacity);
        return centre;
    }

    @Override
    public Optional<AdoptionCentre> findOne(Integer id) {
        String sql = "SELECT * FROM adoption_centre WHERE id = ?";
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
    public Iterable<AdoptionCentre> findAll() {
        Set<AdoptionCentre> centres = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM adoption_centre")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                centres.add(createFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return centres;
    }

    @Override
    public Optional<AdoptionCentre> save(AdoptionCentre entity) {
        validator.validate(entity);
        String sql = "INSERT INTO adoption_centre (id, name, location, capacity) VALUES (?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getId());
            ps.setString(2, entity.getName());
            ps.setString(3, entity.getLocation());
            ps.setInt(4, entity.getCapacity());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<AdoptionCentre> delete(Integer id) {
        Optional<AdoptionCentre> centre = findOne(id);
        if (centre.isPresent()) {
            String sql = "DELETE FROM adoption_centre WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setInt(1, id);
                ps.executeUpdate();
                return centre;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<AdoptionCentre> update(AdoptionCentre entity) {
        validator.validate(entity);
        String sql = "UPDATE adoption_centre SET name = ?, location = ?, capacity = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getName());
            ps.setString(2, entity.getLocation());
            ps.setInt(3, entity.getCapacity());
            ps.setInt(4, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }


    public List<AdoptionCentre> findByLocation(String location) {
        List<AdoptionCentre> centres = new ArrayList<>();
        String sql = "SELECT * FROM adoption_centre WHERE location = ?";

        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, location);
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                AdoptionCentre centre = new AdoptionCentre(
                        resultSet.getInt("id"),
                        resultSet.getString("name"),
                        resultSet.getString("location"),
                        resultSet.getInt("capacity")
                );
                centres.add(centre);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return centres;
    }


}
