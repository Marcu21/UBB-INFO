package com.example.practic_erou;

import com.example.practic_erou.domain.Nevoie;
import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.domain.validators.NevoieValidator;
import com.example.practic_erou.domain.validators.PersoanaValidator;
import com.example.practic_erou.domain.validators.Validator;
import com.example.practic_erou.repository.NevoieFileRepository;
import com.example.practic_erou.repository.PersoanaFileRepository;

import java.time.LocalDateTime;
import java.util.Optional;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
        HelloApplication.main(args);

/*        Validator<Nevoie> nevoieValidator = new NevoieValidator();

        NevoieFileRepository nevoieRepo = new NevoieFileRepository(nevoieValidator, "C:\\Users\\emanu\\IdeaProjects\\practic_erou\\src\\main\\java\\com\\example\\practic_erou\\data\\nevoi.csv");

        try {
            Nevoie n1 = new Nevoie();
            n1.setId(1L);
            n1.setTitlu("Ajutor teme");
            n1.setDescriere("Ajutor la teme de matematică");
            n1.setDeadline(LocalDateTime.of(2025, 1, 30, 16, 0));
            n1.setomInNevoie(1737991268897L);
            n1.setOmSalvator(null);
            n1.setStatus("Caut erou!");
            nevoieRepo.save(n1);
            Nevoie n2 = new Nevoie();
            n2.setId(2L);
            n2.setTitlu("Ajutor evadare");
            n2.setDescriere("Ajuta-ma sa evadez din inchisoare");
            n2.setDeadline(LocalDateTime.of(2025, 2, 15, 20, 0));
            n2.setomInNevoie(1737991326949L);
            n2.setOmSalvator(null);
            n2.setStatus("Caut erou!");
            nevoieRepo.save(n2);
        } catch (Exception e) {
            System.out.println("Eroare la salvarea nevoii: " + e.getMessage());
        }*/



        /*Validator<Persoana> persoanaValidator = new PersoanaValidator();

        PersoanaFileRepository persoanaRepo = new PersoanaFileRepository(persoanaValidator, "C:\\Users\\emanu\\IdeaProjects\\practic_erou\\src\\main\\java\\com\\example\\practic_erou\\data\\persoane.csv");

        try {
            Persoana p1 = new Persoana();
            p1.setId(1L);
            p1.setNume("Popescu");
            p1.setPrenume("Ion");
            p1.setUsername("ipopescu");
            p1.setParola("password123");
            p1.setOras("Cluj-Napoca");
            p1.setStrada("Eroilor");
            p1.setNumarStrada("10");
            p1.setTelefon("0740000000");
            persoanaRepo.save(p1);
        } catch (Exception e) {
            System.out.println("Eroare la salvarea persoanei: " + e.getMessage());
        }


        try {
            Persoana p2 = new Persoana();
            p2.setId(2L);
            p2.setNume("Ionescu");
            p2.setPrenume("Maria");
            p2.setUsername("mionescu");
            p2.setParola("parola456");
            p2.setOras("București");
            p2.setStrada("Unirii");
            p2.setNumarStrada("20");
            p2.setTelefon("0721000001");
            persoanaRepo.save(p2);
        } catch (Exception e) {
            System.out.println("Eroare la salvarea persoanei: " + e.getMessage());
        }

        System.out.println("Persoanele salvate în repository:");
        persoanaRepo.findAll().forEach(System.out::println);

        Optional<Persoana> found = persoanaRepo.findOne(1L);
        if (found.isPresent()) {
            System.out.println("\nPersoana găsită cu ID 1:");
            System.out.println(found.get());
        } else {
            System.out.println("\nPersoana cu ID 1 nu a fost găsită.");
        }


        persoanaRepo.delete(1L);
        System.out.println("\nPersoanele după ștergerea ID-ului 1:");
        persoanaRepo.findAll().forEach(System.out::println);
        persoanaRepo.delete(2L);



        Validator<Nevoie> nevoieValidator = new NevoieValidator();

        NevoieFileRepository nevoieRepo = new NevoieFileRepository(nevoieValidator, "C:\\Users\\emanu\\IdeaProjects\\practic_erou\\src\\main\\java\\com\\example\\practic_erou\\data\\nevoi.csv");

        // Adăugăm câteva nevoi în repository
        try {
            Nevoie n1 = new Nevoie();
            n1.setId(1L);
            n1.setTitlu("Ajutor teme");
            n1.setDescriere("Ajutor la teme de matematică");
            n1.setDeadline(LocalDateTime.of(2025, 1, 30, 16, 0));
            n1.setomInNevoie(101L);
            n1.setOmSalvator(201L);
            n1.setStatus("Activ");
            nevoieRepo.save(n1);
        } catch (Exception e) {
            System.out.println("Eroare la salvarea nevoii: " + e.getMessage());
        }

        try {
            Nevoie n2 = new Nevoie();
            n2.setId(2L);
            n2.setTitlu("Transport");
            n2.setDescriere("Ajutor pentru transportul la aeroport");
            n2.setDeadline(LocalDateTime.of(2025, 2, 1, 10, 30));
            n2.setomInNevoie(102L);
            n2.setOmSalvator(202L);
            n2.setStatus("Activ");
            nevoieRepo.save(n2);
        } catch (Exception e) {
            System.out.println("Eroare la salvarea nevoii: " + e.getMessage());
        }

        // Afișăm toate nevoile din repository
        System.out.println("\nNevoile salvate în repository:");
        nevoieRepo.findAll().forEach(System.out::println);

        // Căutăm o nevoie după ID
        Optional<Nevoie> found1 = nevoieRepo.findOne(1L);
        if (found1.isPresent()) {
            System.out.println("\nNevoia găsită cu ID 1:");
            System.out.println(found1.get());
        } else {
            System.out.println("\nNevoia cu ID 1 nu a fost găsită.");
        }

        // Actualizăm o nevoie
        try {
            Nevoie n3 = new Nevoie();
            n3.setId(1L); // Același ID ca n1
            n3.setTitlu("Ajutor teme modificat");
            n3.setDescriere("Ajutor la teme de matematică - modificat");
            n3.setDeadline(LocalDateTime.of(2025, 1, 31, 18, 0));
            n3.setomInNevoie(101L);
            n3.setOmSalvator(201L);
            n3.setStatus("Rezolvat");
            Optional<Nevoie> updated = nevoieRepo.update(n3);
            if (updated.isEmpty()) {
                System.out.println("\nNevoia cu ID 1 a fost actualizată.");
            } else {
                System.out.println("\nNevoia cu ID 1 nu a fost găsită pentru actualizare.");
            }
        } catch (Exception e) {
            System.out.println("Eroare la actualizarea nevoii: " + e.getMessage());
        }

        // Ștergem o nevoie și afișăm lista actualizată
        nevoieRepo.delete(1L);
        System.out.println("\nNevoile după ștergerea ID-ului 1:");
        nevoieRepo.findAll().forEach(System.out::println);
        nevoieRepo.delete(2L);*/
    }
}
