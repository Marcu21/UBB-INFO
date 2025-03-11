package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.FriendshipRequest;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class FriendshipRequestDbRepository implements Repository<Long, FriendshipRequest> {
    private String url;
    private String username;
    private String password;
    private Validator<FriendshipRequest> validator;
    Connection connection;

    public FriendshipRequestDbRepository(String url, String username, String password, Validator<FriendshipRequest> validator) {
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
    public Optional<FriendshipRequest> findOne(Long id) {
        String query = "SELECT * FROM FriendshipRequests WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long senderId = resultSet.getLong("sender_id");
                Long receiverId = resultSet.getLong("receiver_id");
                String status = resultSet.getString("status");
                LocalDateTime requestDate = resultSet.getTimestamp("request_date").toLocalDateTime();

                FriendshipRequest request = new FriendshipRequest(senderId, receiverId, status, requestDate);
                request.setId(id);
                return Optional.of(request);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<FriendshipRequest> findAll() {
        Set<FriendshipRequest> requests = new HashSet<>();
        String query = "SELECT * FROM FriendshipRequests";
        try (PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                Long senderId = resultSet.getLong("sender_id");
                Long receiverId = resultSet.getLong("receiver_id");
                String status = resultSet.getString("status");
                LocalDateTime requestDate = resultSet.getTimestamp("request_date").toLocalDateTime();

                FriendshipRequest request = new FriendshipRequest(senderId, receiverId, status, requestDate);
                request.setId(resultSet.getLong("id"));
                requests.add(request);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return requests;
    }

    @Override
    public Optional<FriendshipRequest> save(FriendshipRequest entity) {
        validator.validate(entity);
        String query = "INSERT INTO FriendshipRequests (sender_id, receiver_id, status, request_date) VALUES (?, ?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            statement.setLong(1, entity.getSenderId());
            statement.setLong(2, entity.getReceiverId());
            statement.setString(3, entity.getStatus());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getRequestDate()));

            int affectedRows = statement.executeUpdate();
            if (affectedRows > 0) {
                try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        entity.setId(generatedKeys.getLong(1));
                    }
                    return Optional.empty();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<FriendshipRequest> delete(Long id) {
        FriendshipRequest deletedFriendshipRequest;
        String query = "DELETE FROM FriendshipRequests WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                deletedFriendshipRequest = new FriendshipRequest(-1L, -1L, null, null);
                return Optional.of(deletedFriendshipRequest);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<FriendshipRequest> update(FriendshipRequest entity) {
        validator.validate(entity);
        String query = "UPDATE FriendshipRequests SET sender_id = ?, receiver_id = ?, status = ?, request_date = ? WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, entity.getSenderId());
            statement.setLong(2, entity.getReceiverId());
            statement.setString(3, entity.getStatus());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getRequestDate()));
            statement.setLong(5, entity.getId());

            int result = statement.executeUpdate();
            if (result > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

}
