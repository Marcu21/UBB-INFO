CREATE DATABASE SEM4_BD;
GO
USE SEM4_BD;
CREATE TABLE Sectiuni (
    cod_s INT PRIMARY KEY,
    nume NVARCHAR(150) NOT NULL,
    descriere NVARCHAR(MAX)
);

CREATE TABLE Atractii (
    cod_a INT PRIMARY KEY,
    nume NVARCHAR(150) NOT NULL,
    descriere NVARCHAR(MAX),
    varsta_min INT,
    cod_s INT NOT NULL,
    CONSTRAINT FK_Atractii_Sectiuni FOREIGN KEY (cod_s)
        REFERENCES Sectiuni (cod_s)
);

CREATE TABLE Categorii (
    cod_c INT PRIMARY KEY,
    nume NVARCHAR(100) NOT NULL
);

CREATE TABLE Vizitatori (
    cod_v INT PRIMARY KEY,
    nume NVARCHAR(150) NOT NULL,
    email NVARCHAR(150) NOT NULL,
    cod_c INT NOT NULL,
    CONSTRAINT FK_Vizitatori_Categorii FOREIGN KEY (cod_c)
        REFERENCES Categorii (cod_c)
);

CREATE TABLE Note (
    cod_a INT,
    cod_v INT,
    nota DECIMAL(3,1) CHECK (nota >= 1 AND nota <= 10),
    CONSTRAINT PK_Note PRIMARY KEY (cod_a, cod_v),
    CONSTRAINT FK_Note_Atractii FOREIGN KEY (cod_a)
        REFERENCES Atractii (cod_a),
    CONSTRAINT FK_Note_Vizitatori FOREIGN KEY (cod_v)
        REFERENCES Vizitatori (cod_v)
);


INSERT INTO Categorii (cod_c, nume)
VALUES
(1, 'Adult'),
(2, 'Copil'),
(3, 'Pensionar');

INSERT INTO Sectiuni (cod_s, nume, descriere)
VALUES
(1, 'Rollercoasters', 'Atractii recomandate pentru iubitorii de adrenalina'),
(2, 'Zona pentru copii', 'Atractii sigure si distractive pentru copii'),
(3, 'Zona acvatica', 'Tobogane si piscine pentru toate varstele');

INSERT INTO Atractii (cod_a, nume, descriere, varsta_min, cod_s)
VALUES
(1, 'Silver Star', 'Rollercoaster de viteza mare', 12, 1),
(2, 'Carusel', 'Carusel traditional pentru toate varstele', 3, 2),
(3, 'Lac', 'Plimbare relaxanta pe apa', 0, 3),
(4, 'Figuri de ceara', 'Intalneste copia fidela a manelistului Dani Mocanu si a generalului Nicolae Ciuca', 7, 4);

INSERT INTO Vizitatori (cod_v, nume, email, cod_c)
VALUES
(1, 'Ion Popescu', 'ion.popescu@yahoo.com', 1),
(2, 'Maria Ionescu', 'maria.ionescu@gmail.com', 2),
(3, 'Victor Vasile', 'victor.vasile@hotmail.com', 3);

INSERT INTO Note (cod_a, cod_v, nota)
VALUES
(1, 1, 9.5),
(2, 2, 8.0),
(1, 3, 7.5),
(3, 1, 8.5),
(4, 1, 10),
(4, 2, 10),
(4, 3, 10);

INSERT INTO Sectiuni (cod_s, nume, descriere)
VALUES (4, 'Expozitie de figuri de ceara', 'Descopera figuri de ceara ale celebritatilor');

Select * from Atractii
Select * from Vizitatori
Select * from Note
Select * from Sectiuni
Select * from Categorii


--1) Să se creeze o funcție scalară care primește ca parametru numele unei categorii și returnează codul acesteia.
GO
CREATE FUNCTION dbo.GetCategoriaCod (@NumeCategoria NVARCHAR(100))
RETURNS INT
AS
BEGIN
    DECLARE @CodCategoria INT;
    SELECT @CodCategoria = cod_c FROM Categorii WHERE nume = @NumeCategoria;
    RETURN @CodCategoria;
END;
GO

--2) Creați un trigger care împiedică execuția operațiilor de ștergere din tabelul Categorii și afișează un mesaj corespunzător. 
CREATE TRIGGER PreventDeleteOnCategorii
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
    RAISERROR ('Operatia de stergere a fost blocata.', 16, 1);
END;
GO

--3) Creați un view care afișează toate înregistrările din tabelul Categorii al căror nume este egal cu ‘pensionari’ sau ‘copii’.
CREATE VIEW VizualizareCategoriiSpecifice AS
SELECT *
FROM Categorii
WHERE nume IN ('Pensionar', 'Copil');
GO

--4) Creați un view care afișează toate înregistrările din tabelul Sectiuni al căror nume începe cu litera Z.
CREATE VIEW VizualizareSectiuniZ AS
SELECT *
FROM Sectiuni
WHERE nume LIKE 'Z%';
GO

--5) Creați o funcție de tip inline table valued care returnează toate înregistrările din tabelul Sectiuni al căror nume se termină cu o literă dată ca parametru de intrare și au cel puțin două caractere.
CREATE FUNCTION dbo.GetSectiuniByLastChar (@LastChar CHAR(1))
RETURNS TABLE
AS
RETURN (
    SELECT *
    FROM Sectiuni
    WHERE nume LIKE '%' + @LastChar
      AND LEN(nume) >= 2
);
GO

--6) Creați un view care care afișează numele vizitatorilor, nota și numele atracției
CREATE VIEW VizualizareVizitatoriNoteAtractii AS
SELECT 
    V.nume AS NumeVizitator,
    N.nota AS Nota,
    A.nume AS NumeAtractie
FROM 
    Vizitatori V
JOIN 
    Note N ON V.cod_v = N.cod_v
JOIN 
    Atractii A ON N.cod_a = A.cod_a;
GO


--1)
SELECT dbo.GetCategoriaCod('Adult') AS CodCategoria;
GO

--2)
DELETE FROM Categorii WHERE cod_c = 1;
SELECT * FROM Categorii;

--3)
SELECT * FROM VizualizareCategoriiSpecifice;

--4)
SELECT * FROM VizualizareSectiuniZ;

--5)
SELECT * FROM dbo.GetSectiuniByLastChar('a');


--6)
SELECT * FROM VizualizareVizitatoriNoteAtractii;
