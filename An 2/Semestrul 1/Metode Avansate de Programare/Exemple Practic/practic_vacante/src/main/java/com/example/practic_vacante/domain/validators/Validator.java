package com.example.practic_vacante.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}