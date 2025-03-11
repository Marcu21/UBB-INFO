package com.example.examen_practic.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}