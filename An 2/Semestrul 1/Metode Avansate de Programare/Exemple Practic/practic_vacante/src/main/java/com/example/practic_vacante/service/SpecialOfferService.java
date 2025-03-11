package com.example.practic_vacante.service;

import com.example.practic_vacante.domain.SpecialOffer;
import com.example.practic_vacante.repository.Repository;
import com.example.practic_vacante.utils.Observable;
import com.example.practic_vacante.utils.Observer;
import com.example.practic_vacante.utils.events.ChangeEventType;
import com.example.practic_vacante.utils.events.SpecialOfferEntityChangeEvent;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class SpecialOfferService implements Observable<SpecialOfferEntityChangeEvent> {
    private final Repository<Double, SpecialOffer> specialOfferRepo;
    private final List<Observer<SpecialOfferEntityChangeEvent>> observers = new ArrayList<>();
    private final List<SearchRecord> activeSearches = new ArrayList<>();
    private record SearchRecord(String location, LocalDate startDate, LocalDate endDate) {}


    public void recordSearch(String location, LocalDate startDate, LocalDate endDate) {
        activeSearches.add(new SearchRecord(location, startDate, endDate));
        notifyObservers(new SpecialOfferEntityChangeEvent(ChangeEventType.UPDATE, null));
    }

    public long getMatchingUsers(String location, LocalDate startDate, LocalDate endDate) {
        return activeSearches.stream()
                .filter(search -> search.location().equals(location))
                .filter(search -> search.startDate().equals(startDate) && search.endDate().equals(endDate))
                .count() - 1; // Excludem utilizatorul curent
    }


    public SpecialOfferService(Repository<Double, SpecialOffer> specialOfferRepo) {
        this.specialOfferRepo = specialOfferRepo;
    }

    public void addSpecialOffer(SpecialOffer specialOffer) {
        specialOfferRepo.save(specialOffer);
        notifyObservers(new SpecialOfferEntityChangeEvent(ChangeEventType.ADD, specialOffer));
    }

    public void updateSpecialOffer(SpecialOffer specialOffer) {
        specialOfferRepo.update(specialOffer);
        notifyObservers(new SpecialOfferEntityChangeEvent(ChangeEventType.UPDATE, specialOffer));
    }

    public void deleteSpecialOffer(Double id) {
        specialOfferRepo.findOne(id).ifPresent(specialOffer -> {
            specialOfferRepo.delete(id);
            notifyObservers(new SpecialOfferEntityChangeEvent(ChangeEventType.DELETE, specialOffer));
        });
    }

    public SpecialOffer getSpecialOffer(Double id) {
        return specialOfferRepo.findOne(id).orElse(null);
    }

    public Iterable<SpecialOffer> getAllSpecialOffers() {
        return specialOfferRepo.findAll();
    }

    public List<SpecialOffer> getAvailableOffersForClient(int fidelityGrade) {
        return StreamSupport.stream(specialOfferRepo.findAll().spliterator(), false) // Convertim Iterable în Stream
                .filter(offer -> offer.getPercents() < fidelityGrade) // Verificăm fidelityGrade
                .filter(offer -> LocalDate.now().isBefore(offer.getEndDate())) // Ofertele nu sunt expirate
                .collect(Collectors.toList());
    }

    @Override
    public void addObserver(Observer<SpecialOfferEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<SpecialOfferEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(SpecialOfferEntityChangeEvent event) {
        for (Observer<SpecialOfferEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
