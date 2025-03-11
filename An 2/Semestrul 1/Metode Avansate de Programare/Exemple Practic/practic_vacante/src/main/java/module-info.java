module com.example.practic_vacante {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens com.example.practic_vacante to javafx.fxml;
    exports com.example.practic_vacante;
}