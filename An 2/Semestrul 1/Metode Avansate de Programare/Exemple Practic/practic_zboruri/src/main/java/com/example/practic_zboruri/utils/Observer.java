package com.example.practic_zboruri.utils;


import com.example.practic_zboruri.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}