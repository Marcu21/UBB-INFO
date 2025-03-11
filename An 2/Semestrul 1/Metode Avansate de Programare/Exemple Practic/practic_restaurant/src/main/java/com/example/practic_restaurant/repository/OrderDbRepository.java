package com.example.practic_restaurant.repository;

import com.example.practic_restaurant.domain.Order;
import com.example.practic_restaurant.domain.OrderStatus;
import com.example.practic_restaurant.domain.Table;
import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.domain.validators.Validator;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class OrderDbRepository implements Repository<Integer, Order> {
    private String url;
    private String username;
    private String password;
    private Validator<Order> validator;
    private Connection connection;

    public OrderDbRepository(String url, String username, String password, Validator<Order> validator) {
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
    public Optional<Order> findOne(Integer id) {
        String sql = "SELECT * FROM orders WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, id);
            ResultSet resultSet = ps.executeQuery();
            if (resultSet.next()) {
                Table table = new Table(resultSet.getInt("table_id"));
                List<MenuItem> menuItems = getMenuItemsByOrderId(id);
                Order order = new Order(
                        resultSet.getInt("id"),
                        table,
                        menuItems,
                        resultSet.getTimestamp("date").toLocalDateTime(),
                        OrderStatus.valueOf(resultSet.getString("status"))
                );
                return Optional.of(order);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Order> findAll() {
        List<Order> orders = new ArrayList<>();
        String sql = "SELECT * FROM orders";
        try (PreparedStatement ps = connection.prepareStatement(sql);
             ResultSet resultSet = ps.executeQuery()) {
            while (resultSet.next()) {
                Table table = new Table(resultSet.getInt("table_id"));
                List<MenuItem> menuItems = getMenuItemsByOrderId(resultSet.getInt("id"));
                Order order = new Order(
                        resultSet.getInt("id"),
                        table,
                        menuItems,
                        resultSet.getTimestamp("date").toLocalDateTime(),
                        OrderStatus.valueOf(resultSet.getString("status"))
                );
                orders.add(order);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return orders;
    }

    @Override
    public Optional<Order> save(Order entity) {
        validator.validate(entity);
        String sql = "INSERT INTO orders (table_id, date, status) VALUES (?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            ps.setInt(1, entity.getTable().getId());
            ps.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            ps.setString(3, entity.getStatus().name());
            ps.executeUpdate();

            ResultSet generatedKeys = ps.getGeneratedKeys();
            if (generatedKeys.next()) {
                int orderId = generatedKeys.getInt(1);
                saveOrderItems(orderId, entity.getMenuItems());
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Order> delete(Integer id) {
        String sql = "DELETE FROM orders WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            Optional<Order> order = findOne(id);
            if (order.isPresent()) {
                deleteOrderItems(id);
                ps.setInt(1, id);
                ps.executeUpdate();
                return order;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Order> update(Order entity) {
        validator.validate(entity);
        String sql = "UPDATE orders SET table_id = ?, date = ?, status = ? WHERE id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, entity.getTable().getId());
            ps.setTimestamp(2, Timestamp.valueOf(entity.getDate()));
            ps.setString(3, entity.getStatus().name());
            ps.setInt(4, entity.getId());
            if (ps.executeUpdate() > 0) {
                deleteOrderItems(entity.getId());
                saveOrderItems(entity.getId(), entity.getMenuItems());
                return Optional.empty();
            }
            return Optional.of(entity);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    private List<MenuItem> getMenuItemsByOrderId(int orderId) {
        List<MenuItem> menuItems = new ArrayList<>();
        String sql = "SELECT * FROM menu_items mi JOIN order_items oi ON mi.id = oi.menu_item_id WHERE oi.order_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, orderId);
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                menuItems.add(new MenuItem(
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
        return menuItems;
    }

    private void saveOrderItems(int orderId, List<MenuItem> menuItems) throws SQLException {
        String sql = "INSERT INTO order_items (order_id, menu_item_id) VALUES (?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            for (MenuItem menuItem : menuItems) {
                ps.setInt(1, orderId);
                ps.setInt(2, menuItem.getId());
                ps.addBatch();
            }
            ps.executeBatch();
        }
    }

    private void deleteOrderItems(int orderId) {
        String sql = "DELETE FROM order_items WHERE order_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1, orderId);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
