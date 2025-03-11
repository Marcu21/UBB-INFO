package com.example.practic_erou.domain.validators;

import com.example.practic_erou.domain.Nevoie;

import java.time.LocalDateTime;

public class NevoieValidator implements Validator<Nevoie> {

    @Override
    public void validate(Nevoie nevolie) throws ValidationException {
        StringBuilder errors = new StringBuilder();

        if (nevolie.getTitlu() == null || nevolie.getTitlu().trim().isEmpty()) {
            errors.append("Titlul nu poate fi gol.\n");
        }

        if (nevolie.getDescriere() == null || nevolie.getDescriere().trim().isEmpty()) {
            errors.append("Descrierea nu poate fi goală.\n");
        }

        if (nevolie.getDeadline() == null || nevolie.getDeadline().isBefore(LocalDateTime.now())) {
            errors.append("Deadline-ul trebuie să fie în viitor.\n");
        }

        if (nevolie.getOmInNevoie() <= 0) {
            errors.append("ID-ul persoanei care are nevoie trebuie să fie un număr pozitiv.\n");
        }

        if (nevolie.getOmSalvator() != null && nevolie.getOmSalvator() < 0) {
            errors.append("ID-ul persoanei salvator nu poate fi negativ.\n");
        }

        if (nevolie.getStatus() == null ||
                (!nevolie.getStatus().equalsIgnoreCase("Caut erou!") &&
                        !nevolie.getStatus().equalsIgnoreCase("Erou gasit!"))){
            errors.append("Statusul trebuie să fie unul dintre: Caut erou! sau Erou gasit!.\n");
        }

        if (errors.length() > 0) {
            throw new ValidationException(errors.toString());
        }
    }
}
