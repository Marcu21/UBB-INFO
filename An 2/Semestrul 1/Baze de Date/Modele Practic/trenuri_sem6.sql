CREATE DATABASE TrenuriSeminar
GO
USE TrenuriSeminar
GO

CREATE TABLE TipuriDeTren(
id int PRIMARY KEY IDENTITY,
descriere varchar(100))

CREATE TABLE Trenuri(
id int PRIMARY KEY IDENTITY,
nume varchar(100),
tip int FOREIGN KEY REFERENCES TipuriDeTren(id))

CREATE TABLE Rute(
id int PRIMARY KEY IDENTITY,
nume varchar(100),
tren int FOREIGN KEY REFERENCES trenuri(id))

CREATE TABLE Statii(
id int PRIMARY KEY IDENTITY,
nume varchar(100))

CREATE TABLE RuteStatii(
idRuta int FOREIGN KEY REFERENCES Rute(id),
idStatie int FOREIGN KEY REFERENCES Statii(id),
oraSosirii time,
oraPlecarii time,
CONSTRAINT Pk_RuteStatii PRIMARY KEY (idRuta, idStatie))


INSERT INTO TipuriDeTren(descriere) VALUES('tren rapid'),('tren rosu'),('regional'),('interregio')

INSERT INTO Trenuri(nume,tip) VALUES ('trenul unu', 1),('alt tren', 1), ('inca un tren', 2), ('trenul U', 3), ('nu mai stiu', 4)

INSERT INTO Rute(nume, tren) VALUES ('cluj-buc', 1), ('cluj-constanta', 2), ('baia mare-cluj', 2), ('carei-carei2', 3), ('carei-Bod', 4)

INSERT INTO Statii(nume) VALUES ('Teius'), ('Brasov'),('Cluj 2'), ('Bod'), ('statie noua')

INSERT INTO RuteStatii(idRuta, idStatie, oraSosirii, oraPlecarii) VALUES
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

SELECT * FROM Trenuri;
SELECT * FROM TipuriDeTren;
SELECT * FROM Rute;
SELECT * FROM Statii;
SELECT * FROM RuteStatii;

GO
CREATE PROCEDURE UpsertRutaStatie
	@idRuta int,
	@idStatie int,
	@oraSosirii Time,
	@oraPlecarii Time
AS
BEGIN
	IF EXISTS(SELECT * FROM RuteStatii WHERE idRuta = @idRuta AND idStatie = @idStatie)
		UPDATE RuteStatii SET oraSosirii = @oraSosirii, oraPlecarii = @oraPlecarii WHERE idRuta = @idRuta AND idStatie = @idStatie
	ELSE
		INSERT INTO RuteStatii(idRuta, idStatie, oraSosirii, oraPlecarii) VALUES(@idRuta, @idStatie,@oraSosirii,@oraPlecarii)
END

EXEC UpsertRutaStatie 1, 3, '19:19:19', '20:00:00'

EXEC UpsertRutaStatie 1, 2, '16:19:19', '17:00:00'


CREATE VIEW RuteCuToateStatiile AS
SELECT R.nume
FROM Rute R
JOIN RuteStatii RS ON R.id = RS.idRuta
GROUP BY R.id, R.nume
HAVING COUNT(DISTINCT RS.idStatie) = (SELECT COUNT(*) FROM Statii);

SELECT * FROM RuteCuToateStatiile;
