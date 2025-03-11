package com.example.practic_restaurant.domain;

import java.time.LocalDateTime;
import java.util.List;

public class Order extends Entity<Integer> {
    private Table table;
    private List<MenuItem> menuItems;
    private LocalDateTime date;
    private OrderStatus status;

    public Order(Integer id, Table table, List<MenuItem> menuItems, LocalDateTime date, OrderStatus status) {
        super(id);
        this.table = table;
        this.menuItems = menuItems;
        this.date = date;
        this.status = status;
    }

    public Table getTable() {
        return table;
    }

    public void setTable(Table table) {
        this.table = table;
    }

    public List<MenuItem> getMenuItems() {
        return menuItems;
    }

    public void setMenuItems(List<MenuItem> menuItems) {
        this.menuItems = menuItems;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public OrderStatus getStatus() {
        return status;
    }

    public void setStatus(OrderStatus status) {
        this.status = status;
    }
}
