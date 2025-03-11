CREATE DATABASE Lab14_2;
GO

USE Lab14_2;
GO

CREATE TABLE Participanti
(id_participant INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
email VARCHAR(100),
data_nasterii DATE
);

CREATE TABLE Producatori
(id_producator INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
website VARCHAR(100),
telefon VARCHAR(15)
);

CREATE TABLE Pateuri
(id_pateu INT IDENTITY PRIMARY KEY,
denumire VARCHAR(100),
descriere VARCHAR(100),
calorii INT,
gramaj INT,
data_lansarii DATE,
id_producator INT FOREIGN KEY REFERENCES Producatori(id_producator)
);

CREATE TABLE Evenimente
(id_eveniment INT IDENTITY PRIMARY KEY,
data_ora DATETIME,
adresa VARCHAR(100),
sponsor_principal VARCHAR(100)
);

CREATE TABLE EvenimentePateuriParticipanti
(id_eveniment INT FOREIGN KEY REFERENCES Evenimente(id_eveniment),
id_pateu INT FOREIGN KEY REFERENCES Pateuri(id_pateu),
id_participant INT FOREIGN KEY REFERENCES Participanti(id_participant),
recenzie VARCHAR(100) NOT NULL,
PRIMARY KEY(id_eveniment, id_pateu, id_participant)
);


--procedura stocata care primeste un pate, un eveniment de degustare si un participant si adauga o recenzie pateului gustat de catre participant in cadrul evenimentului de degustare. 
--Daca recenzia exista deja, ea va fi actualizata

GO
CREATE PROCEDURE UpsertEvenimentePateuriParticipanti
	@id_pateu INT,
	@id_eveniment INT,
	@id_participant INT,
	@recenzie VARCHAR(100)
AS
BEGIN
	IF EXISTS (SELECT * FROM EvenimentePateuriParticipanti WHERE id_participant = @id_participant AND id_pateu = @id_pateu AND id_eveniment = @id_eveniment)
		UPDATE EvenimentePateuriParticipanti SET recenzie = @recenzie WHERE id_participant = @id_participant AND id_pateu = @id_pateu AND id_eveniment = @id_eveniment
	ELSE
		INSERT INTO EvenimentePateuriParticipanti(id_eveniment, id_pateu, id_participant, recenzie) VALUES (@id_eveniment, @id_pateu, @id_participant, @recenzie)
END
GO


--functie definita de utilizator care afiseaza numele producatorului, denumirea pateului, descrierea pateului, numarul de calorii  si continutul recenziei pentru 
--toate pateurile a caror denumire contine cuvantul ‘crocodil’ si a caror recenzie se incheie cu cuvantul ‘grasime’.

CREATE FUNCTION AfisareDetaliiPateuri()
RETURNS TABLE
AS
RETURN (
    SELECT 
        p.nume AS NumeProducator,
        pa.denumire AS DenumirePateu,
        pa.descriere AS DescrierePateu,
        pa.calorii AS Calorii,
        epp.recenzie AS Recenzie
    FROM 
        Producatori p
    JOIN 
        Pateuri pa ON p.id_producator = pa.id_producator
    JOIN 
        EvenimentePateuriParticipanti epp ON pa.id_pateu = epp.id_pateu
    WHERE 
        pa.denumire LIKE '%crocodil%' 
        AND epp.recenzie LIKE '% grasime'
);
GO
