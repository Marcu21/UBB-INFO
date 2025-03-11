package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Prietenie;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.Validator;
import com.example.guiex1.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

public class MessageDbRepository implements Repository<Long, Message> {
    private String url;
    private String username;
    private String password;
    private Validator<Message> validator;
    private Repository<Long, Utilizator> userRepository;
    Connection connection;

    public MessageDbRepository(String url, String username, String password, Validator<Message> validator, Repository<Long, Utilizator> userRepository) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
        this.userRepository = userRepository;
        try {
            connection = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Optional<Message> findOneNoReply(Long aLong) {
        String query = "SELECT * FROM messages WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query);
        ) {
            statement.setLong(1, aLong);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long from_id = resultSet.getLong("from_id");
                Long to_id = resultSet.getLong("to_id");
                String message = resultSet.getString("message");
                LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();
                Message msg = new Message(userRepository.findOne(from_id).get(), Collections.singletonList(userRepository.findOne(to_id).get()), message, date);
                msg.setId(aLong);
                return Optional.of(msg);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Message> findOne(Long aLong) {
        Optional<Message> optionalMsg = findOneNoReply(aLong);
        if (!optionalMsg.isPresent()) {
            return Optional.empty();
        }
        Message msg = optionalMsg.get();

        String query = "SELECT reply_id FROM messages WHERE id = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setLong(1, aLong);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long reply_id = resultSet.getLong("reply_id");
                if (reply_id != 0) {
                    Optional<Message> replyMessage = findOneNoReply(reply_id);
                    replyMessage.ifPresent(msg::setReply);
                }
            }
            return Optional.of(msg);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }



    @Override
    public Iterable<Message> findAll() {
        List<Message> messages = new ArrayList<>();
        String query = "SELECT * FROM messages";
        try (PreparedStatement statement = connection.prepareStatement(query);
        ) {
            ResultSet resultSet = statement.executeQuery();

            while(resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long from_id = resultSet.getLong("from_id");
                Long to_id = resultSet.getLong("to_id");
                LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();
                String message = resultSet.getString("message");
                Long reply_id = resultSet.getLong("reply_id");
                Utilizator from = userRepository.findOne(from_id).get();
                List<Utilizator> to = Collections.singletonList(userRepository.findOne(to_id).get());
                Message msg = new Message(from, to, message, date, findOne(reply_id).orElse(null));
                msg.setId(id);
                messages.add(msg);
            }

        } catch(SQLException e) {
            throw new RuntimeException(e);
        }
        return messages;
    }

    @Override
    public Optional<Message> save(Message entity) {

        String query = "INSERT INTO messages(from_id, to_id, date, message, reply_id) VALUES (?,?,?,?,?)";

        try(PreparedStatement statement = connection.prepareStatement(query);) {
            statement.setLong(1, entity.getFrom().getId());
            statement.setLong(2, entity.getTo().get(0).getId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getData()));
            statement.setString(4, entity.getMessage());
            if(entity.getReply() == null) {
                statement.setNull(5, Types.NULL);
            } else statement.setLong(5, entity.getReply().getId());
            statement.executeUpdate();
        } catch (SQLException e) {
            return Optional.ofNullable(entity);
        }

        return Optional.empty();
    }

    @Override
    public Optional<Message> delete(Long aLong) {
        String query = "DELETE FROM messages WHERE id = ?";

        try(PreparedStatement statement = connection.prepareStatement(query);
        ) {
            statement.setLong(1, aLong);
            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Message> update(Message entity) {
        String query = "UPDATE messages SET from_id = ?, to_id = ?, date = ?, message = ?, reply_id = ? WHERE id = ?";
        try(PreparedStatement statement = connection.prepareStatement(query);
        ) {
            statement.setLong(1, entity.getFrom().getId());
            statement.setLong(2, entity.getTo().get(0).getId());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getData()));
            statement.setString(4, entity.getMessage());
            statement.setLong(5, entity.getReply().getId());
            statement.setLong(6, entity.getId());
            statement.executeUpdate();
            return Optional.of(entity);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}