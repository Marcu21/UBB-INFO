package com.example.practic_restaurant.service;

import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.repository.Repository;

import java.util.Optional;
import java.util.Set;

public class MenuItemService {
    private Repository<Integer, MenuItem> menuItemRepository;

    public MenuItemService(Repository<Integer, MenuItem> menuItemRepository) {
        this.menuItemRepository = menuItemRepository;
    }

    public Optional<MenuItem> findMenuItemById(Integer id) {
        return menuItemRepository.findOne(id);
    }

    public Set<MenuItem> findAllMenuItems() {
        return (Set<MenuItem>) menuItemRepository.findAll();
    }

    public boolean addMenuItem(MenuItem menuItem) {
        Optional<MenuItem> existingMenuItem = menuItemRepository.findOne(menuItem.getId());
        if (!existingMenuItem.isPresent()) {
            menuItemRepository.save(menuItem);
            return true;
        }
        return false;
    }

    public boolean deleteMenuItem(Integer id) {
        Optional<MenuItem> menuItem = menuItemRepository.findOne(id);
        if (menuItem.isPresent()) {
            menuItemRepository.delete(id);
            return true;
        }
        return false;
    }

    public boolean updateMenuItem(MenuItem menuItem) {
        Optional<MenuItem> existingMenuItem = menuItemRepository.findOne(menuItem.getId());
        if (existingMenuItem.isPresent()) {
            menuItemRepository.update(menuItem);
            return true;
        }
        return false;
    }
}
