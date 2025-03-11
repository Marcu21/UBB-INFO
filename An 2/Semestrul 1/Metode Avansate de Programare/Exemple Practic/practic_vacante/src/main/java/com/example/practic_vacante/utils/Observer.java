package com.example.practic_vacante.utils;


import com.example.practic_vacante.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}