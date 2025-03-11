package com.example.guiex1.controller;

import com.example.guiex1.domain.Prietenie;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.services.PrietenieService;
import com.example.guiex1.services.UtilizatorService;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.FileChooser;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UserProfileController {
    @FXML
    private ImageView profilePicture;
    @FXML
    private Label userName;
    @FXML
    private TextArea bioText;
    @FXML
    private Label friendsCount;
    @FXML
    private TableView<Utilizator> friendsTable;
    @FXML
    private TableColumn<Utilizator, String> friendsFirstNameColumn;
    @FXML
    private TableColumn<Utilizator, String> friendsLastNameColumn;
    @FXML
    private Button friendsPrevPageButton;
    @FXML
    private Button friendsNextPageButton;
    @FXML
    private Label friendsPageNumber;

    @FXML
    private Label commonFriendsCount;
    @FXML
    private TableView<Utilizator> commonFriendsTable;
    @FXML
    private TableColumn<Utilizator, String> commonFriendsFirstNameColumn;
    @FXML
    private TableColumn<Utilizator, String> commonFriendsLastNameColumn;
    @FXML
    private Button commonFriendsPrevPageButton;
    @FXML
    private Button commonFriendsNextPageButton;
    @FXML
    private Label commonFriendsPageNumber;

    @FXML
    private Button changeProfilePictureButton;
    @FXML
    private Button saveBioButton;

    private UtilizatorService utilizatorService;
    private PrietenieService prietenieService;
    private Utilizator user;
    private Utilizator mainUser;

    private int friendsCurrentPage = 0;
    private int commonFriendsCurrentPage = 0;
    private int pageSize = 2;

    public void setServices(UtilizatorService utilizatorService, PrietenieService prietenieService) {
        this.utilizatorService = utilizatorService;
        this.prietenieService = prietenieService;
    }

    public void setUser(Utilizator user) {
        this.user = user;
        updateUI();
    }

    public void setMainUser(Utilizator mainUser) {
        this.mainUser = mainUser;
    }

    @FXML
    public void initialize() {
        friendsFirstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        friendsLastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        commonFriendsFirstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        commonFriendsLastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
    }

    private void updateUI() {
        if (user != null) {
            String relativePath = user.getProfilePictureURL();
            String absoluteURL;

            if (relativePath == null || relativePath.isBlank()) {
                absoluteURL = getClass().getResource("/com/example/guiex1/images/default_profile_picture.png").toString();
            } else {
                Path imagePath = Path.of(System.getProperty("user.home"), "MyAppProfilePictures", relativePath);
                absoluteURL = imagePath.toUri().toString();
            }

            profilePicture.setImage(new Image(absoluteURL, 150, 150, true, true));
            userName.setText(user.getFirstName() + " " + user.getLastName());
            bioText.setText(user.getBio() != null ? user.getBio() : "No bio available");

            updateFriendsPage();
            if (mainUser != null) {
                updateCommonFriendsPage();
            } else {
                commonFriendsCount.setVisible(false);
                commonFriendsTable.setVisible(false);
                commonFriendsPrevPageButton.setVisible(false);
                commonFriendsNextPageButton.setVisible(false);
                commonFriendsPageNumber.setVisible(false);
            }
        }
    }

    private void updateFriendsPage() {
        Page<Prietenie> friendsPage = prietenieService.findFriendshipsForUserOnPage(user.getId(), new Pageable(friendsCurrentPage, pageSize));
        List<Prietenie> prietenii = StreamSupport.stream(friendsPage.getElementsOnPage().spliterator(), false).toList();
        List<Utilizator> friends = prietenii.stream()
                .map(prietenie -> {
                    if (prietenie.getFirstUserId().equals(user.getId())) {
                        return utilizatorService.findOne(prietenie.getSecondUserId());
                    } else {
                        return utilizatorService.findOne(prietenie.getFirstUserId());
                    }
                })
                .collect(Collectors.toList());

        friendsCount.setText("Prieteni: " + friendsPage.getTotalNumberElements());
        friendsTable.getItems().setAll(friends);

        friendsPrevPageButton.setDisable(friendsCurrentPage == 0);
        int noOfPages = (int) Math.ceil((double) friendsPage.getTotalNumberElements() / pageSize);
        friendsNextPageButton.setDisable(friendsCurrentPage + 1 >= noOfPages);
        if (noOfPages == 0) friendsPageNumber.setText((friendsCurrentPage + 1) + " / " + 1);
        else friendsPageNumber.setText((friendsCurrentPage + 1) + " / " + noOfPages);
    }

    private void updateCommonFriendsPage() {
        List<Utilizator> mainUserFriends = StreamSupport.stream(prietenieService.getFriendsForUser(mainUser.getId()).spliterator(), false)
                .collect(Collectors.toList());
        List<Utilizator> selectedUserFriends = StreamSupport.stream(prietenieService.getFriendsForUser(user.getId()).spliterator(), false)
                .collect(Collectors.toList());
        List<Utilizator> commonFriends = selectedUserFriends.stream()
                .filter(mainUserFriends::contains)
                .collect(Collectors.toList());

        int totalCommonFriends = commonFriends.size();
        int start = commonFriendsCurrentPage * pageSize;
        int end = Math.min(start + pageSize, totalCommonFriends);
        List<Utilizator> currentPageCommonFriends = commonFriends.subList(start, end);

        commonFriendsCount.setText("Prieteni Comuni: " + totalCommonFriends);
        commonFriendsTable.getItems().setAll(currentPageCommonFriends);

        commonFriendsPrevPageButton.setDisable(commonFriendsCurrentPage == 0);
        int noOfPages = (int) (Math.ceil((double) totalCommonFriends / pageSize));
        commonFriendsNextPageButton.setDisable(commonFriendsCurrentPage + 1 >= noOfPages);
        if (noOfPages == 0) commonFriendsPageNumber.setText((commonFriendsCurrentPage + 1) + " / " + 1);
        else commonFriendsPageNumber.setText((commonFriendsCurrentPage + 1) + " / " + noOfPages);
    }

    @FXML
    private void handleFriendsPrevPage() {
        friendsCurrentPage--;
        updateFriendsPage();
    }

    @FXML
    private void handleFriendsNextPage() {
        friendsCurrentPage++;
        updateFriendsPage();
    }

    @FXML
    private void handleCommonFriendsPrevPage() {
        commonFriendsCurrentPage--;
        updateCommonFriendsPage();
    }

    @FXML
    private void handleCommonFriendsNextPage() {
        commonFriendsCurrentPage++;
        updateCommonFriendsPage();
    }

    @FXML
    private void handleChangeProfilePicture() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Select a Profile Picture");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Image Files", "*.png", "*.jpg", "*.jpeg")
        );

        File selectedFile = fileChooser.showOpenDialog(null);

        if (selectedFile != null) {
            try {
                Path destinationDirectory = Path.of(System.getProperty("user.home"), "MyAppProfilePictures");
                Files.createDirectories(destinationDirectory);

                Path destinationPath = destinationDirectory.resolve(selectedFile.getName());
                Files.copy(selectedFile.toPath(), destinationPath, StandardCopyOption.REPLACE_EXISTING);

                String relativePath = selectedFile.getName();
                user.setProfilePictureURL(relativePath);

                utilizatorService.updateUtilizator(user);

                String absoluteURL = destinationPath.toUri().toString();
                profilePicture.setImage(new Image(absoluteURL));
            } catch (Exception e) {
                e.printStackTrace();
                MessageAlert.showErrorMessage(null, "Eroare la incarcarea imaginii de profil: " + e.getMessage());
            }
        }
    }

    @FXML
    private void handleSaveBio() {
        String newBio = bioText.getText();
        user.setBio(newBio);
        utilizatorService.updateUtilizator(user);
    }

    public void enableEditing() {
        bioText.setEditable(true);
        changeProfilePictureButton.setVisible(true);
        saveBioButton.setVisible(true);
    }

    public void disableEditing() {
        bioText.setEditable(false);
        changeProfilePictureButton.setVisible(false);
        saveBioButton.setVisible(false);
    }
}
