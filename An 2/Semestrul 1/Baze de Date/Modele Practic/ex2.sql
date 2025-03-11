CREATE DATABASE Ex2;
GO

USE Ex2;
GO

CREATE TABLE TipuriDeTren
(id_tip INT IDENTITY PRIMARY KEY,
descriere VARCHAR(500)
);

CREATE TABLE Trenuri
(id_trenuri INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
id_tip INT,
FOREIGN KEY (id_tip) REFERENCES TipuriDeTren(id_tip)
);

CREATE TABLE Statii
(id_statie INT IDENTITY PRIMARY KEY,
nume VARCHAR(100)
);

CREATE TABLE Rute
(id_ruta INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
id_tren INT FOREIGN KEY REFERENCES Trenuri(id_trenuri)
);

CREATE TABLE RuteStatii
(id_ruta INT FOREIGN KEY REFERENCES Rute(id_ruta),
id_statie INT FOREIGN KEY REFERENCES Statii(id_statie),
ora_sosirii TIME,
ora_plecarii TIME,
PRIMARY KEY(id_ruta, id_statie)
);


INSERT INTO TipuriDeTren(descriere) VALUES('tren rapid'),('tren rosu'),('regional'),('interregio')

INSERT INTO Trenuri(nume,id_tip) VALUES ('trenul unu', 1),('alt tren', 1), ('inca un tren', 2), ('trenul U', 3), ('nu mai stiu', 4)

INSERT INTO Rute(nume, id_tren) VALUES ('cluj-buc', 1), ('cluj-constanta', 2), ('baia mare-cluj', 2), ('carei-carei2', 3), ('carei-Bod', 4)

INSERT INTO Statii(nume) VALUES ('Teius'), ('Brasov'),('Cluj 2'), ('Bod'), ('statie noua')

INSERT INTO RuteStatii(id_ruta, id_statie, ora_sosirii, ora_plecarii) VALUES
(1,1, '11:11:00', '11:13:00'),
(1,2,'14:15:00','14:20:00'),
(2,1,'11:10:00', '11:12:00'),
(2,2,'14:25:00','14:30:00'),
(3,5,'19:00:00','19:02:00'),
(4,5,'16:00:00', '16:10:00'),
(5,1,'10:10:10','10:11:11'),
(5,2,'12:11:00','12:12:00'),
(5,3,'15:15:00','15:20:00'),
(5,4,'17:20:00','17:25:00'),
(5,5,'20:20:20','20:30:00')


GO
CREATE PROCEDURE UpsertRutaStatie
	@id_ruta INT,
	@id_statie INT,
	@ora_sosirii TIME,
	@ora_plecarii TIME
AS
BEGIN
	IF EXISTS(SELECT * FROM RuteStatii WHERE id_ruta = @id_ruta AND id_statie = @id_statie)
		UPDATE RuteStatii SET ora_sosirii = @ora_sosirii, ora_plecarii = @ora_plecarii WHERE id_ruta = @id_ruta AND id_statie = @id_statie
	ELSE
		INSERT RuteStatii(id_ruta, id_statie, ora_sosirii, ora_plecarii) VALUES (@id_ruta, @id_statie, @ora_sosirii, @ora_plecarii)
END
GO

SELECT * FROM RuteStatii;

EXEC UpsertRutaStatie 1, 3, '19:19:19', '20:00:00'

EXEC UpsertRutaStatie 1, 2, '16:19:19', '17:00:00'


GO
CREATE VIEW viewRuteCuToateStatiile AS
SELECT
	r.nume
FROM Rute r
INNER JOIN RuteStatii rs ON r.id_ruta = rs.id_ruta
GROUP BY r.id_ruta, r.nume
HAVING COUNT(DISTINCT rs.id_statie) = (SELECT COUNT(*) FROM Statii);

SELECT * FROM viewRuteCuToateStatiile;
