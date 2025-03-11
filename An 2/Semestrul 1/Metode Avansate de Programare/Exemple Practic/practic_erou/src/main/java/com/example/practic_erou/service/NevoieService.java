package com.example.practic_erou.service;

import com.example.practic_erou.domain.Nevoie;
import com.example.practic_erou.repository.NevoieFileRepository;
import com.example.practic_erou.utils.Observable;
import com.example.practic_erou.utils.Observer;
import com.example.practic_erou.utils.events.ChangeEventType;
import com.example.practic_erou.utils.events.NevoieEntityChangeEvent;

import java.util.ArrayList;
import java.util.List;

public class NevoieService implements Observable<NevoieEntityChangeEvent> {
    private final NevoieFileRepository nevoieRepo;
    private final List<Observer<NevoieEntityChangeEvent>> observers = new ArrayList<>();

    public NevoieService(NevoieFileRepository nevoieRepo) {
        this.nevoieRepo = nevoieRepo;
    }


    public void addNevoie(Nevoie nevoie) {
        nevoieRepo.save(nevoie);
        notifyObservers(new NevoieEntityChangeEvent(ChangeEventType.ADD, nevoie));
    }


    public void updateNevoie(Nevoie nevoie) {
        nevoieRepo.update(nevoie);
        notifyObservers(new NevoieEntityChangeEvent(ChangeEventType.UPDATE, nevoie));
    }


    public void deleteNevoie(Long id) {
        nevoieRepo.findOne(id).ifPresent(nevoie -> {
            nevoieRepo.delete(id);
            notifyObservers(new NevoieEntityChangeEvent(ChangeEventType.DELETE, nevoie));
        });
    }

    public Nevoie getNevoie(Long id) {
        return nevoieRepo.findOne(id).orElse(null);
    }


    public Iterable<Nevoie> getAllNevoi() {
        return nevoieRepo.findAll();
    }


    @Override
    public void addObserver(Observer<NevoieEntityChangeEvent> e) {
        observers.add(e);
    }


    @Override
    public void removeObserver(Observer<NevoieEntityChangeEvent> e) {
        observers.remove(e);
    }


    @Override
    public void notifyObservers(NevoieEntityChangeEvent event) {
        for (Observer<NevoieEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
