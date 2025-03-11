package com.example.practic_erou.domain.validators;

import com.example.practic_erou.domain.Persoana;

public class PersoanaValidator implements Validator<Persoana> {

    @Override
    public void validate(Persoana persoana) throws ValidationException {
        StringBuilder errors = new StringBuilder();

        if (persoana.getNume() == null || persoana.getNume().trim().isEmpty()) {
            errors.append("Numele nu poate fi gol.\n");
        }

        if (persoana.getPrenume() == null || persoana.getPrenume().trim().isEmpty()) {
            errors.append("Prenumele nu poate fi gol.\n");
        }

        if (persoana.getUsername() == null || persoana.getUsername().trim().isEmpty()) {
            errors.append("Username-ul nu poate fi gol.\n");
        }

        if (persoana.getParola() == null || persoana.getParola().trim().length() < 6) {
            errors.append("Parola trebuie să aibă cel puțin 6 caractere.\n");
        }

        if (persoana.getOras() == null || persoana.getOras().trim().isEmpty()) {
            errors.append("Orașul nu poate fi gol.\n");
        }

        if (persoana.getStrada() == null || persoana.getStrada().trim().isEmpty()) {
            errors.append("Strada nu poate fi goală.\n");
        }

        if (persoana.getNumarStrada() == null || persoana.getNumarStrada().trim().isEmpty()) {
            errors.append("Numărul străzii nu poate fi gol.\n");
        }

        if (persoana.getTelefon() == null || !persoana.getTelefon().matches("\\d{10}")) {
            errors.append("Telefonul trebuie să conțină exact 10 cifre.\n");
        }

        if (errors.length() > 0) {
            throw new ValidationException(errors.toString());
        }
    }
}
