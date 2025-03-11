CREATE DATABASE Lab14;
GO

USE Lab14;
GO

CREATE TABLE Participanti
(id_participant INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
telefon VARCHAR(15),
adresa VARCHAR(100)
);

CREATE TABLE Dovleci
(id_dovleac INT IDENTITY PRIMARY KEY,
descriere VARCHAR(100),
data_decorare DATE,
timp_finalizare TIME,
finalizat BIT
);

CREATE TABLE Evaluatori
(id_evaluator INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
email VARCHAR(100),
data_nasterii DATE
);

CREATE TABLE Decorari
(id_participant INT FOREIGN KEY REFERENCES Participanti(id_participant),
id_dovleac INT FOREIGN KEY REFERENCES Dovleci(id_dovleac),
descriere VARCHAR(100),
PRIMARY KEY(id_participant, id_dovleac)
);

CREATE TABLE Note
(id_evaluator INT FOREIGN KEY REFERENCES Evaluatori(id_evaluator),
id_dovleac INT FOREIGN KEY REFERENCES Dovleci(id_dovleac),
nota INT CHECK (nota >= 1 AND nota <=10),
PRIMARY KEY(id_evaluator, id_dovleac)
);


INSERT INTO Participanti(nume, telefon, adresa) VALUES
('Emanuel Marcu', '0542926489', 'Str. Mihai Viteazu 80'),
('Alex Danciu', '0124235053', 'Str. Bicaz 13'),
('Raul Parau', '099812478', 'Str. Principala Dindesti'),
('Inca cineva', '091245114', 'Str. nu stiu');

INSERT INTO Dovleci(descriere, data_decorare, timp_finalizare, finalizat) VALUES
('dovleac tare', '2025-01-15', '9:54:01', 1),
('dovleac bun', '2025-01-14', '3:13:02', 0),
('dovleac ok', '2025-01-16', '5:52:03', 1),
('dovleac mediocru', '2025-01-13', '7:24:00', 0),
('dovleac super', '2025-01-11', '4:22:12', 1),
('dovleac urat', '2025-01-16', '6:12:11', 1);

INSERT INTO Evaluatori(nume, email, data_nasterii) VALUES
('Evaluator1', 'evaluator1@yahoo.com', '2000-04-11'),
('Evaluator2', 'evaluator2@yahoo.com', '2001-05-12'),
('Evaluator3', 'evaluator3@yahoo.com', '2002-06-13'),
('Evaluator4', 'evaluator4@yahoo.com', '2003-07-14'),
('Evaluator5', 'evaluator5@yahoo.com', '2004-08-15');

INSERT INTO Decorari(id_participant, id_dovleac, descriere) VALUES
(1,4,'mult'),
(3,4,'putintel'),
(2,5,'putin'),
(2,6,'aproape tot'),
(2,7,'aproape deloc'),
(3,7,'cam tot'),
(1,8,'tot'),
(4,9,'a facut tot de unul singur');

INSERT INTO Decorari(id_participant, id_dovleac, descriere) VALUES
(3,8, 'aproape deloc');



INSERT INTO Note(id_evaluator, id_dovleac, nota) VALUES
(1, 4, 10),
(1, 5, 9),
(1, 6, 9),
(1, 7, 7),
(1, 8, 10),
(1, 9, 6),
(2, 4, 8),
(3, 5, 6),
(2, 6, 10);


--procedura stocata care primeste un participant si un dovleac si adauga descrierea activitatii de decorare a participantului asupra dovleacului. 
--Daca dovleacul a fost deja asociat participantului respectiv, descrierea activitatii de decorare va fi actualizata.

GO
CREATE PROCEDURE UpsertDecorari
	@id_participant INT,
	@id_dovleac INT,
	@descriere VARCHAR(100)
AS
BEGIN
	IF EXISTS (SELECT * FROM Decorari WHERE id_participant = @id_participant AND id_dovleac = @id_dovleac)
		UPDATE Decorari SET descriere = @descriere WHERE id_participant = @id_participant AND id_dovleac = @id_dovleac
	ELSE
		INSERT INTO Decorari(id_participant, id_dovleac, descriere) VALUES (@id_participant, @id_dovleac, @descriere)
END
GO


EXEC UpsertDecorari 1, 4, 'foarte mult'
EXEC UpsertDecorari 1, 5, 'mult'
SELECT * FROM Decorari;


-- view care afiseaza numele participantului care a decorat cei mai multi dovleci marcati ca finalizati in cadrul competitiei.

GO
CREATE OR ALTER VIEW vw_NumaruUnu AS
SELECT TOP 1 WITH TIES
	p.nume AS Nume_Participant,
	COUNT(d.id_participant) AS Numar_Decorari
FROM
	Participanti p
JOIN Decorari d ON p.id_participant = d.id_participant
JOIN Dovleci dov ON d.id_dovleac = dov.id_dovleac AND dov.finalizat = 1
GROUP BY p.nume
ORDER BY COUNT(dov.id_dovleac) DESC;
GO



SELECT * FROM vw_NumaruUnu;