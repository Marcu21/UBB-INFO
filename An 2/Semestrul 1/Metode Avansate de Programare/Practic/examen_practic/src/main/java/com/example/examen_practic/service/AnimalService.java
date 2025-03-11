package com.example.examen_practic.service;

import com.example.examen_practic.domain.AdoptionCentre;
import com.example.examen_practic.domain.Animal;
import com.example.examen_practic.domain.AnimalType;
import com.example.examen_practic.repository.AnimalDbRepository;
import com.example.examen_practic.utils.Observable;
import com.example.examen_practic.utils.Observer;
import com.example.examen_practic.utils.events.AnimalChangeEvent;
import com.example.examen_practic.utils.events.ChangeEventType;

import java.util.ArrayList;
import java.util.List;

public class AnimalService implements Observable<AnimalChangeEvent> {
    private final AnimalDbRepository repository;
    private final List<Observer<AnimalChangeEvent>> observers = new ArrayList<>();

    public AnimalService(AnimalDbRepository repository) {
        this.repository = repository;
    }

    public void addAnimal(Animal animal) {
        repository.save(animal);
        notifyObservers(new AnimalChangeEvent(ChangeEventType.ADD, animal));
    }

    public void updateAnimal(Animal animal) {
        Animal oldAnimal = getAnimal(animal.getId());
        if (oldAnimal != null) {
            repository.update(animal);
            notifyObservers(new AnimalChangeEvent(ChangeEventType.UPDATE, animal, oldAnimal));
        }
    }

    public void deleteAnimal(Integer id) {
        Animal oldAnimal = getAnimal(id);
        if (oldAnimal != null) {
            repository.delete(id);
            notifyObservers(new AnimalChangeEvent(ChangeEventType.DELETE, oldAnimal));
        }
    }

    public Animal getAnimal(Integer id) {
        return repository.findOne(id).orElse(null);
    }

    public Iterable<Animal> getAllAnimals() {
        return repository.findAll();
    }

    public List<Animal> getAnimalsFromAdoptionCentre(AdoptionCentre centre, AnimalType type) {
        return repository.findByCentreAndType(centre.getId(), type);
    }

    @Override
    public void addObserver(Observer<AnimalChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<AnimalChangeEvent> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(AnimalChangeEvent event) {
        for (Observer<AnimalChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
