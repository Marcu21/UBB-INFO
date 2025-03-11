package com.example.practic_erou.repository;

import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.domain.validators.Validator;

public class PersoanaFileRepository extends AbstractFileRepository<Long, Persoana> {

    public PersoanaFileRepository(Validator<Persoana> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Persoana lineToEntity(String line) {
        String[] tokens = line.split(";");
        Long id = Long.parseLong(tokens[0]);
        String nume = tokens[1];
        String prenume = tokens[2];
        String username = tokens[3];
        String parola = tokens[4];
        String oras = tokens[5];
        String strada = tokens[6];
        String numarStrada = tokens[7];
        String telefon = tokens[8];

        Persoana persoana = new Persoana();
        persoana.setId(id);
        persoana.setNume(nume);
        persoana.setPrenume(prenume);
        persoana.setUsername(username);
        persoana.setParola(parola);
        persoana.setOras(oras);
        persoana.setStrada(strada);
        persoana.setNumarStrada(numarStrada);
        persoana.setTelefon(telefon);

        return persoana;
    }

    @Override
    public String entityToLine(Persoana entity) {
        return String.join(";",
                String.valueOf(entity.getId()),
                entity.getNume(),
                entity.getPrenume(),
                entity.getUsername(),
                entity.getParola(),
                entity.getOras(),
                entity.getStrada(),
                entity.getNumarStrada(),
                entity.getTelefon()
        );
    }
}
