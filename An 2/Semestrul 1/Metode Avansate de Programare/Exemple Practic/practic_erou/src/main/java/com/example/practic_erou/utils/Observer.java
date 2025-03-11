package com.example.practic_erou.utils;


import com.example.practic_erou.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}