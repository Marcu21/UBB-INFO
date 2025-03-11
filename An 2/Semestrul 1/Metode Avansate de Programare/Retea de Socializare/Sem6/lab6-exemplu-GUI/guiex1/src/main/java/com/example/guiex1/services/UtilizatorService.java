package com.example.guiex1.services;



import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UtilizatorService implements Observable<UtilizatorEntityChangeEvent> {
    private Repository<Long, Utilizator> repo;
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();

    public UtilizatorService(Repository<Long, Utilizator> repo) {
        this.repo = repo;
    }


    public Utilizator addUtilizator(Utilizator user) {
        user.setPassword(hashPassword(user.getPassword()));
        for(Utilizator u:repo.findAll()){
            if(u.getEmail().equals(user.getEmail())){
                throw new RuntimeException("Exista deja un utilizator cu acest email!");
            }
        }
        if(repo.save(user).isEmpty()){
            UtilizatorEntityChangeEvent event = new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user);
            notifyObservers(event);
            return null;
        }
        return user;
    }

    public Utilizator deleteUtilizator(Long id){
        Optional<Utilizator> user=repo.delete(id);
        if (user.isPresent()) {
            notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE, user.get()));
            return user.get();
        }
        return null;
    }

    public Iterable<Utilizator> getAll(){
        return repo.findAll();
    }



    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);

    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {

        observers.stream().forEach(x->x.update(t));
    }

    public Utilizator updateUtilizator(Utilizator u) {
        Optional<Utilizator> oldUser=repo.findOne(u.getId());
        if(oldUser.isPresent()) {
            Optional<Utilizator> newUser=repo.update(u);
            if (newUser.isEmpty())
                notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, u, oldUser.get()));
            return newUser.orElse(null);
        }
        return oldUser.orElse(null);
    }

    public Utilizator findOne(Long id) {
        return repo.findOne(id).orElse(null);
    }

    public Utilizator getUtilizatorByFirstNameAndLastName(String firstName, String lastName) {
        for (Utilizator u : repo.findAll()) {
            if (u.getFirstName().equals(firstName) && u.getLastName().equals(lastName)) {
                return u;
            }
        }
        return null;
    }

    public Utilizator login(String email, String password) {
        String hashedPassword = hashPassword(password);
        for (Utilizator u : repo.findAll()) {
            System.out.println(u.getEmail() + " " + u.getPassword());
            if (u.getEmail().equals(email) && u.getPassword().equals(hashedPassword)) {
                return u;
            }
        }
        return null;
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Eroare la hash-ul parolei: " + e.getMessage());
        }
    }

    public void hashExistingPasswords() {
        for (Utilizator user : repo.findAll()) {
            if (user.getPassword().length() < 64) {
                String hashedPassword = hashPassword(user.getPassword());
                user.setPassword(hashedPassword);
                repo.update(user);
                System.out.println("Parola utilizatorului " + user.getEmail() + " a fost hash-uita.");
            }
        }
    }


}
