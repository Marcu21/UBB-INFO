package com.example.practic_erou.repository;

import java.io.*;
import java.util.Optional;

import com.example.practic_erou.domain.Entity;
import com.example.practic_erou.domain.validators.Validator;


public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E>{
    private String filename;

    public AbstractFileRepository(Validator<E> validator, String fileName) {
        super(validator);
        filename=fileName;
        loadData();
    }


    public abstract E lineToEntity(String line);
    public abstract String entityToLine(E entity);

    @Override
    public Optional<E> save(E entity) {
        Optional<E> e = super.save(entity);
        if (e.isEmpty())
            writeToFile(entity);
        return e;
    }

    private void writeToFile() {
        try  ( BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            for (E entity: entities.values()) {
                String ent = entityToLine(entity);
                writer.write(ent);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    private void writeToFile(E entity) {
        try  ( BufferedWriter writer = new BufferedWriter(new FileWriter(filename, true))){
            writer.write(entityToLine(entity));
            writer.newLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void loadData() {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                E entity = lineToEntity(line);
                super.save(entity);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    @Override
    public Optional<E> delete(ID id) {
        Optional<E> entity = super.delete(id);
        if (entity.isPresent())
            writeToFile();
        return entity;
    }

    @Override
    public Optional<E> update(E entity) {
        Optional<E> en = super.update(entity);
        if (en.isEmpty())
            writeToFile();
        return en;
    }
}

