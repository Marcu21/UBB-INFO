package com.example.practic_erou.controller;

import com.example.practic_erou.domain.Nevoie;
import com.example.practic_erou.domain.Persoana;
import com.example.practic_erou.service.NevoieService;
import com.example.practic_erou.service.PersoanaService;
import com.example.practic_erou.utils.Observer;
import com.example.practic_erou.utils.events.ChangeEventType;
import com.example.practic_erou.utils.events.NevoieEntityChangeEvent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.time.format.DateTimeFormatter;

public class AjutorController implements Observer<NevoieEntityChangeEvent> {

    @FXML
    private TableView<Nevoie> tableNevoi;

    @FXML
    private TableColumn<Nevoie, String> colTitlu;

    @FXML
    private TableColumn<Nevoie, String> colDescriere;

    @FXML
    private TableColumn<Nevoie, String> colDeadline;

    @FXML
    private TableColumn<Nevoie, String> colStatus;

    @FXML
    private TableView<Nevoie> tableFapteBune;

    @FXML
    private TableColumn<Nevoie, String> colFapteTitlu;

    @FXML
    private TableColumn<Nevoie, String> colFapteDescriere;

    @FXML
    private TableColumn<Nevoie, String> colFapteDeadline;

    @FXML
    private TextField tfTitlu;

    @FXML
    private TextArea taDescriere;

    @FXML
    private DatePicker dpDeadline;

    @FXML
    private Label lblUserInfo;


    private Persoana user; // Utilizatorul conectat
    private NevoieService nevoieService;
    private PersoanaService persoanaService;
    private String orasUtilizator; // Orașul utilizatorului conectat

    private final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    public void setNevoieService(NevoieService nevoieService, PersoanaService persoanaService) {
        this.nevoieService = nevoieService;
        this.persoanaService = persoanaService;

        // Înregistrează controller-ul ca observer pentru evenimentele din nevoieService
        this.nevoieService.addObserver(this);
    }

    public void setUtilizator(Persoana utilizator, Stage stage) {
        this.user = utilizator;
        this.orasUtilizator = utilizator.getOras();

        // Setăm titlul ferestrei
        stage.setTitle("Ajutor - " + utilizator.getUsername() + " din " + utilizator.getOras());

        // Setăm textul în Label
        lblUserInfo.setText("Conectat ca: " + utilizator.getUsername() + " | Oraș: " + utilizator.getOras());

        // Încarcă datele în tabele
        loadNevoiForOras();
        loadFapteBune();
    }


    @FXML
    public void initialize() {
        // Configurare tabel pentru nevoi disponibile
        colTitlu.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        colDescriere.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        colDeadline.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleStringProperty(cellData.getValue().getDeadline().format(formatter)));
        colStatus.setCellValueFactory(new PropertyValueFactory<>("status"));

        // Configurare tabel pentru fapte bune
        colFapteTitlu.setCellValueFactory(new PropertyValueFactory<>("titlu"));
        colFapteDescriere.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        colFapteDeadline.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleStringProperty(cellData.getValue().getDeadline().format(formatter)));
    }

    private void loadNevoiForOras() {
        if (nevoieService != null && orasUtilizator != null) {
            ObservableList<Nevoie> nevoiList = FXCollections.observableArrayList();

            nevoieService.getAllNevoi().forEach(nevoie -> {
                // Găsește persoana asociată cu această nevoie
                Persoana persoana = persoanaService.getPersoana(nevoie.getOmInNevoie());
                if (persoana != null) { // Verificăm dacă persoana există
                    // Verifică dacă orașul persoanei este același cu orașul utilizatorului curent
                    if (nevoie.getStatus().equals("Caut erou!") && !nevoie.getOmInNevoie().equals(user.getId()) &&
                            nevoie.getOmSalvator() == null &&
                            orasUtilizator.equals(persoana.getOras())) {
                        nevoiList.add(nevoie);
                    }
                }
            });

            tableNevoi.setItems(nevoiList);
        }
    }

    private void loadFapteBune() {
        if (nevoieService != null && user != null) {
            ObservableList<Nevoie> fapteBuneList = FXCollections.observableArrayList();

            // Selectează nevoile rezolvate de utilizator
            nevoieService.getAllNevoi().forEach(nevoie -> {
                if (nevoie.getOmSalvator() != null && nevoie.getOmSalvator().equals(user.getId())) {
                    fapteBuneList.add(nevoie);
                }
            });

            tableFapteBune.setItems(fapteBuneList);
        }
    }

    @FXML
    public void handlePreiaNevoie() {
        Nevoie selectedNevoie = tableNevoi.getSelectionModel().getSelectedItem();

        if (selectedNevoie == null) {
            MessageAlert.showErrorMessage(null, "Vă rugăm să selectați o nevoie din tabel.");
            return;
        }

        // Actualizează nevoia
        selectedNevoie.setOmSalvator(user.getId());
        selectedNevoie.setStatus("Erou gasit!");
        nevoieService.updateNevoie(selectedNevoie);

        // Mesaj de confirmare
        MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Succes",
                "Nevoia a fost atribuită cu succes! Sunteți eroul pentru această nevoie.");

        // Reîncarcă tabelele
        loadNevoiForOras();
        loadFapteBune(); // Actualizează tabelul de fapte bune
    }

    @FXML
    public void handleAdaugaNevoie() {
        String titlu = tfTitlu.getText();
        String descriere = taDescriere.getText();
        var deadline = dpDeadline.getValue();

        if (titlu.isEmpty() || descriere.isEmpty() || deadline == null) {
            MessageAlert.showErrorMessage(null, "Toate câmpurile trebuie completate!");
            return;
        }

        try {
            // Creare nevoie
            Nevoie nevoie = new Nevoie();
            nevoie.setId(System.currentTimeMillis()); // ID unic
            nevoie.setTitlu(titlu);
            nevoie.setDescriere(descriere);
            nevoie.setDeadline(deadline.atStartOfDay()); // Convertim LocalDate în LocalDateTime
            nevoie.setomInNevoie(user.getId()); // Setăm utilizatorul curent ca fiind persoana în nevoie
            nevoie.setOmSalvator(null); // Nu există salvator inițial
            nevoie.setStatus("Caut erou!");

            // Salvare nevoie
            nevoieService.addNevoie(nevoie);

            // Mesaj de confirmare
            MessageAlert.showMessage(null, Alert.AlertType.INFORMATION, "Succes", "Nevoia a fost adăugată cu succes!");

            // Resetare formular
            tfTitlu.clear();
            taDescriere.clear();
            dpDeadline.setValue(null);

        } catch (Exception e) {
            MessageAlert.showErrorMessage(null, "Eroare la adăugarea nevoii: " + e.getMessage());
        }
    }

    @Override
    public void update(NevoieEntityChangeEvent event) {
        // Reîncarcă tabelele la orice modificare a entităților Nevoie
        if (event.getType() == ChangeEventType.ADD || event.getType() == ChangeEventType.UPDATE || event.getType() == ChangeEventType.DELETE) {
            loadNevoiForOras();
            loadFapteBune();
        }
    }
}

