package com.example.examen_practic.service;

import com.example.examen_practic.domain.AdoptionCentre;
import com.example.examen_practic.repository.AdoptionCentreDbRepository;

import java.util.List;

public class AdoptionCentreService {
    private final AdoptionCentreDbRepository repository;

    public AdoptionCentreService(AdoptionCentreDbRepository repository) {
        this.repository = repository;
    }

    public void addAdoptionCentre(AdoptionCentre centre) {
        repository.save(centre);
    }

    public void updateAdoptionCentre(AdoptionCentre centre) {
        repository.update(centre);
    }

    public void deleteAdoptionCentre(Integer id) {
        if (repository.findOne(id).isPresent()) {
            repository.delete(id);
        }
    }

    public AdoptionCentre getAdoptionCentre(Integer id) {
        return repository.findOne(id).orElse(null);
    }

    public Iterable<AdoptionCentre> getAllAdoptionCentres() {
        return repository.findAll();
    }

    public List<AdoptionCentre> getCentresByLocation(String location) {
        return repository.findByLocation(location);
    }

}
