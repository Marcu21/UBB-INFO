package com.example.practic_vacante.service;

import com.example.practic_vacante.domain.Hotel;
import com.example.practic_vacante.domain.HotelOccupancyDTO;
import com.example.practic_vacante.repository.Repository;
import com.example.practic_vacante.utils.Observable;
import com.example.practic_vacante.utils.Observer;
import com.example.practic_vacante.utils.events.ChangeEventType;
import com.example.practic_vacante.utils.events.HotelEntityChangeEvent;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class HotelService implements Observable<HotelEntityChangeEvent> {
    private final Repository<Double, Hotel> hotelRepo;
    private final List<Observer<HotelEntityChangeEvent>> observers = new ArrayList<>();

    public HotelService(Repository<Double, Hotel> hotelRepo) {
        this.hotelRepo = hotelRepo;
    }

    public void addHotel(Hotel hotel) {
        hotelRepo.save(hotel);
        notifyObservers(new HotelEntityChangeEvent(ChangeEventType.ADD, hotel));
    }

    public void updateHotel(Hotel hotel) {
        hotelRepo.update(hotel);
        notifyObservers(new HotelEntityChangeEvent(ChangeEventType.UPDATE, hotel));
    }

    public void deleteHotel(Double id) {
        hotelRepo.findOne(id).ifPresent(hotel -> {
            hotelRepo.delete(id);
            notifyObservers(new HotelEntityChangeEvent(ChangeEventType.DELETE, hotel));
        });
    }

    public Hotel getHotel(Double id) {
        return hotelRepo.findOne(id).orElse(null);
    }

    public Iterable<Hotel> getAllHotels() {
        return hotelRepo.findAll();
    }

    @Override
    public void addObserver(Observer<HotelEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<HotelEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(HotelEntityChangeEvent event) {
        for (Observer<HotelEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }


    public List<String> getAllLocations() {
        List<String> locations = new ArrayList<>();
        hotelRepo.findAll().forEach(hotel -> {
            String location = hotel.getLocationName();
            if (!locations.contains(location)) {
                locations.add(location);
            }
        });
        return locations;
    }



}
