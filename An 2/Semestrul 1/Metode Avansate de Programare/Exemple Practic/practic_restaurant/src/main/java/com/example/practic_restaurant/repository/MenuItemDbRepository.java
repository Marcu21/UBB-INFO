package com.example.practic_restaurant.repository;

import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.domain.validators.Validator;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class MenuItemDbRepository implements Repository<Integer, MenuItem> {
    private String url;
    private String username;
    private String password;
    private Validator<MenuItem> validator;
    private Connection connection;

    public MenuItemDbRepository(String url, String username, String password, Validator<MenuItem> validator) {
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
    public Optional<MenuItem> findOne(Integer id) {
        String sql = "SELECT * FROM menu_items WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, id);
            ResultSet resultSet = ps.executeQuery();
            if (resultSet.next()) {
                return Optional.of(new MenuItem(
                        resultSet.getInt("id"),
                        resultSet.getString("category"),
                        resultSet.getString("item"),
                        resultSet.getFloat("price"),
                        resultSet.getString("currency")
                ));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<MenuItem> findAll() {
        Set<MenuItem> menuItems = new HashSet<>();
        String sql = "SELECT * FROM menu_items";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                MenuItem menuItem = new MenuItem(
                        resultSet.getInt("id"),
                        resultSet.getString("category"),
                        resultSet.getString("item"),
                        resultSet.getFloat("price"),
                        resultSet.getString("currency")
                );
                menuItems.add(menuItem);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return menuItems;
    }

    @Override
    public Optional<MenuItem> save(MenuItem entity) {
        validator.validate(entity);
        String sql = "INSERT INTO menu_items (id, category, item, price, currency) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getId());
            ps.setString(2, entity.getCategory());
            ps.setString(3, entity.getItem());
            ps.setFloat(4, entity.getPrice());
            ps.setString(5, entity.getCurrency());
            ps.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
            return Optional.of(entity);
        }
    }

    @Override
    public Optional<MenuItem> delete(Integer id) {
        String sql = "DELETE FROM menu_items WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            Optional<MenuItem> menuItem = findOne(id);
            if (menuItem.isPresent()) {
                ps.setInt(1, id);
                ps.executeUpdate();
                return menuItem;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<MenuItem> update(MenuItem entity) {
        validator.validate(entity);
        String sql = "UPDATE menu_items SET category = ?, item = ?, price = ?, currency = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, entity.getCategory());
            ps.setString(2, entity.getItem());
            ps.setFloat(3, entity.getPrice());
            ps.setString(4, entity.getCurrency());
            ps.setInt(5, entity.getId());
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
