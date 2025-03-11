package com.example.practic_erou;

import com.example.practic_erou.domain.Nevoie;
import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.domain.validators.NevoieValidator;
import com.example.practic_erou.domain.validators.PersoanaValidator;
import com.example.practic_erou.domain.validators.Validator;
import com.example.practic_erou.repository.NevoieFileRepository;
import com.example.practic_erou.repository.PersoanaFileRepository;
import com.example.practic_erou.service.NevoieService;
import com.example.practic_erou.service.PersoanaService;
import com.example.practic_erou.controller.RegistrationController;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws IOException {
        // Inițializare validatori
        Validator<Persoana> persoanaValidator = new PersoanaValidator();
        Validator<Nevoie> nevoieValidator = new NevoieValidator();

        // Inițializare repository-uri
        PersoanaFileRepository persoanaRepo = new PersoanaFileRepository(persoanaValidator, "C:\\Users\\emanu\\IdeaProjects\\practic_erou\\src\\main\\java\\com\\example\\practic_erou\\data\\persoane.csv");
        NevoieFileRepository nevoieRepo = new NevoieFileRepository(nevoieValidator, "C:\\Users\\emanu\\IdeaProjects\\practic_erou\\src\\main\\java\\com\\example\\practic_erou\\data\\nevoi.csv");

        // Inițializare servicii
        PersoanaService persoanaService = new PersoanaService(persoanaRepo);
        NevoieService nevoieService = new NevoieService(nevoieRepo);

        // Încarcă fișierul FXML
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("registration.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 800); // Dimensiunea ferestrei

        // Obține controller-ul asociat fișierului FXML
        RegistrationController registrationController = fxmlLoader.getController();

        // Setează serviciile în controller
        registrationController.setRegistrationService(persoanaService, nevoieService);

        // Configurare fereastră principală
        primaryStage.setTitle("Aplicație Înregistrare și Login");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
