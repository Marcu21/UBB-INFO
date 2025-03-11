package com.example.practic_restaurant.controller;

import com.example.practic_restaurant.domain.*;
import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.service.MenuItemService;
import com.example.practic_restaurant.service.OrderService;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class TableController {

    @FXML
    private Label tableLabel;

    @FXML
    private TableView<MenuItem> antreuriTable;
    @FXML
    private TableColumn<MenuItem, String> antreuriItemColumn;
    @FXML
    private TableColumn<MenuItem, String> antreuriPriceColumn;

    @FXML
    private TableView<MenuItem> felPrincipalTable;
    @FXML
    private TableColumn<MenuItem, String> felPrincipalItemColumn;
    @FXML
    private TableColumn<MenuItem, String> felPrincipalPriceColumn;

    @FXML
    private Button placeOrderButton;

    private int tableId;
    private MenuItemService menuItemService;
    private OrderService orderService;

    public void setTableId(int id) {
        this.tableId = id;
        tableLabel.setText("Table " + id);
    }

    public void setMenuItemService(MenuItemService menuItemService) {
        this.menuItemService = menuItemService;
        loadMenu();
    }

    public void setOrderService(OrderService orderService) {
        this.orderService = orderService;
    }

    private void loadMenu() {
        List<MenuItem> menuItems = new ArrayList<>(menuItemService.findAllMenuItems());

        // Filtrăm produsele pe categorii
        List<MenuItem> antreuri = menuItems.stream()
                .filter(item -> item.getCategory().equals("Antreuri"))
                .collect(Collectors.toList());

        List<MenuItem> felPrincipal = menuItems.stream()
                .filter(item -> item.getCategory().equals("Fel Principal"))
                .collect(Collectors.toList());

        // Setăm coloanele pentru Antreuri
        antreuriItemColumn.setCellValueFactory(new PropertyValueFactory<>("item"));
        antreuriPriceColumn.setCellValueFactory(new PropertyValueFactory<>("formattedPrice"));
        antreuriTable.getItems().setAll(antreuri);
        antreuriTable.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE); // Permitem selecția multiplă

        // Setăm coloanele pentru Fel Principal
        felPrincipalItemColumn.setCellValueFactory(new PropertyValueFactory<>("item"));
        felPrincipalPriceColumn.setCellValueFactory(new PropertyValueFactory<>("formattedPrice"));
        felPrincipalTable.getItems().setAll(felPrincipal);
        felPrincipalTable.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE); // Permitem selecția multiplă
    }

    @FXML
    public void placeOrder() {
        // Obținem produsele selectate din Antreuri
        List<MenuItem> selectedAntreuri = getSelectedMenuItems(antreuriTable);

        // Obținem produsele selectate din Fel Principal
        List<MenuItem> selectedFelPrincipal = getSelectedMenuItems(felPrincipalTable);

        // Combinăm produsele selectate din ambele categorii
        List<MenuItem> selectedItems = selectedAntreuri;
        selectedItems.addAll(selectedFelPrincipal);

        // Verificăm dacă au fost selectate produse
        if (selectedItems.isEmpty()) {
            showAlert("Eroare", "Trebuie să selectezi cel puțin un produs.");
            return;
        }

        // Creăm o comandă cu produsele selectate (fără a seta ID-ul)
        Order order = new Order(
                null,  // Lasăm ID-ul să fie generat automat de baza de date
                new Table(tableId),
                selectedItems,
                LocalDateTime.now(),
                OrderStatus.PLACED
        );

        // Plasăm comanda
        orderService.placeOrder(order);

        showAlert("Succes", "Comanda a fost plasată cu succes!");
    }


    private List<MenuItem> getSelectedMenuItems(TableView<MenuItem> tableView) {
        return tableView.getSelectionModel().getSelectedItems().stream()
                .collect(Collectors.toList());
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}
