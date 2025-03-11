package com.example.examen_practic.controller;

import com.example.examen_practic.domain.AdoptionCentre;
import com.example.examen_practic.domain.Animal;
import com.example.examen_practic.domain.AnimalType;
import com.example.examen_practic.service.AdoptionCentreService;
import com.example.examen_practic.service.AnimalService;
import com.example.examen_practic.utils.Observer;
import com.example.examen_practic.utils.events.AnimalChangeEvent;
import com.example.examen_practic.utils.events.ChangeEventType;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.List;
import java.util.Optional;

public class AdoptionCentreController implements Observer<AnimalChangeEvent> {
    @FXML
    private Label centreNameLabel;
    @FXML
    private Label centreLocationLabel;
    @FXML
    private Label centreCapacityLabel;
    @FXML
    private Label centreOccupancyLabel;
    @FXML
    private TableView<Animal> animalTable;
    @FXML
    private TableColumn<Animal, Integer> idColumn;
    @FXML
    private TableColumn<Animal, String> nameColumn;
    @FXML
    private TableColumn<Animal, String> typeColumn;
    @FXML
    private ComboBox<AnimalType> animalTypeComboBox;
    @FXML
    private TableColumn<Animal, Void> transferColumn;

    private AnimalService animalService;
    private AdoptionCentreService adoptionCentreService;
    private AdoptionCentre centre;

    public void setServices(AnimalService animalService, AdoptionCentreService adoptionCentreService, AdoptionCentre centre) {
        this.animalService = animalService;
        this.adoptionCentreService = adoptionCentreService;
        this.centre = centre;
        initializeView();

        animalService.addObserver(this);
    }

    private void initializeView() {
        centreNameLabel.setText("Centre: " + centre.getName());
        centreLocationLabel.setText("Location: " + centre.getLocation());
        centreCapacityLabel.setText("Capacity: " + centre.getCapacity());

        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        typeColumn.setCellValueFactory(new PropertyValueFactory<>("type"));

        setupTransferButtons();
        setupAnimalTypeFilter();
        loadAnimalsForCentre(null);
        updateOccupancy();
    }

    private void loadAnimalsForCentre(AnimalType type) {
        List<Animal> animals = animalService.getAnimalsFromAdoptionCentre(centre, type);
        animalTable.getItems().setAll(animals);
        updateOccupancy();
    }

    private void updateOccupancy() {
        int animale = animalTable.getItems().size();
        int capacity = centre.getCapacity();
        int procentaj = (int) (((double) animale / capacity) * 100);
        centreOccupancyLabel.setText("Occupancy: " + procentaj + "%");
    }

    private void setupAnimalTypeFilter() {
        animalTypeComboBox.getItems().add(null);
        animalTypeComboBox.getItems().addAll(AnimalType.values());
        animalTypeComboBox.setPromptText("All Types");

        animalTypeComboBox.setOnAction(event -> {
            AnimalType selectedType = animalTypeComboBox.getValue();
            loadAnimalsForCentre(selectedType);
        });
    }

    private void setupTransferButtons() {
        transferColumn.setCellFactory(column -> new TableCell<>() {
            @Override
            protected void updateItem(Void item, boolean empty) {
                super.updateItem(item, empty);
                if (empty) {
                    setGraphic(null);
                } else {
                    Button requestButton = new Button("Request Transfer");
                    requestButton.setOnAction(event -> sendTransferRequest(getTableView().getItems().get(getIndex())));
                    setGraphic(requestButton);
                }
            }
        });
    }

    private void sendTransferRequest(Animal animal) {
        List<AdoptionCentre> centres = adoptionCentreService.getCentresByLocation(centre.getLocation());

        for (int i = 0; i < centres.size(); i++) {
            if (centres.get(i).getId().equals(centre.getId())) {
                centres.remove(i);
                break;
            }
        }

        if (centres.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText("Nu sunt centre disponibile in aceasta locatie!");
            alert.showAndWait();
            return;
        }

        for (AdoptionCentre c : centres) {
            if (showTransferNotification(c, animal)) break;
        }
    }

    private boolean showTransferNotification(AdoptionCentre targetCentre, Animal animal) {
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Transfer Request");
        alert.setHeaderText(targetCentre.getName());
        alert.setContentText(centre.getName() + " requested to transfer " + animal.getName());

        ButtonType acceptButton = new ButtonType("Accept");
        ButtonType ignoreButton = new ButtonType("Ignore");
        alert.getButtonTypes().setAll(acceptButton, ignoreButton);

        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent() && result.get() == acceptButton) {
            animal.setCentreId(targetCentre.getId());
            animalService.updateAnimal(animal);
            return true;
        }
        return false;
    }

    @Override
    public void update(AnimalChangeEvent event) {
        Animal updatedAnimal = event.getData();

        AnimalType selectedType = animalTypeComboBox.getValue();


        if (updatedAnimal.getCentreId() == centre.getId()) {
            loadAnimalsForCentre(selectedType);
            updateOccupancy();
        }

        if (event.getOldData() != null && event.getOldData().getCentreId() == centre.getId()) {
            loadAnimalsForCentre(selectedType);
            updateOccupancy();
        }
    }

}
