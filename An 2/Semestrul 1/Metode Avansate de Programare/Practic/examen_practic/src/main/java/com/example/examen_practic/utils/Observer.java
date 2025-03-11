package com.example.examen_practic.utils;


import com.example.examen_practic.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}