package com.example.practic_vacante.repository;

import com.example.practic_vacante.domain.SpecialOffer;
import com.example.practic_vacante.domain.validators.Validator;
import com.example.practic_vacante.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class SpecialOfferDbRepository implements Repository<Double, SpecialOffer> {
    private String url;
    private String username;
    private String password;
    private Validator<SpecialOffer> validator;
    private Connection connection;

    public SpecialOfferDbRepository(String url, String username, String password, Validator<SpecialOffer> validator) {
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

    private SpecialOffer createSpecialOfferFromResultSet(ResultSet resultSet) throws SQLException {
        Double id = resultSet.getDouble("special_offer_id");
        Double hotelId = resultSet.getDouble("hotel_id");
        Date startDate = resultSet.getDate("start_date");
        Date endDate = resultSet.getDate("end_date");
        int percents = resultSet.getInt("percents");

        SpecialOffer specialOffer = new SpecialOffer(id, hotelId, startDate.toLocalDate(), endDate.toLocalDate(), percents);
        specialOffer.setId(id);
        return specialOffer;
    }

    @Override
    public Optional<SpecialOffer> findOne(Double id) {
        String sql = "SELECT * FROM special_offers WHERE special_offer_id = ?";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setDouble(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Optional.of(createSpecialOfferFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Iterable<SpecialOffer> findAll() {
        Set<SpecialOffer> specialOffers = new HashSet<>();
        try (PreparedStatement statement = connection.prepareStatement("SELECT * FROM special_offers")) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                specialOffers.add(createSpecialOfferFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return specialOffers;
    }

    @Override
    public Optional<SpecialOffer> save(SpecialOffer entity) {
        validator.validate(entity);
        String sql = "INSERT INTO special_offers (special_offer_id, hotel_id, start_date, end_date, percents) VALUES (?, ?, ?, ?, ?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setDouble(1, entity.getId());
            ps.setDouble(2, entity.getHotelId());
            ps.setDate(3, Date.valueOf(entity.getStartDate()));
            ps.setDate(4, Date.valueOf(entity.getEndDate()));
            ps.setInt(5, entity.getPercents());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }

    @Override
    public Optional<SpecialOffer> delete(Double id) {
        Optional<SpecialOffer> specialOffer = findOne(id);
        if (specialOffer.isPresent()) {
            String sql = "DELETE FROM special_offers WHERE special_offer_id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setDouble(1, id);
                ps.executeUpdate();
                return specialOffer;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return Optional.empty();
    }

    @Override
    public Optional<SpecialOffer> update(SpecialOffer entity) {
        validator.validate(entity);
        String sql = "UPDATE special_offers SET hotel_id = ?, start_date = ?, end_date = ?, percents = ? WHERE special_offer_id = ?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setDouble(1, entity.getHotelId());
            ps.setDate(2, Date.valueOf(entity.getStartDate()));
            ps.setDate(3, Date.valueOf(entity.getEndDate()));
            ps.setInt(4, entity.getPercents());
            ps.setDouble(5, entity.getId());

            if (ps.executeUpdate() > 0) {
                return Optional.empty();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.of(entity);
    }
}

