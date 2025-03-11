package com.example.practic_vacante.service;

import com.example.practic_vacante.domain.Reservation;
import com.example.practic_vacante.repository.Repository;
import com.example.practic_vacante.utils.Observable;
import com.example.practic_vacante.utils.Observer;
import com.example.practic_vacante.utils.events.ChangeEventType;
import com.example.practic_vacante.utils.events.ReservationEntityChangeEvent;

import java.util.ArrayList;
import java.util.List;

public class ReservationService implements Observable<ReservationEntityChangeEvent> {
    private final Repository<Double, Reservation> reservationRepo;
    private final List<Observer<ReservationEntityChangeEvent>> observers = new ArrayList<>();

    public ReservationService(Repository<Double, Reservation> reservationRepo) {
        this.reservationRepo = reservationRepo;
    }

    public void addReservation(Reservation reservation) {
        reservationRepo.save(reservation);
        notifyObservers(new ReservationEntityChangeEvent(ChangeEventType.ADD, reservation));
    }

    public void updateReservation(Reservation reservation) {
        reservationRepo.update(reservation);
        notifyObservers(new ReservationEntityChangeEvent(ChangeEventType.UPDATE, reservation));
    }

    public void deleteReservation(Double id) {
        reservationRepo.findOne(id).ifPresent(reservation -> {
            reservationRepo.delete(id);
            notifyObservers(new ReservationEntityChangeEvent(ChangeEventType.DELETE, reservation));
        });
    }

    public Reservation getReservation(Double id) {
        return reservationRepo.findOne(id).orElse(null);
    }

    public Iterable<Reservation> getAllReservations() {
        return reservationRepo.findAll();
    }

    @Override
    public void addObserver(Observer<ReservationEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<ReservationEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(ReservationEntityChangeEvent event) {
        for (Observer<ReservationEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
