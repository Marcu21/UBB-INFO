CREATE DATABASE Ex1;
GO

USE Ex1;

GO

CREATE TABLE Producatori
(producator_id INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
siteweb VARCHAR(500)
);

CREATE TABLE TipDeserturi
(tipdesert_id INT IDENTITY PRIMARY KEY,
nume VARCHAR(100)
);

CREATE TABLE Deserturi
(desert_id INT IDENTITY PRIMARY KEY,
modpreparare VARCHAR(500),
pret DECIMAL(10,2),
calorii INT,
producator_id INT,
tipdesert_id INT,
FOREIGN KEY (producator_id) REFERENCES Producatori(producator_id),
FOREIGN KEY (tipdesert_id) REFERENCES TipDeserturi(tipdesert_id)
);

CREATE TABLE Clienti
(client_id INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
email VARCHAR(300),
datanasterii DATE
);

CREATE TABLE Achizitii
(client_id INT,
desert_id INT,
cantitate INT,
PRIMARY KEY(client_id, desert_id),
FOREIGN KEY (client_id) REFERENCES Clienti(client_id),
FOREIGN KEY (desert_id) REFERENCES Deserturi(desert_id)
);

ALTER TABLE Deserturi
ADD nume varchar(200);


GO
CREATE PROCEDURE UpsertAchizitie
	@cod_client INT,
	@cod_desert INT,
	@cantitate INT
AS
BEGIN
	IF EXISTS(SELECT 1 FROM Achizitii WHERE client_id = @cod_client AND desert_id = @cod_desert)
		UPDATE Achizitii
		SET cantitate = @cantitate
		WHERE client_id = @cod_client AND desert_id = @cod_desert
	ELSE
		INSERT INTO Achizitii(client_id, desert_id, cantitate) VALUES (@cod_client, @cod_desert, @cantitate)
END


SELECT * FROM Achizitii;
EXEC UpsertAchizitie 1, 1, 6;
EXEC UpsertAchizitie 1, 2, 5;





GO
CREATE OR ALTER VIEW viewTot
AS
SELECT
	p.nume AS Producator,
	d.nume AS Desert,
	d.calorii,
	a.cantitate,
	c.nume AS Client
FROM Producatori p
INNER JOIN Deserturi d ON p.producator_id = d.producator_id
INNER JOIN Achizitii a ON d.desert_id = a.desert_id
INNER JOIN Clienti c ON a.client_id = c.client_id
WHERE c.nume LIKE 'A%'

GO

SELECT * FROM viewTot;

GO
CREATE FUNCTION getAll()
RETURNS TABLE
AS
RETURN
(
	SELECT
	p.nume AS Producator,
	d.nume AS Desert,
	d.calorii,
	a.cantitate,
	c.nume AS Client
FROM Producatori p
INNER JOIN Deserturi d ON p.producator_id = d.producator_id
INNER JOIN Achizitii a ON d.desert_id = a.desert_id
INNER JOIN Clienti c ON a.client_id = c.client_id
WHERE c.nume LIKE 'A%'
)
GO

SELECT * FROM getAll()




INSERT INTO Producatori(nume,siteweb) VALUES ('Patiseria Ana', 'www.patiseria-ana.ro');
INSERT INTO Producatori(nume,siteweb) VALUES ('Patiseria Cristela', 'www.patiseria-cristela.com');
INSERT INTO Producatori(nume,siteweb) VALUES ('Dulciuri Bune', 'www.dulciuri-bune.ro');

INSERT INTO TipDeserturi(nume) VALUES ('Prajituri');
INSERT INTO TipDeserturi(nume) VALUES ('Torturi');
INSERT INTO TipDeserturi(nume) VALUES ('Inghetata');
INSERT INTO TipDeserturi(nume) VALUES ('Patiserie');

INSERT INTO Deserturi(nume,modpreparare,pret,calorii,producator_id,tipdesert_id) VALUES ('Croissant cu ciocolata', 'Se foloseste foietaj si ciocolata', 8.50, 300, 1, 4);
INSERT INTO Deserturi(nume,modpreparare,pret,calorii,producator_id,tipdesert_id) VALUES ('Eclere', 'N-am nicio idee', 16.00, 400, 2, 1);
INSERT INTO Deserturi(nume,modpreparare,pret,calorii,producator_id,tipdesert_id) VALUES ('Tort de ciocolata', 'Se foloseste ce trebuie pentru tort si ciocolata', 88.50, 900, 3, 2);
INSERT INTO Deserturi(nume,modpreparare,pret,calorii,producator_id,tipdesert_id) VALUES ('Inghetata de ciocolata', 'Multa ciocolata', 19.00, 500, 1, 3);


INSERT INTO Clienti(nume,email,datanasterii) VALUES ('Emanuel Marcu', 'emanuel.marcu@yahoo.com', '2004-08-21');
INSERT INTO Clienti(nume,email,datanasterii) VALUES ('Alex Danciu', 'alex.danciu@yahoo.com', '2004-06-19');
INSERT INTO Clienti(nume,email,datanasterii) VALUES ('Raul Parau', 'raul.parau@yahoo.com', '2004-10-10');


INSERT INTO Achizitii(client_id, desert_id, cantitate) VALUES (1, 1, 2);
INSERT INTO Achizitii(client_id, desert_id, cantitate) VALUES (1, 3, 1);
INSERT INTO Achizitii(client_id, desert_id, cantitate) VALUES (2, 2, 4);
INSERT INTO Achizitii(client_id, desert_id, cantitate) VALUES (3, 4, 3);