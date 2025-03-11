package com.example.practic_restaurant.service;

import com.example.practic_restaurant.domain.Order;
import com.example.practic_restaurant.domain.OrderStatus;
import com.example.practic_restaurant.repository.Repository;
import com.example.practic_restaurant.utils.Observable;
import com.example.practic_restaurant.utils.Observer;
import com.example.practic_restaurant.utils.events.ChangeEventType;
import com.example.practic_restaurant.utils.events.OrderChangeEvent;

import java.util.ArrayList;
import java.util.List;

public class OrderService implements Observable<OrderChangeEvent> {
    private Repository<Integer, Order> orderRepository;
    private List<Observer<OrderChangeEvent>> observers = new ArrayList<>();

    public OrderService(Repository<Integer, Order> orderRepository) {
        this.orderRepository = orderRepository;
    }

    // Adăugarea unei comenzi noi
    public void placeOrder(Order order) {
        // Salvăm comanda
        orderRepository.save(order);

        // Notificăm observatorii despre adăugarea comenzii
        OrderChangeEvent event = new OrderChangeEvent(ChangeEventType.ADD, order);
        notifyObservers(event);
    }

    // Actualizarea statusului comenzii
    public void updateOrderStatus(int orderId, OrderStatus status) {
        // Extragem comanda folosind findOne, fără Optional
        Order order = orderRepository.findOne(orderId).orElse(null);

        if (order != null) {
            order.setStatus(status);
            orderRepository.update(order);

            // Notificăm observatorii despre actualizarea statusului
            OrderChangeEvent event = new OrderChangeEvent(ChangeEventType.UPDATE, order);
            notifyObservers(event);
        }
    }

    // Găsirea unei comenzi după ID
    public Order findOrderById(int orderId) {
        return orderRepository.findOne(orderId).orElse(null);
    }

    // Găsirea tuturor comenzilor
    public Iterable<Order> findAllOrders() {
        return orderRepository.findAll();
    }

    // Ștergerea unei comenzi
    public void deleteOrder(int orderId) {
        Order order = orderRepository.findOne(orderId).orElse(null);

        if (order != null) {
            // Notificăm observatorii despre ștergerea comenzii
            OrderChangeEvent event = new OrderChangeEvent(ChangeEventType.DELETE, order);
            notifyObservers(event);
        }
    }

    @Override
    public void addObserver(Observer<OrderChangeEvent> observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer<OrderChangeEvent> observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(OrderChangeEvent event) {
        for (Observer<OrderChangeEvent> observer : observers) {
            observer.update(event);
        }
    }
}
