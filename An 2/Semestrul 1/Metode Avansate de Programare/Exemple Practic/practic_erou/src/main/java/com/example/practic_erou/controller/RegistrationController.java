package com.example.practic_erou.controller;

import com.example.practic_erou.domain.Oras;
import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.service.NevoieService;
import com.example.practic_erou.service.PersoanaService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class RegistrationController {

    private PersoanaService persoanaService;
    private NevoieService nevoieService;

    @FXML
    private TextField tfNume;

    @FXML
    private TextField tfPrenume;

    @FXML
    private TextField tfUsername;

    @FXML
    private PasswordField pfParola;

    @FXML
    private PasswordField pfConfirmParola;

    @FXML
    private ComboBox<Oras> cbOras;

    @FXML
    private TextField tfStrada;

    @FXML
    private TextField tfNumarStrada;

    @FXML
    private TextField tfTelefon;

    @FXML
    private Label lblMessage;

    @FXML
    private ListView<String> lvUsers;

    @FXML
    private PasswordField pfLoginPassword;

    @FXML
    public void initialize() {
        // Adaugă valorile pentru orașe în ComboBox
        cbOras.getItems().addAll(Oras.values());
    }

    public void setRegistrationService(PersoanaService persoanaService, NevoieService nevoieService) {
        this.persoanaService = persoanaService;
        this.nevoieService = nevoieService;
        loadUsers(); // Încarcă utilizatorii disponibili
    }

    private void loadUsers() {
        lvUsers.getItems().clear();
        // Obține toate persoanele din serviciu și le adaugă în ListView
        persoanaService.getAllPersoane()
                .forEach(p -> lvUsers.getItems().add(p.getUsername()));
    }

    private void redirectToAjutor(Persoana user) throws IOException {
        // Creare nouă fereastră pentru Ajutor
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/com/example/practic_erou/ajutor.fxml"));
        Scene scene = new Scene(fxmlLoader.load());

        // Configurare controller
        AjutorController controller = fxmlLoader.getController();
        controller.setNevoieService(nevoieService, persoanaService); // Setează serviciile

        // Creare și configurare Stage pentru noua fereastră
        Stage stage = new Stage();
        controller.setUtilizator(user, stage); // Setează utilizatorul conectat și titlul ferestrei

        stage.setScene(scene);
        stage.setTitle("Ajutor - " + user.getUsername()); // Titlu temporar (setat complet în setUtilizator)
        stage.show();
    }



    @FXML
    public void handleRegister() {
        if (!pfParola.getText().equals(pfConfirmParola.getText())) {
            lblMessage.setText("Parolele nu coincid!");
            return;
        }
        try {
            // Creare persoană nouă pe baza inputurilor
            Persoana p = new Persoana();
            p.setId(System.currentTimeMillis());
            p.setNume(tfNume.getText());
            p.setPrenume(tfPrenume.getText());
            p.setUsername(tfUsername.getText());
            p.setParola(pfParola.getText());
            p.setOras(cbOras.getValue() != null ? cbOras.getValue().toString() : "");
            p.setStrada(tfStrada.getText());
            p.setNumarStrada(tfNumarStrada.getText());
            p.setTelefon(tfTelefon.getText());

            // Adaugare persoană în serviciu
            persoanaService.addPersoana(p);
            lblMessage.setText("Utilizator înregistrat cu succes!");

            loadUsers(); // Reîncarcă lista de utilizatori
            redirectToAjutor(p); // Redirecționează utilizatorul
        } catch (Exception e) {
            lblMessage.setText("Eroare: " + e.getMessage());
        }
    }

    @FXML
    public void handleLogin() {
        String selectedUser = lvUsers.getSelectionModel().getSelectedItem();
        String enteredPassword = pfLoginPassword.getText();

        if (selectedUser == null) {
            lblMessage.setText("Vă rugăm să selectați un utilizator pentru login.");
            return;
        }

        // Transformă Iterable într-un Stream
        Stream<Persoana> persoaneStream = StreamSupport.stream(persoanaService.getAllPersoane().spliterator(), false);

        // Găsește utilizatorul selectat din serviciu
        Persoana user = persoaneStream
                .filter(p -> p.getUsername().equals(selectedUser))
                .findFirst()
                .orElse(null);

        if (user != null) {
            if (user.getParola().equals(enteredPassword)) {
                lblMessage.setText("Bun venit, " + selectedUser + "!");
                try {
                    redirectToAjutor(user); // Redirecționează utilizatorul
                } catch (IOException e) {
                    lblMessage.setText("Eroare la redirecționare: " + e.getMessage());
                    e.printStackTrace();
                }
            } else {
                lblMessage.setText("Parola este incorectă. Încercați din nou.");
            }
        } else {
            lblMessage.setText("Utilizatorul nu a fost găsit.");
        }
    }
}
