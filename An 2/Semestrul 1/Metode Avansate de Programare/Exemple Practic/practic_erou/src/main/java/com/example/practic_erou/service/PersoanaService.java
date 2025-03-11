package com.example.practic_erou.service;

import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.repository.PersoanaFileRepository;
import com.example.practic_erou.utils.Observable;
import com.example.practic_erou.utils.Observer;
import com.example.practic_erou.utils.events.ChangeEventType;
import com.example.practic_erou.utils.events.PersoanaEntityChangeEvent;

import java.util.ArrayList;
import java.util.List;

public class PersoanaService implements Observable<PersoanaEntityChangeEvent> {
    private final PersoanaFileRepository persoanaRepo;
    private final List<Observer<PersoanaEntityChangeEvent>> observers = new ArrayList<>();

    public PersoanaService(PersoanaFileRepository persoanaRepo) {
        this.persoanaRepo = persoanaRepo;
    }

    public void addPersoana(Persoana persoana) {
        persoanaRepo.save(persoana);
        notifyObservers(new PersoanaEntityChangeEvent(ChangeEventType.ADD, persoana));
    }


    public void updatePersoana(Persoana persoana) {
        persoanaRepo.update(persoana);
        notifyObservers(new PersoanaEntityChangeEvent(ChangeEventType.UPDATE, persoana));
    }


    public void deletePersoana(Long id) {
        persoanaRepo.findOne(id).ifPresent(persoana -> {
            persoanaRepo.delete(id);
            notifyObservers(new PersoanaEntityChangeEvent(ChangeEventType.DELETE, persoana));
        });
    }

    public Persoana getPersoana(Long id) {
        return persoanaRepo.findOne(id).orElse(null);
    }


    public Iterable<Persoana> getAllPersoane() {
        return persoanaRepo.findAll();
    }


    @Override
    public void addObserver(Observer<PersoanaEntityChangeEvent> e) {
        observers.add(e);
    }


    @Override
    public void removeObserver(Observer<PersoanaEntityChangeEvent> e) {
        observers.remove(e);
    }


    @Override
    public void notifyObservers(PersoanaEntityChangeEvent event) {
        for (Observer<PersoanaEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
