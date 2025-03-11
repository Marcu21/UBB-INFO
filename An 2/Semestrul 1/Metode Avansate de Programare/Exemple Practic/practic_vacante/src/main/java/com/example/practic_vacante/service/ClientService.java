package com.example.practic_vacante.service;

import com.example.practic_vacante.domain.Client;
import com.example.practic_vacante.repository.Repository;
import com.example.practic_vacante.utils.Observable;
import com.example.practic_vacante.utils.Observer;
import com.example.practic_vacante.utils.events.ChangeEventType;
import com.example.practic_vacante.utils.events.ClientEntityChangeEvent;

import java.util.ArrayList;
import java.util.List;

public class ClientService implements Observable<ClientEntityChangeEvent> {
    private final Repository<Long, Client> clientRepo;
    private final List<Observer<ClientEntityChangeEvent>> observers = new ArrayList<>();

    public ClientService(Repository<Long, Client> clientRepo) {
        this.clientRepo = clientRepo;
    }

    public void addClient(Client client) {
        clientRepo.save(client);
        notifyObservers(new ClientEntityChangeEvent(ChangeEventType.ADD, client));
    }

    public void updateClient(Client client) {
        clientRepo.update(client);
        notifyObservers(new ClientEntityChangeEvent(ChangeEventType.UPDATE, client));
    }

    public void deleteClient(Long id) {
        clientRepo.findOne(id).ifPresent(client -> {
            clientRepo.delete(id);
            notifyObservers(new ClientEntityChangeEvent(ChangeEventType.DELETE, client));
        });
    }

    public Client getClient(Long id) {
        return clientRepo.findOne(id).orElse(null);
    }

    public Iterable<Client> getAllClients() {
        return clientRepo.findAll();
    }

    @Override
    public void addObserver(Observer<ClientEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<ClientEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(ClientEntityChangeEvent event) {
        for (Observer<ClientEntityChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
