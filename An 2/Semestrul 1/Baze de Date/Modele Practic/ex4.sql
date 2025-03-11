CREATE DATABASE Ex4;
GO

USE Ex4;
GO

CREATE TABLE Categorii
(id_categorie INT IDENTITY PRIMARY KEY,
nume VARCHAR(100)
);

CREATE TABLE Vizitatori
(id_vizitator INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
email VARCHAR(150),
id_categorie INT FOREIGN KEY REFERENCES Categorii(id_categorie)
);

CREATE TABLE Sectiuni
(id_sectiune INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
descriere VARCHAR(200),
);

CREATE TABLE Atractii
(id_atractie INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
descriere VARCHAR(200),
varsta_minima INT,
id_sectiune INT FOREIGN KEY REFERENCES Sectiuni(id_sectiune)
);

CREATE TABLE Note
(id_vizitator INT FOREIGN KEY REFERENCES Vizitatori(id_vizitator),
id_atractie INT FOREIGN KEY REFERENCES Atractii(id_atractie),
nota DECIMAL(3,1) CHECK (nota >=1 AND nota <=10),
PRIMARY KEY(id_vizitator, id_atractie)
);

INSERT INTO Categorii (nume)
VALUES
('Adult'),
('Copil'),
('Pensionar');

INSERT INTO Sectiuni (nume, descriere)
VALUES
('Rollercoasters', 'Atractii recomandate pentru iubitorii de adrenalina'),
('Zona pentru copii', 'Atractii sigure si distractive pentru copii'),
('Zona acvatica', 'Tobogane si piscine pentru toate varstele');

INSERT INTO Atractii (nume, descriere, varsta_minima, id_sectiune)
VALUES
('Silver Star', 'Rollercoaster de viteza mare', 12, 1),
('Carusel', 'Carusel traditional pentru toate varstele', 3, 2),
('Lac', 'Plimbare relaxanta pe apa', 0, 3),
('Figuri de ceara', 'Intalneste copia fidela a manelistului Dani Mocanu si a generalului Nicolae Ciuca', 7, 4);

INSERT INTO Vizitatori (nume, email, id_categorie)
VALUES
('Ion Popescu', 'ion.popescu@yahoo.com', 1),
('Maria Ionescu', 'maria.ionescu@gmail.com', 2),
('Victor Vasile', 'victor.vasile@hotmail.com', 3);

INSERT INTO Note (id_atractie, id_vizitator, nota)
VALUES
(9, 1, 9.5),
(10, 2, 8.0),
(9, 3, 7.5),
(11, 1, 8.5),
(12, 1, 10),
(12, 2, 10),
(12, 3, 10);

INSERT INTO Sectiuni (nume, descriere)
VALUES ('Expozitie de figuri de ceara', 'Descopera figuri de ceara ale celebritatilor');

Select * from Atractii
Select * from Vizitatori
Select * from Note
Select * from Sectiuni
Select * from Categorii


-- functie scalara care primeste ca parametru numele unei categorii si returneaza id-ul acesteia
GO
CREATE FUNCTION getIdCategorie(@nume_categorie VARCHAR(100))
RETURNS INT
AS
BEGIN
	DECLARE @id INT;
	SELECT @id = c.id_categorie
	FROM Categorii c
	WHERE c.nume = @nume_categorie
	RETURN @id
END
GO

SELECT dbo.getIdCategorie('Pensionar') AS id_categorie


-- trigger care impiedica stergerea din tabelul Categorii si afiseaza un mesaj de eroare
GO
CREATE TRIGGER triggerDeleteCategorii
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
    RAISERROR ('Operatia de stergere a fost blocata.', 16, 1);
END;
GO

DELETE FROM Categorii WHERE id_categorie = 1;
SELECT * FROM Categorii;


-- view care afiseaza toate inregistrarile din tabelul Categorii care au numele egal cu 'Pensionar' sau 'Copil'
GO
CREATE VIEW viewCopilPensionar AS
SELECT * FROM Categorii WHERE nume = 'Copil' OR nume = 'Pensionar'
GO

SELECT * FROM viewCopilPensionar;



-- view care afiseaza toate inregistrarile din tabelul Sectiuni al caror nume incepe cu litera Z
GO
CREATE OR ALTER VIEW viewSectiuniZ AS
SELECT * FROM Sectiuni WHERE nume LIKE 'Z%'
GO

SELECT * FROM ViewSectiuniZ;



-- functie de tip inline table valued care returneaza toate inregistrarile din tabelul Sectiuni al caror nume se termina cu o litera data ca parametru si au cel putin doua caractere
GO
CREATE FUNCTION getSectiuniLitera(@litera CHAR)
RETURNS TABLE
AS
RETURN
(
SELECT * FROM Sectiuni WHERE LEN(nume) >= 2 AND nume LIKE '%' + @litera
)
GO

SELECT * FROM dbo.getSectiuniLitera('a');



-- view care care afiseaza numele vizitatorilor, nota si numele atractiei
GO
CREATE VIEW viewNote AS
SELECT
	v.nume AS Nume_Vizitator,
	n.nota AS Nota,
	a.nume AS Nume_Atractie
FROM Note n
JOIN Vizitatori v ON n.id_vizitator = v.id_vizitator
JOIN Atractii a ON n.id_atractie = a.id_atractie
GO

SELECT * FROM viewNote