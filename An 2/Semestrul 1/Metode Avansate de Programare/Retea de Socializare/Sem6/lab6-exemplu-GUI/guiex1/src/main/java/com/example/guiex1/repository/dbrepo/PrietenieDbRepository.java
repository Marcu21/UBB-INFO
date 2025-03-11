package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.Prietenie;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.PagingRepository;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class PrietenieDbRepository implements PagingRepository<Long, Prietenie> {
    private String url;
    private String username;
    private String password;
    private Validator<Prietenie> validator;
    Connection connection;

    public PrietenieDbRepository(String url, String username, String password, Validator<Prietenie> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
        try{
            connection = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<Prietenie> findOne(Long id) {
        String query = "SELECT * FROM friendships WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long user_id1 = resultSet.getLong("user_id1");
                Long user_id2 = resultSet.getLong("user_id2");
                LocalDateTime friendsFrom = resultSet.getTimestamp("friends_from").toLocalDateTime();

                Prietenie prietenie = new Prietenie(user_id1, user_id2, friendsFrom);
                prietenie.setId(id);
                return Optional.of(prietenie);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Prietenie> findAll() {
        Set<Prietenie> friendships = new HashSet<>();
        String query = "SELECT * FROM friendships";
        try (PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long user_id1 = resultSet.getLong("user_id1");
                Long user_id2 = resultSet.getLong("user_id2");
                Timestamp friendsFromTimestamp = resultSet.getTimestamp("friends_from");
                LocalDateTime friendsFrom = friendsFromTimestamp != null ? friendsFromTimestamp.toLocalDateTime() : null;

                Prietenie prietenie = new Prietenie(user_id1, user_id2, friendsFrom);
                prietenie.setId(id);
                friendships.add(prietenie);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return friendships;
    }


    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        validator.validate(entity);
        String query = "INSERT INTO friendships (user_id1, user_id2, friends_from) VALUES (?, ?, ?)";
        try (PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            statement.setLong(1, entity.getFirstUserId());
            statement.setLong(2, entity.getSecondUserId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getFriendsFrom()));

            int result = statement.executeUpdate();
            if (result > 0) {
                try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                    if (generatedKeys.next()) {
                        entity.setId(generatedKeys.getLong(1));
                    }
                }
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<Prietenie> delete(Long id) {
        Prietenie deletedFriendship = null;
        String query = "DELETE FROM friendships WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            statement.setLong(1, id);
            int rowsAffected = statement.executeUpdate();
            if (rowsAffected > 0) {
                deletedFriendship = new Prietenie(-1L, -1L, null);
                return Optional.of(deletedFriendship);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }


    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        validator.validate(entity);
        String query = "UPDATE friendships SET user_id1 = ?, user_id2 = ?, friends_from = ? WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, entity.getFirstUserId());
            statement.setLong(2, entity.getSecondUserId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getFriendsFrom()));
            statement.setLong(4, entity.getId());

            int result = statement.executeUpdate();
            if (result > 0) return Optional.empty();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Page<Prietenie> findAllOnPage(Pageable pageable) {
        List<Prietenie> pageContent = new ArrayList<>();
        String query = "SELECT * FROM friendships ORDER BY id LIMIT ? OFFSET ?";
        int totalElements = countTotalFriendships();

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setInt(1, pageable.getPageSize());
            statement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Prietenie prietenie = extractPrietenieFromResultSet(resultSet);
                pageContent.add(prietenie);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Error accessing database", e);
        }
        return new Page<>(pageContent, totalElements);
    }


    private Prietenie extractPrietenieFromResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        Long user_id1 = resultSet.getLong("user_id1");
        Long user_id2 = resultSet.getLong("user_id2");
        Timestamp friendsFromTimestamp = resultSet.getTimestamp("friends_from");
        Prietenie prietenie = new Prietenie(user_id1, user_id2, friendsFromTimestamp.toLocalDateTime());
        prietenie.setId(id);
        return prietenie;
    }

    private int countTotalFriendships() {
        String query = "SELECT COUNT(*) AS total FROM friendships";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt("total");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Error counting friendships", e);
        }
        return 0;
    }

    @Override
    public Page<Prietenie> findAllByUserIdOnPage(Long userId, Pageable pageable) {
        List<Prietenie> friendships = new ArrayList<>();
        String query = "SELECT * FROM friendships " +
                "WHERE user_id1 = ? OR user_id2 = ? " +
                "ORDER BY friends_from DESC " +
                "LIMIT ? OFFSET ?";

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, userId);
            statement.setLong(2, userId);
            statement.setInt(3, pageable.getPageSize());
            statement.setInt(4, pageable.getPageSize() * pageable.getPageNumber());

            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long user_id1 = resultSet.getLong("user_id1");
                Long user_id2 = resultSet.getLong("user_id2");
                LocalDateTime friendsFrom = resultSet.getTimestamp("friends_from").toLocalDateTime();

                Prietenie prietenie = new Prietenie(user_id1, user_id2, friendsFrom);
                prietenie.setId(id);
                friendships.add(prietenie);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        int totalElements = countFriendshipsForUser(userId);
        return new Page<>(friendships, totalElements);
    }


    private int countFriendshipsForUser(Long userId) {
        String query = "SELECT COUNT(*) FROM friendships WHERE user_id1 = ? OR user_id2 = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, userId);
            statement.setLong(2, userId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getInt(1);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return 0;
    }
}
