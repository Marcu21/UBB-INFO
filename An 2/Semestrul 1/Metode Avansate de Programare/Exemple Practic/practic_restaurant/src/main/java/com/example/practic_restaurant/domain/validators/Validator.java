package com.example.practic_restaurant.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}