module com.example.practic_erou {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.practic_erou to javafx.fxml;
    exports com.example.practic_erou;
}