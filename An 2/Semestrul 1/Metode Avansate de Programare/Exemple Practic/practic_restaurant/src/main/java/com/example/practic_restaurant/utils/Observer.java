package com.example.practic_restaurant.utils;


import com.example.practic_restaurant.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}