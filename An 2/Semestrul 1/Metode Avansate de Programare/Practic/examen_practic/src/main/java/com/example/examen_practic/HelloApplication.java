package com.example.examen_practic;

import com.example.examen_practic.controller.AdoptionCentreController;
import com.example.examen_practic.domain.AdoptionCentre;
import com.example.examen_practic.domain.Animal;
import com.example.examen_practic.domain.AnimalType;
import com.example.examen_practic.domain.validators.AdoptionCentreValidator;
import com.example.examen_practic.domain.validators.AnimalValidator;
import com.example.examen_practic.repository.AdoptionCentreDbRepository;
import com.example.examen_practic.repository.AnimalDbRepository;
import com.example.examen_practic.service.AdoptionCentreService;
import com.example.examen_practic.service.AnimalService;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        System.out.println("Hello, World!");
        System.out.println("Reading data from database");

        String username = "postgres";
        String password = "skerdix";
        String url = "jdbc:postgresql://localhost:5432/examen";

        AdoptionCentreDbRepository adoptionCentreRepo = new AdoptionCentreDbRepository(url, username, password, new AdoptionCentreValidator());
        AnimalDbRepository animalRepo = new AnimalDbRepository(url, username, password, new AnimalValidator());

        AdoptionCentreService adoptionCentreService = new AdoptionCentreService(adoptionCentreRepo);
        AnimalService animalService = new AnimalService(animalRepo);


        for (AdoptionCentre centre : adoptionCentreService.getAllAdoptionCentres()) {
            openCentreWindow(centre, adoptionCentreService, animalService);
        }
    }

    private void openCentreWindow(AdoptionCentre centre, AdoptionCentreService adoptionCentreService, AnimalService animalService) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/examen_practic/adoption_centre_view.fxml"));
            Scene scene = new Scene(loader.load());

            AdoptionCentreController controller = loader.getController();
            controller.setServices(animalService, adoptionCentreService, centre);

            Stage stage = new Stage();
            stage.setTitle("Adoption Centre - " + centre.getName());
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void addData(AdoptionCentreService adoptionCentreService, AnimalService animalService) {
            AdoptionCentre centru1 = new AdoptionCentre(3, "Centrul Animalelor", "Cluj", 10);
            AdoptionCentre centru2 = new AdoptionCentre(4, "Visul Animalelor", "Cluj", 20);

            adoptionCentreService.addAdoptionCentre(centru1);
            adoptionCentreService.addAdoptionCentre(centru2);

            Animal animal1 = new Animal(4, "Elemer", 3, AnimalType.DOG);
            Animal animal2 = new Animal(5, "Tzuni", 3, AnimalType.CAT);
            Animal animal3 = new Animal(6, "Brutus", 4, AnimalType.DOG);

            animalService.addAnimal(animal1);
            animalService.addAnimal(animal2);
            animalService.addAnimal(animal3);

    }


    public static void main(String[] args) {
        launch();
    }
}