package com.example.guiex1.services;

import com.example.guiex1.domain.FriendRequestsDetail;
import com.example.guiex1.domain.FriendshipRequest;
import com.example.guiex1.domain.Prietenie;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.FriendshipRequestsEntityChangeEvent;
import com.example.guiex1.utils.events.PrietenieEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class FriendshipRequestService implements Observable<FriendshipRequestsEntityChangeEvent> {
    private Repository<Long, FriendshipRequest> friendshipRequestRepository;
    private PrietenieService prietenieService;
    private UtilizatorService utilizatorService;
    private List<Observer<FriendshipRequestsEntityChangeEvent>> observers = new ArrayList<>();

    public FriendshipRequestService(Repository<Long, FriendshipRequest> friendshipRequestRepository, PrietenieService prietenieService, UtilizatorService utilizatorService) {
        this.friendshipRequestRepository = friendshipRequestRepository;
        this.prietenieService = prietenieService;
        this.utilizatorService = utilizatorService;
    }

    public boolean sendFriendRequest(Long senderId, Long receiverId) {
        if (senderId.equals(receiverId)) {
            throw new IllegalArgumentException("You cannot send a friend request to yourself.");
        }

        Iterable<FriendshipRequest> existingRequests = friendshipRequestRepository.findAll();
        for (FriendshipRequest request : existingRequests) {
            if (request.getSenderId().equals(senderId) && request.getReceiverId().equals(receiverId) && "pending".equals(request.getStatus())) {
                throw new IllegalArgumentException("A request already exists.");
            }
        }

        Iterable<Prietenie> friendships = prietenieService.getAllPrietenii();
        for (Prietenie friendship : friendships) {
            if ((friendship.getFirstUserId().equals(senderId) && friendship.getSecondUserId().equals(receiverId)) ||
                    (friendship.getFirstUserId().equals(receiverId) && friendship.getSecondUserId().equals(senderId))) {
                throw new IllegalArgumentException("You are already friends.");
            }
        }

        FriendshipRequest newRequest = new FriendshipRequest(senderId, receiverId, "pending", LocalDateTime.now());
        notifyObservers(new FriendshipRequestsEntityChangeEvent(ChangeEventType.ADD, newRequest));
        return friendshipRequestRepository.save(newRequest).isEmpty();
    }

    public boolean acceptFriendRequest(Long senderId, Long receiverId) {
        Iterable<FriendshipRequest> existingRequests = friendshipRequestRepository.findAll();
        for (FriendshipRequest request : existingRequests) {
            if (request.getSenderId().equals(senderId) && request.getReceiverId().equals(receiverId) && "pending".equals(request.getStatus())) {
                request.setStatus("accepted");
                friendshipRequestRepository.update(request);
                prietenieService.addPrietenie(new Prietenie(senderId, receiverId, LocalDateTime.now()));
                notifyObservers(new FriendshipRequestsEntityChangeEvent(ChangeEventType.UPDATE, request));
                return true;
            }
        }
        return false;
    }

    public List<FriendshipRequest> getAllFriendRequestsForUser(Long userId) {
        List<FriendshipRequest> requestsForUser = new ArrayList<>();
        Iterable<FriendshipRequest> allRequests = friendshipRequestRepository.findAll();

        for (FriendshipRequest request : allRequests) {
            if (request.getReceiverId().equals(userId)) {
                requestsForUser.add(request);
            }
        }

        return requestsForUser;
    }

    public List<FriendRequestsDetail> getFriendRequestsDetailsForUser(Long userId) {
        List<FriendRequestsDetail> detailsList = new ArrayList<>();
        Iterable<FriendshipRequest> requests = getAllFriendRequestsForUser(userId);

        for (FriendshipRequest request : requests) {
            Utilizator sender = utilizatorService.findOne(request.getSenderId());
            Utilizator receiver = utilizatorService.findOne(request.getReceiverId());
            Utilizator relevantUser = (sender.getId().equals(userId)) ? receiver : sender;

            if (relevantUser != null) {
                FriendRequestsDetail detail = new FriendRequestsDetail(relevantUser, request.getStatus(), request.getRequestDate());
                detailsList.add(detail);
            }
        }

        return detailsList;
    }

    @Override
    public void addObserver(Observer<FriendshipRequestsEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<FriendshipRequestsEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(FriendshipRequestsEntityChangeEvent t) {
        observers.forEach(observer -> observer.update(t));
    }
}
