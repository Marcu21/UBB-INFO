﻿namespace lab9_map;

public interface Container
{
    Task Remove();
    void Add(Task task);
    int Size();
    bool IsEmpty();
}