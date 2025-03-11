package com.example.practic_zboruri.service;

import com.example.practic_zboruri.domain.Flight;
import com.example.practic_zboruri.repository.Repository;
import com.example.practic_zboruri.utils.Observable;
import com.example.practic_zboruri.utils.Observer;
import com.example.practic_zboruri.utils.events.ChangeEventType;
import com.example.practic_zboruri.utils.events.FlightChangeEventType;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FlightService implements Observable<FlightChangeEventType> {
    private final Repository<Long, Flight> flightRepo;
    private final List<Observer<FlightChangeEventType>> observers = new ArrayList<>();


    public FlightService(Repository<Long, Flight> flightRepo) {
        this.flightRepo = flightRepo;
    }

    public void addFlight(Flight flight) {
        flightRepo.save(flight);
        notifyObservers(new FlightChangeEventType(ChangeEventType.ADD, flight));
    }

    public void updateFlight(Flight flight) {
        flightRepo.update(flight);
        notifyObservers(new FlightChangeEventType(ChangeEventType.UPDATE, flight));
    }

    public void deleteFlight(Long id) {
        flightRepo.findOne(id).ifPresent(flight -> {
            flightRepo.delete(id);
            notifyObservers(new FlightChangeEventType(ChangeEventType.DELETE, flight));
        });
    }

    public Flight getFlight(Long id) {
        return flightRepo.findOne(id).orElse(null);
    }

    public Iterable<Flight> getAllFlights() {
        return flightRepo.findAll();
    }

    public ArrayList<Flight> getFlightsByFilter(String from, String to, LocalDate departureDate) {
        ArrayList<Flight> flights = new ArrayList<>();
        for (Flight flight : flightRepo.findAll()) {
            if (flight.getFrom().equals(from) && flight.getTo().equals(to) && flight.getDepartureTime().toLocalDate().equals(departureDate)) {
                flights.add(flight);
            }
        }
        return flights;
    }

    public ArrayList<String> getToLocations() {
        ArrayList<String> flights = new ArrayList<>();
        for (Flight flight : flightRepo.findAll()) {
            if(!flights.contains(flight.getTo())) {
                flights.add(flight.getTo());
            }
        }
        return flights;
    }

    public ArrayList<String> getFromLocations() {
        ArrayList<String> flights = new ArrayList<>();
        for (Flight flight : flightRepo.findAll()) {
            if(!flights.contains(flight.getFrom())) {
                flights.add(flight.getFrom());
            }
        }
        return flights;
    }

    @Override
    public void addObserver(Observer<FlightChangeEventType> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<FlightChangeEventType> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(FlightChangeEventType event) {
        for (Observer<FlightChangeEventType> observer : observers) {
            observer.update(event);
        }
    }
}
