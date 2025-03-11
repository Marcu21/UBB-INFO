package com.example.practic_restaurant;

import com.example.practic_restaurant.controller.TableController;
import com.example.practic_restaurant.controller.StaffController;
import com.example.practic_restaurant.domain.MenuItem;
import com.example.practic_restaurant.domain.Order;
import com.example.practic_restaurant.domain.Table;
import com.example.practic_restaurant.domain.validators.MenuItemValidator;
import com.example.practic_restaurant.domain.validators.OrderValidator;
import com.example.practic_restaurant.domain.validators.TableValidator;
import com.example.practic_restaurant.repository.MenuItemDbRepository;
import com.example.practic_restaurant.repository.OrderDbRepository;
import com.example.practic_restaurant.repository.Repository;
import com.example.practic_restaurant.repository.TableDbRepository;
import com.example.practic_restaurant.service.MenuItemService;
import com.example.practic_restaurant.service.OrderService;
import com.example.practic_restaurant.service.TableService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class HelloApplication extends Application {

    private TableService tableService;
    private MenuItemService menuItemService;
    private OrderService orderService;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        System.out.println("Reading data from database");

        String username = "postgres";
        String password = "skerdix";
        String url = "jdbc:postgresql://localhost:5432/postgres";

        // Inițializează repository-urile
        Repository<Integer, Table> tableRepository = new TableDbRepository(url, username, password, new TableValidator());
        Repository<Integer, MenuItem> menuItemRepository = new MenuItemDbRepository(url, username, password, new MenuItemValidator());
        Repository<Integer, Order> orderRepository = new OrderDbRepository(url, username, password, new OrderValidator());

        // Inițializează serviciile
        tableService = new TableService(tableRepository);
        menuItemService = new MenuItemService(menuItemRepository);
        orderService = new OrderService(orderRepository);

        // Verifică dacă serviciile sunt corect inițializate
        if (orderService == null) {
            System.out.println("Error: OrderService is null in start method.");
            return;  // Ieși din funcție dacă serviciul nu este corect setat
        }

        initStaffView();
        initTableViews();
    }


    private void addTestTables() {
        tableService.addTable(new Table(1));
        tableService.addTable(new Table(2));
        tableService.addTable(new Table(3));
        System.out.println("Mesele au fost adăugate în baza de date.");
    }

    private void addTestMenuItems() {
        menuItemService.addMenuItem(new MenuItem(1, "Antreuri", "Bruschete cu rosii", 15, "RON"));
        menuItemService.addMenuItem(new MenuItem(2, "Antreuri", "Salata Caprese", 20, "RON"));
        menuItemService.addMenuItem(new MenuItem(3, "Fel Principal", "Paste cu sos pesto", 25, "RON"));
        menuItemService.addMenuItem(new MenuItem(4, "Fel Principal", "Vinete parmigiana", 25, "RON"));
        System.out.println("Produsele au fost adăugate în baza de date.");
    }


    private void initStaffView() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/com/example/practic_restaurant/StaffWindow.fxml"));
        VBox staffLayout = fxmlLoader.load();

        Stage staffStage = new Stage();
        staffStage.setTitle("Staff");
        staffStage.setScene(new Scene(staffLayout));
        staffStage.show();

        StaffController staffController = fxmlLoader.getController();

        // Asigură-te că serviciul este setat corect înainte de a continua
        if (orderService == null) {
            System.out.println("Error: OrderService is null before setting in StaffController.");
            return; // Evităm executarea continuării în cazul unui serviciu null
        }

        for(Order order : orderService.findAllOrders()) {
            System.out.println(order);
        }

        // Setăm serviciul în controller
        staffController.setOrderService(orderService);
    }


    private void initTableViews() throws IOException {
        List<Table> tables = new ArrayList<>(tableService.findAllTables());

        for (Table table : tables) {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/com/example/practic_restaurant/TableWindow.fxml"));
            VBox tableLayout = fxmlLoader.load();

            Stage tableStage = new Stage();
            tableStage.setTitle("Table " + table.getId());
            tableStage.setScene(new Scene(tableLayout));
            tableStage.show();

            TableController tableController = fxmlLoader.getController();
            tableController.setTableId(table.getId());
            tableController.setMenuItemService(menuItemService);
            tableController.setOrderService(orderService);
        }
    }

}
