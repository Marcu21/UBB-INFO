package com.example.practic_zboruri.service;

import com.example.practic_zboruri.domain.Client;
import com.example.practic_zboruri.repository.Repository;

import java.util.List;

public class ClientService {
    private final Repository<Long, Client> clientRepo;

    public ClientService(Repository<Long, Client> clientRepo) {
        this.clientRepo = clientRepo;
    }

    public void addClient(Client client) {
        clientRepo.save(client);
    }

    public void updateClient(Client client) {
        clientRepo.update(client);
    }

    public void deleteClient(Long id) {
        clientRepo.findOne(id).ifPresent(client -> clientRepo.delete(id));
    }

    public Client getClient(Long id) {
        return clientRepo.findOne(id).orElse(null);
    }

    public Iterable<Client> getAllClients() {
        return clientRepo.findAll();
    }

    public Client login(String username)
    {
        for(Client c : getAllClients())
        {
            if(c.getUsername().equals(username))
                return c;
        }
        return null;
    }
}
