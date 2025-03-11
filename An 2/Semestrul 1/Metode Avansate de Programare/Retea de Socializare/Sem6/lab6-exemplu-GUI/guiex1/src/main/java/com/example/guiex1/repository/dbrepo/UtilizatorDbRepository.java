package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;


import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UtilizatorDbRepository implements Repository<Long, Utilizator> {
    private String url;
    private String username;
    private String password;
    private Validator<Utilizator> validator;
    Connection connection;


    public UtilizatorDbRepository(String url, String username, String password, Validator<Utilizator> validator) {
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
    public Optional<Utilizator> findOne(Long id) {
        Utilizator user;
        try (ResultSet resultSet = connection.createStatement().executeQuery(String.format("select * from users U where U.id = '%d'", id))) {
            if (resultSet.next()) {
                user = createUserFromResultSet(resultSet);
                return Optional.ofNullable(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }


    private Utilizator createUserFromResultSet(ResultSet resultSet) {
        try {
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");
            String email = resultSet.getString("email");
            String parola = resultSet.getString("parola");
            String profilePictureURL = resultSet.getString("profile_picture_url");
            String bio = resultSet.getString("bio");

            Long idd = resultSet.getLong("id");
            Utilizator user = new Utilizator(firstName, lastName, email, parola, profilePictureURL, bio);
            user.setId(idd);
            return user;
        } catch (SQLException e) {
            return null;
        }
    }


    @Override
    public Iterable<Utilizator> findAll() {
        Set<Utilizator> users = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * from users");
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                String email = resultSet.getString("email");
                String parola = resultSet.getString("parola");
                String profilePictureURL = resultSet.getString("profile_picture_url");
                String bio = resultSet.getString("bio");

                Utilizator utilizator = new Utilizator(firstName, lastName, email, parola, profilePictureURL, bio);
                utilizator.setId(id);
                users.add(utilizator);
            }
            return users;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }


    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        String sql = "insert into users (first_name, last_name, email, parola, profile_picture_url, bio) values (?, ?, ?, ?, ?, ?)";
        validator.validate(entity);
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setString(3, entity.getEmail());
            ps.setString(4, entity.getPassword());
            ps.setString(5, entity.getProfilePictureURL());
            ps.setString(6, entity.getBio());

            ps.executeUpdate();
        } catch (SQLException e) {
            return Optional.ofNullable(entity);
        }
        return Optional.empty();
    }


    @Override
    public Optional<Utilizator> delete(Long id) {
        String sql = "delete from users where id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            Optional<Utilizator> user = findOne(id);
            if (!user.isEmpty()) {
                ps.setLong(1, id);
                ps.executeUpdate();
            }
            return user;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Utilizator> update(Utilizator user) {
        String sql = "update users set first_name = ?, last_name = ?, email = ?, parola = ?, profile_picture_url = ?, bio = ? where id = ?";
        validator.validate(user);
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, user.getFirstName());
            ps.setString(2, user.getLastName());
            ps.setString(3, user.getEmail());
            ps.setString(4, user.getPassword());
            ps.setString(5, user.getProfilePictureURL());
            ps.setString(6, user.getBio());
            ps.setLong(7, user.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
            return Optional.ofNullable(user);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }
}

