package com.example.practic_zboruri.service;

import com.example.practic_zboruri.domain.Flight;
import com.example.practic_zboruri.domain.Ticket;
import com.example.practic_zboruri.repository.Repository;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class TicketService {
    private final Repository<Long, Ticket> ticketRepo;

    public TicketService(Repository<Long, Ticket> ticketRepo) {
        this.ticketRepo = ticketRepo;
    }

    public void addTicket(Ticket ticket) {
        ticketRepo.save(ticket);
    }

    public void updateTicket(Ticket ticket) {
        ticketRepo.update(ticket);
    }

    public void deleteTicket(Long id) {
        ticketRepo.findOne(id).ifPresent(ticket -> ticketRepo.delete(id));
    }

    public Ticket getTicket(Long id) {
        return ticketRepo.findOne(id).orElse(null);
    }

    public Iterable<Ticket> getAllTickets() {
        return ticketRepo.findAll();
    }

    public ArrayList<Ticket> getTicketsByUsername(String username){
        ArrayList<Ticket> tickets = new ArrayList<>();
        for(Ticket ticket : ticketRepo.findAll()){
            if(ticket.getUsername().equals(username)){
                tickets.add(ticket);
            }
        }

        return tickets;
    }

    public ArrayList<Ticket> getTicketsByDate(LocalDate date){
        ArrayList<Ticket> tickets = new ArrayList<>();
        for(Ticket ticket : ticketRepo.findAll()){
            if(ticket.getPurchaseTime().toLocalDate().equals(date)){
                tickets.add(ticket);
            }
        }

        return tickets;
    }
    
}
