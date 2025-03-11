package com.example.practic_zboruri.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}