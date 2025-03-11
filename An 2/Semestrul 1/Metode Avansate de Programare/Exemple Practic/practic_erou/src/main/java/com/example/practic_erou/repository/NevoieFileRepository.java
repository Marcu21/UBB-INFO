package com.example.practic_erou.repository;

import com.example.practic_erou.domain.Nevoie;
import com.example.practic_erou.domain.validators.Validator;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class NevoieFileRepository extends AbstractFileRepository<Long, Nevoie> {
    private static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public NevoieFileRepository(Validator<Nevoie> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    public Nevoie lineToEntity(String line) {
        String[] tokens = line.split(";");
        Long id = Long.parseLong(tokens[0]);
        String titlu = tokens[1];
        String descriere = tokens[2];
        LocalDateTime deadline = LocalDateTime.parse(tokens[3], formatter);
        Long omInNevoie = Long.parseLong(tokens[4]);
        Long omSalvator = tokens[5].isEmpty() ? null : Long.parseLong(tokens[5]); // Tratare pentru omSalvator gol
        String status = tokens[6];

        Nevoie nevolie = new Nevoie();
        nevolie.setId(id);
        nevolie.setTitlu(titlu);
        nevolie.setDescriere(descriere);
        nevolie.setDeadline(deadline);
        nevolie.setomInNevoie(omInNevoie);
        nevolie.setOmSalvator(omSalvator);
        nevolie.setStatus(status);

        return nevolie;
    }


    @Override
    public String entityToLine(Nevoie entity) {
        return entity.getId() + ";" +
                entity.getTitlu() + ";" +
                entity.getDescriere() + ";" +
                entity.getDeadline().format(formatter) + ";" +
                entity.getOmInNevoie() + ";" +
                (entity.getOmSalvator() != null ? entity.getOmSalvator() : "") + ";" + // Tratare null pentru omSalvator
                entity.getStatus();
    }

}
