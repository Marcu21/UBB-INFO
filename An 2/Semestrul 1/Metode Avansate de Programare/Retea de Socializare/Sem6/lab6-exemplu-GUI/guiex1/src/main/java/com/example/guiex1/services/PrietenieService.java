package com.example.guiex1.services;

import com.example.guiex1.domain.FriendDetail;
import com.example.guiex1.domain.Prietenie;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.PrietenieDbRepository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.PrietenieEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.StreamSupport;

public class PrietenieService implements Observable<PrietenieEntityChangeEvent> {
    private  Repository<Long, Utilizator> utilizatorRepository;
    private PrietenieDbRepository prietenieRepository;
    private List<Observer<PrietenieEntityChangeEvent>> observers = new ArrayList<>();

    public PrietenieService(PrietenieDbRepository prietenieRepository, Repository<Long, Utilizator> utilizatorRepository) {
        this.prietenieRepository = prietenieRepository;
        this.utilizatorRepository = utilizatorRepository;
    }

    public Prietenie addPrietenie(Prietenie prietenie) {
        if (prietenieRepository.save(prietenie).isEmpty()) {
            notifyObservers(new PrietenieEntityChangeEvent(ChangeEventType.ADD, prietenie));
            return null;
        }
        return prietenie;
    }

    public Prietenie deletePrietenie(Long id) {
        Optional<Prietenie> prietenie = prietenieRepository.delete(id);
        if (prietenie.isPresent()) {
            notifyObservers(new PrietenieEntityChangeEvent(ChangeEventType.DELETE, prietenie.get()));
            return prietenie.get();
        }
        return null;
    }

    public Iterable<Prietenie> getAllPrietenii() {
        return prietenieRepository.findAll();
    }


    public Iterable<Utilizator> getFriendsForUser(Long userId) {
        Iterable<Prietenie> allFriendships = prietenieRepository.findAll();
        List<Utilizator> friends = new ArrayList<>();

        for (Prietenie prietenie : allFriendships) {
            if (prietenie.getFirstUserId().equals(userId)) {
                Utilizator friend = utilizatorRepository.findOne(prietenie.getSecondUserId()).orElse(null);
                if (friend != null) friends.add(friend);
            } else if (prietenie.getSecondUserId().equals(userId)) {
                Utilizator friend = utilizatorRepository.findOne(prietenie.getFirstUserId()).orElse(null);
                if (friend != null) friends.add(friend);
            }
        }

        return friends;
    }

    public List<FriendDetail> getFriendDetailsForUser(Long userId) {
        Iterable<Prietenie> allFriendships = prietenieRepository.findAll();
        List<FriendDetail> friendDetails = new ArrayList<>();

        for (Prietenie prietenie : allFriendships) {
            if (prietenie.getFirstUserId().equals(userId) || prietenie.getSecondUserId().equals(userId)) {
                Long friendId = prietenie.getFirstUserId().equals(userId) ? prietenie.getSecondUserId() : prietenie.getFirstUserId();
                Utilizator friend = utilizatorRepository.findOne(friendId).orElse(null);
                if (friend != null) {
                    FriendDetail detail = new FriendDetail(friend, prietenie.getFriendsFrom());
                    friendDetails.add(detail);
                }
            }
        }

        return friendDetails;
    }

    @Override
    public void addObserver(Observer<PrietenieEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<PrietenieEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(PrietenieEntityChangeEvent t) {
        observers.forEach(observer -> observer.update(t));
    }

    public Page<Prietenie> findAllOnPage(Pageable pageable) {
        return prietenieRepository.findAllOnPage(pageable);
    }

    public Page<Prietenie> findFriendshipsForUserOnPage(Long userId, Pageable pageable) {
        return prietenieRepository.findAllByUserIdOnPage(userId, pageable);
    }

}
