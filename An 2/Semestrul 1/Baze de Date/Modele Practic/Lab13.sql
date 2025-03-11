CREATE DATABASE Lab13;
GO

USE Lab13;
GO

CREATE TABLE Producatori
(ProducatorID INT IDENTITY PRIMARY KEY,
Nume NVARCHAR(100) NOT NULL,
SiteWeb NVARCHAR(200)
);

CREATE TABLE TipDeserturi
(TipDesertID INT IDENTITY PRIMARY KEY,
Nume NVARCHAR(100) NOT NULL
);

CREATE TABLE Deserturi
(DesertID INT IDENTITY PRIMARY KEY,
Nume NVARCHAR(100) NOT NULL,
ModPreparare NVARCHAR(1000),
Pret DECIMAL(10,2) NOT NULL,
Calorii INT NOT NULL,
ProducatorID INT NOT NULL,
TipDesertID INT NOT NULL,
FOREIGN KEY (ProducatorID) REFERENCES Producatori(ProducatorID) ON DELETE CASCADE,
FOREIGN KEY (TipDesertID) REFERENCES TipDeserturi(TipDesertID) ON DELETE CASCADE
);

CREATE TABLE Clienti
(ClientID INT IDENTITY PRIMARY KEY,
Nume NVARCHAR(100) NOT NULL,
Email NVARCHAR(150) NOT NULL UNIQUE,
DataNasterii DATE NOT NULL
);

CREATE TABLE Achizitii
(AchizitieID INT IDENTITY PRIMARY KEY,
ClientID INT NOT NULL,
DesertID INT NOT NULL,
Cantitate INT NOT NULL,
FOREIGN KEY (ClientID) REFERENCES Clienti(ClientID) ON DELETE CASCADE,
FOREIGN KEY (DesertID) REFERENCES Deserturi(DesertID) ON DELETE CASCADE,
UNIQUE (ClientID, DesertID)
);


INSERT INTO Producatori(Nume,SiteWeb) VALUES ('Patiseria Ana', 'www.patiseria-ana.ro');
INSERT INTO Producatori(Nume,SiteWeb) VALUES ('Patiseria Cristela', 'www.patiseria-cristela.com');
INSERT INTO Producatori(Nume,SiteWeb) VALUES ('Dulciuri Bune', 'www.dulciuri-bune.ro');

INSERT INTO TipDeserturi(Nume) VALUES ('Prajituri');
INSERT INTO TipDeserturi(Nume) VALUES ('Torturi');
INSERT INTO TipDeserturi(Nume) VALUES ('Inghetata');
INSERT INTO TipDeserturi(Nume) VALUES ('Patiserie');

INSERT INTO Deserturi(Nume,ModPreparare,Pret,Calorii,ProducatorID,TipDesertID) VALUES ('Croissant cu ciocolata', 'Se foloseste foietaj si ciocolata', 8.50, 300, 1, 4);
INSERT INTO Deserturi(Nume,ModPreparare,Pret,Calorii,ProducatorID,TipDesertID) VALUES ('Eclere', 'N-am nicio idee', 16.00, 400, 2, 1);
INSERT INTO Deserturi(Nume,ModPreparare,Pret,Calorii,ProducatorID,TipDesertID) VALUES ('Tort de ciocolata', 'Se foloseste ce trebuie pentru tort si ciocolata', 88.50, 900, 3, 2);
INSERT INTO Deserturi(Nume,ModPreparare,Pret,Calorii,ProducatorID,TipDesertID) VALUES ('Inghetata de ciocolata', 'Multa ciocolata', 19.00, 500, 1, 3);


INSERT INTO Clienti(Nume,Email,DataNasterii) VALUES ('Emanuel Marcu', 'emanuel.marcu@yahoo.com', '2004-08-21');
INSERT INTO Clienti(Nume,Email,DataNasterii) VALUES ('Alex Danciu', 'alex.danciu@yahoo.com', '2004-06-19');
INSERT INTO Clienti(Nume,Email,DataNasterii) VALUES ('Raul Parau', 'raul.parau@yahoo.com', '2004-10-10');

INSERT INTO Achizitii(ClientID, DesertID, Cantitate) VALUES (1, 1, 2);
INSERT INTO Achizitii(ClientID, DesertID, Cantitate) VALUES (1, 3, 1);
INSERT INTO Achizitii(ClientID, DesertID, Cantitate) VALUES (2, 2, 4);
INSERT INTO Achizitii(ClientID, DesertID, Cantitate) VALUES (3, 4, 3);

SELECT * FROM Producatori;
SELECT * FROM TipDeserturi;
SELECT * FROM Deserturi;
SELECT * FROM Clienti;
SELECT * FROM Achizitii;

GO
CREATE OR ALTER PROCEDURE UpsertAchizitie
	@ClientID int,
	@DesertID int,
	@Cantitate int
AS
BEGIN
	IF EXISTS(SELECT * FROM Achizitii WHERE ClientID = @ClientID AND DesertID = @DesertID)
		UPDATE Achizitii SET Cantitate = @Cantitate WHERE ClientID = @ClientID AND DesertID = @DesertID
	ELSE
		INSERT INTO Achizitii(ClientID, DesertID, Cantitate) VALUES(@ClientID, @DesertID,@Cantitate)
END

EXEC UpsertAchizitie 1, 1, 6;
EXEC UpsertAchizitie 1, 2, 5;


-- procedura stocata care primeste un desert, un client si o cantitate si adauga desertul clientului respectiv. Daca desertul a fost deja adaugat clientului respectiv, se va actualiza cantitatea.

GO
CREATE FUNCTION GetClientDesert()
RETURNS TABLE
AS
RETURN
(
	SELECT
	P.Nume AS Producator,
	D.Nume AS Desert,
	D.Calorii,
	A.Cantitate,
	C.Nume AS Client
	FROM Achizitii A
	INNER JOIN Clienti C on A.ClientID = C.ClientID
	INNER JOIN Deserturi D ON A.DesertID = D.DesertID
    INNER JOIN Producatori P ON D.ProducatorID = P.ProducatorID
    WHERE C.Nume LIKE 'A%'
);
GO

SELECT * FROM GetClientDesert();


-- functie definita de utilizator care afiseaza numele producatorului, numele desertului, numarul de calorii, cantitatea si numele clientului pentru toti clientii al caror nume incepe cu litera ‘A’.

GO
CREATE VIEW dbo.VwAchizitiiIndexate WITH SCHEMABINDING
AS
    SELECT 
        a.AchizitieID,
        a.ClientID,
        c.Nume AS NumeClient,
        d.Nume AS NumeDesert,
        a.Cantitate,
        p.Nume AS NumeProducator
    FROM dbo.Achizitii a
    INNER JOIN dbo.Clienti c ON a.ClientID = c.ClientID
    INNER JOIN dbo.Deserturi d ON a.DesertID = d.DesertID
    INNER JOIN dbo.Producatori p ON d.ProducatorID = p.ProducatorID;
GO



CREATE UNIQUE CLUSTERED INDEX IDX_VwAchizitiiIndexate
ON dbo.VwAchizitiiIndexate (AchizitieID);
GO

SELECT * FROM VwAchizitiiIndexate WITH (NOEXPAND);