package com.example.practic_restaurant.controller;

import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.domain.Order;
import com.example.practic_restaurant.service.OrderService;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Comparator;
import java.util.stream.Collectors;
import com.example.practic_restaurant.utils.Observer;
import com.example.practic_restaurant.utils.events.OrderChangeEvent;

import javafx.scene.control.cell.PropertyValueFactory;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Comparator;
import java.util.stream.Collectors;

public class StaffController implements Observer<OrderChangeEvent> {

    @FXML
    private TableView<Order> ordersTable;
    @FXML
    private TableColumn<Order, Integer> tableColumn;
    @FXML
    private TableColumn<Order, String> dateColumn;
    @FXML
    private TableColumn<Order, String> itemsColumn;

    private OrderService orderService;

    public void setOrderService(OrderService orderService) {
        this.orderService = orderService;
        this.orderService.addObserver(this); // Înregistrează controller-ul ca observer
        configureTableColumns(); // Configurarea coloanelor pentru tabel
        loadOrders();
    }

    private void configureTableColumns() {
        // Configurează coloana pentru ID-ul mesei
        tableColumn.setCellValueFactory(cellData -> new SimpleIntegerProperty(cellData.getValue().getTable().getId()).asObject());

        // Configurează coloana pentru data comenzii
        dateColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                cellData.getValue().getDate().format(DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm"))
        ));

        // Configurează coloana pentru produsele comandate
        itemsColumn.setCellValueFactory(cellData -> new SimpleStringProperty(
                cellData.getValue().getMenuItems().stream()
                        .map(MenuItem::getItem)
                        .collect(Collectors.joining(", "))
        ));
    }

    private void loadOrders() {
        updateOrders();
    }

    private void updateOrders() {
        List<Order> sortedOrders = ((List<Order>) orderService.findAllOrders())
                .stream()
                .sorted(Comparator.comparing(Order::getDate))
                .collect(Collectors.toList());

        ordersTable.getItems().setAll(sortedOrders);
        ordersTable.refresh(); // Asigură-te că tabelul se actualizează
    }

    @Override
    public void update(OrderChangeEvent event) {
        // Actualizează tabelul atunci când o comandă nouă este plasată
        updateOrders();
    }
}
