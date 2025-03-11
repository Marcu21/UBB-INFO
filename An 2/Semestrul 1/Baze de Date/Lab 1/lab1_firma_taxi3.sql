CREATE DATABASE FirmaTaxi3;
GO
USE FirmaTaxi3;
CREATE TABLE Soferi
(cod_sofer INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
CNP VARCHAR(13),
numar_telefon VARCHAR(20)
);
CREATE TABLE Vehicule
(cod_vehicul INT PRIMARY KEY IDENTITY,
marca VARCHAR(100),
model VARCHAR(100),
an_fabricatie INT,
numar_inmatriculare VARCHAR(20)
);
CREATE TABLE Clienti
(cod_client INT PRIMARY KEY,
nume VARCHAR(100),
numar_telefon VARCHAR(20)
);
CREATE TABLE Curse
(cod_cursa INT PRIMARY KEY,
cod_sofer INT,
cod_vehicul INT,
cod_client INT,
pornire VARCHAR(100),
destinatie VARCHAR(100),
distanta DECIMAL(10,2),
cost DECIMAL(10,2),
FOREIGN KEY (cod_sofer) REFERENCES Soferi(cod_sofer),
FOREIGN KEY (cod_vehicul) REFERENCES Vehicule(cod_vehicul),
FOREIGN KEY (cod_client) REFERENCES Clienti(cod_client)
);
CREATE TABLE Tarife
(cod_tarif INT PRIMARY KEY,
pret_pornire DECIMAL(10,2),
pret_km DECIMAL(10,2)
);
CREATE TABLE Plati
(cod_plata INT PRIMARY KEY,
tip_plata VARCHAR(100),
suma DECIMAL(10,2),
data_plata DATETIME
);
CREATE TABLE Reclamatii
(cod_cursa INT PRIMARY KEY,
cod_client INT,
descriere VARCHAR(200),
data_reclamatie DATE,
FOREIGN KEY (cod_cursa) REFERENCES Curse(cod_cursa),
FOREIGN KEY (cod_client) REFERENCES Clienti(cod_client),
);
CREATE TABLE Rating
(cod_cursa INT PRIMARY KEY,
cod_client INT,
scor INT,
descriere VARCHAR(200),
FOREIGN KEY (cod_cursa) REFERENCES Curse(cod_cursa),
FOREIGN KEY (cod_client) REFERENCES Clienti(cod_client),
CONSTRAINT ck_scor CHECK (scor>=1 AND scor<=5)
);
CREATE TABLE Program_Soferi
(cod_program INT PRIMARY KEY,
cod_sofer INT,
ziua VARCHAR(10),
ora_inceput TIME,
ora_sfarsit TIME,
FOREIGN KEY (cod_sofer) REFERENCES Soferi(cod_sofer)
);
/*CREATE TABLE Statii_Taxi
(cod_statie INT PRIMARY KEY,
nume VARCHAR(100),
locatie VARCHAR(100),
);*/
CREATE TABLE Relatie_Soferi_Vehicule
(cod_relatie INT PRIMARY KEY,
cod_sofer INT,
cod_vehicul INT,
data_inceput DATETIME,
data_sfarsit DATETIME,
FOREIGN KEY (cod_sofer) REFERENCES Soferi(cod_sofer),
FOREIGN KEY (cod_vehicul) REFERENCES Vehicule(cod_vehicul)
);
--DROP TABLE Cursa
ALTER TABLE Curse
ADD cod_tarif INT,
FOREIGN KEY (cod_tarif) REFERENCES Tarife(cod_tarif);
--DROP TABLE Statii_Taxi
CREATE TABLE Garaje
(cod_garaj INT PRIMARY KEY,
nume VARCHAR(100),
locatie VARCHAR(100),
capacitate INT
);
ALTER TABLE Vehicule
ADD cod_garaj INT,
FOREIGN KEY (cod_garaj) REFERENCES Garaje(cod_garaj);
ALTER TABLE Curse
ADD cod_plata INT,
FOREIGN KEY (cod_plata) REFERENCES Plati(cod_plata);
ALTER TABLE Plati DROP COLUMN suma;
ALTER TABLE Plati DROP COLUMN data_plata;


ALTER TABLE Relatie_Soferi_Vehicule
DROP CONSTRAINT PK_Relatie_Soferi_Vehicule;

ALTER TABLE Relatie_Soferi_Vehicule
DROP COLUMN cod_relatie;

ALTER TABLE Relatie_Soferi_Vehicule
ALTER COLUMN cod_sofer INT NOT NULL;

ALTER TABLE Relatie_Soferi_Vehicule
ALTER COLUMN cod_vehicul INT NOT NULL;



ALTER TABLE Relatie_Soferi_Vehicule
ADD CONSTRAINT PK_Relatie_Soferi_Vehicule PRIMARY KEY (cod_sofer, cod_vehicul);
