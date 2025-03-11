CREATE DATABASE Ex3;
GO

USE Ex3;
GO

CREATE TABLE TipuriDeRestaurante
(id_tip INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
descriere VARCHAR(300)
);

CREATE TABLE Orase
(id_oras INT IDENTITY PRIMARY KEY,
nume VARCHAR(100)
);

CREATE TABLE Restaurante
(id_restaurant INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
adresa VARCHAR(200),
telefon VARCHAR(15),
id_oras INT FOREIGN KEY REFERENCES Orase(id_oras),
id_tip INT FOREIGN KEY REFERENCES TipuriDeRestaurante(id_tip)
);

CREATE TABLE Utilizator
(id_utilizator INT IDENTITY PRIMARY KEY,
nume_utilizator VARCHAR(100),
email VARCHAR(100),
parola VARCHAR(100)
);

CREATE TABLE Rating
(id_utilizator INT FOREIGN KEY REFERENCES Utilizator(id_utilizator),
id_restaurant INT FOREIGN KEY REFERENCES Restaurante(id_restaurant),
nota DECIMAL(3,1),
PRIMARY KEY(id_utilizator, id_restaurant)
);

INSERT INTO Orase(nume) VALUES 
('Carei'),('Satu-Mare'),('Cluj')
INSERT INTO TipuriDeRestaurante(nume, descriere) VALUES 
('fast-food', 'rapid si gustos'),('pizzerie', 'cea mai buna pizza'), ('restaurant', 'specific italian')
INSERT INTO Restaurante(nume, adresa, telefon, id_oras, id_tip) VALUES
('kfc','str careiului', '123', 2, 1),
('class','bulevard transilvania', '144', 2, 2),
('bizzarre','str vasile lucaciu', '333', 1, 3),
('grande', 'str 1 decembrie', '444', 1, 2),
('gyro','piata avram iancu', '555', 1, 1),
('mc', 'str careiului', '421', 2, 1),
('tolouse','piata unirii', '1111', 3, 3),
('marty','piata unirii', '2222', 3, 3)
INSERT INTO Utilizator(nume_utilizator, email, parola) VALUES
('manufermecatu21', 'manuferm21@yahoo.com', 'manutalent'),
('alexbastanu', 'alexbastan@yahoo.com', 'alexbbb'),
('marcutancu', 'marcutanc@yahoo.com', 'marcutitan')
INSERT INTO Rating(id_utilizator, id_restaurant, nota) VALUES
(1, 1, 9.8),
(1, 2, 9.2),
(1, 3, 5.0),
(1, 4, 4.1),
(1, 7, 9.9),
(1, 8, 10.0),
(2, 1, 3.3),
(3, 1, 8.7),
(3, 6, 9.2)


SELECT * FROM Rating;

GO
CREATE PROCEDURE UpsertRating
	@id_utilizator INT,
	@id_restaurant INT,
	@nota DECIMAL(3,1)
AS
BEGIN
	IF EXISTS(SELECT * FROM Rating WHERE id_restaurant = @id_restaurant AND id_utilizator = @id_utilizator)
		UPDATE Rating SET nota = @nota WHERE id_restaurant = @id_restaurant AND id_utilizator = @id_utilizator
	ELSE
		INSERT INTO Rating(id_utilizator, id_restaurant, nota) VALUES (@id_utilizator, @id_restaurant, @nota)
END

EXEC UpsertRating 1, 1, 9.9
EXEC UpsertRating 1, 5, 3

GO
CREATE OR ALTER FUNCTION getDetalii(@email VARCHAR(100))
RETURNS TABLE
AS
RETURN
(
SELECT
	t.nume AS TIP,
	r.nume AS RESTAURANT,
	r.telefon AS TELEFON,
	o.nume AS ORAS,
	ra.nota AS NOTA,
	u.nume_utilizator AS NumeUtilizator,
	u.email AS EMAIL
FROM Utilizator u
JOIN Rating ra ON u.id_utilizator = ra.id_utilizator
JOIN Restaurante r ON ra.id_restaurant = r.id_restaurant
JOIN Orase o ON r.id_oras = o.id_oras
JOIN TipuriDeRestaurante t ON r.id_tip = t.id_tip
WHERE u.email = @email
)

GO
SELECT * FROM getDetalii('manuferm21@yahoo.com')