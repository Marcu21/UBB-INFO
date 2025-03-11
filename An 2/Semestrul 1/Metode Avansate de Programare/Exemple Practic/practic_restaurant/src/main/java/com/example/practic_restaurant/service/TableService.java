package com.example.practic_restaurant.service;

import com.example.practic_restaurant.domain.Table;
import com.example.practic_restaurant.repository.Repository;

import java.util.Optional;
import java.util.Set;

public class TableService {
    private Repository<Integer, Table> tableRepository;

    public TableService(Repository<Integer, Table> tableRepository) {
        this.tableRepository = tableRepository;
    }

    public Optional<Table> findTableById(Integer id) {
        return tableRepository.findOne(id);
    }

    public Set<Table> findAllTables() {
        return (Set<Table>) tableRepository.findAll();
    }

    public boolean addTable(Table table) {
        Optional<Table> existingTable = tableRepository.findOne(table.getId());
        if (!existingTable.isPresent()) {
            tableRepository.save(table);
            return true;
        }
        return false;
    }

    public boolean deleteTable(Integer id) {
        Optional<Table> table = tableRepository.findOne(id);
        if (table.isPresent()) {
            tableRepository.delete(id);
            return true;
        }
        return false;
    }

    public boolean updateTable(Table table) {
        Optional<Table> existingTable = tableRepository.findOne(table.getId());
        if (existingTable.isPresent()) {
            tableRepository.update(table);
            return true;
        }
        return false;
    }
}
