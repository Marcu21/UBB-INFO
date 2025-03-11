package com.example.practic_erou.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}