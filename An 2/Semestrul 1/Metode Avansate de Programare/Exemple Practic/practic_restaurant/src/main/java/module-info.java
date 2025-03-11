module com.example.practic_restaurant {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.practic_restaurant to javafx.fxml;
    exports com.example.practic_restaurant;
}