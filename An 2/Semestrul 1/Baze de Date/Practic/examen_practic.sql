CREATE DATABASE Practic;
GO

USE Practic;
GO

CREATE TABLE Tari
(id_tara INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
locuitori INT
);

CREATE TABLE Companii
(id_companie INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
data_infiintare DATE,
rating INT CHECK(rating >= 1 AND rating <=5),
id_tara INT FOREIGN KEY REFERENCES Tari(id_tara)
);

CREATE TABLE Certificari
(id_certificare INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
descriere VARCHAR(200),
data_lansarii DATE,
versiune VARCHAR(10),
nivel INT,
id_companie INT FOREIGN KEY REFERENCES Companii(id_companie)
);

CREATE TABLE Angajati
(id_angajat INT IDENTITY PRIMARY KEY,
nume VARCHAR(100),
prenume VARCHAR(100),
data_nasterii DATE,
email VARCHAR(100),
telefon VARCHAR(15)
);

CREATE TABLE CertificariAngajati
(id_certificare INT FOREIGN KEY REFERENCES Certificari(id_certificare),
id_angajat INT FOREIGN KEY REFERENCES Angajati(id_angajat),
data_examinarii DATE,
pret FLOAT,
punctaj INT NOT NULL,
PRIMARY KEY(id_certificare, id_angajat)
);



INSERT INTO Tari(nume, locuitori) VALUES
('tara1', 1000), 
('tara2', 2000), 
('tara3', 3000), 
('tara4', 4000),
('tara5', 5000);

INSERT INTO Companii(nume, data_infiintare, rating, id_tara) VALUES
('companie1', '2000-01-01', 1, 1),
('companie2', '2000-02-02', 2, 2),
('companie3', '2000-03-03', 3, 3),
('companie4', '2000-04-04', 4, 4),
('companie5', '2000-05-05', 5, 5),
('companie11', '2000-11-11', 4, 1),
('companie22', '2000-12-12', 3, 2);

INSERT INTO Certificari(nume, descriere, data_lansarii, versiune, nivel, id_companie) VALUES
('certificare1', 'aceasta este certificarea1', '2020-01-01', 'v1', 1, 1),
('certificare2', 'aceasta este certificarea2', '2020-02-02', 'v2', 1, 2),
('certificare3', 'aceasta este certificarea3', '2020-03-03', 'v3', 1, 3),
('certificare4', 'aceasta este certificarea4', '2020-04-04', 'v4', 1, 4),
('certificare5', 'aceasta este certificarea5', '2020-05-05', 'v5', 1, 5),
('certificare11', 'aceasta este certificarea11', '2020-11-11', 'v11', 11, 1),
('certificare111', 'aceasta este certificarea111', '2020-01-11', 'v111', 1, 1),
('certificare6', 'aceasta este certificarea6', '2020-06-06', 'v6', 1, 6),
('certificare66', 'aceasta este certificarea66', '2020-06-06', 'v66', 1, 6),
('certificare7', 'aceasta este certificarea7', '2020-07-07', 'v7', 1, 7);

INSERT INTO Angajati(nume, prenume, data_nasterii, email, telefon) VALUES
('nume1', 'prenume1', '1999-01-01', 'angajat1@yahoo.com', '0711111111'),
('nume2', 'prenume2', '1999-02-02', 'angajat2@yahoo.com', '0722222222'),
('nume3', 'prenume3', '1999-03-03', 'angajat3@yahoo.com', '0733333333'),
('nume4', 'prenume4', '1999-04-04', 'angajat4@yahoo.com', '0744444444'),
('nume5', 'prenume5', '1999-05-05', 'angajat5@yahoo.com', '0755555555'),
('nume6', 'prenume6', '1999-06-06', 'angajat6@yahoo.com', '0766666666');

INSERT INTO Angajati(nume, prenume, data_nasterii, email, telefon) VALUES
('nume7', 'prenume7', '1999-07-07', 'angajat7@yahoo.com', '0777777777');

INSERT INTO CertificariAngajati(id_certificare, id_angajat, data_examinarii, pret, punctaj) VALUES
(1, 1, '2021-01-01', 11.11, 111),
(2, 2, '2021-02-02', 22.22, 222),
(3, 3, '2021-03-03', 33.33, 333),
(4, 4, '2021-04-04', 44.44, 444),
(5, 5, '2021-05-05', 55.55, 555),
(8, 6, '2021-06-06', 66.66, 666),
(9, 6, '2021-09-09', 99.99, 999);


SELECT * FROM Tari;
SELECT * FROM Companii;
SELECT * FROM Certificari;
SELECT * FROM Angajati;
SELECT * FROM CertificariAngajati;


GO
CREATE OR ALTER PROCEDURE UpsertCertificariAngajati
	@id_certificare INT,
	@id_angajat INT,
	@data_examinarii DATE,
	@pret FLOAT,
	@punctaj INT
AS
BEGIN
	IF EXISTS(SELECT * FROM CertificariAngajati WHERE id_angajat = @id_angajat AND id_certificare = @id_certificare)
		UPDATE CertificariAngajati SET data_examinarii = @data_examinarii, pret = @pret, punctaj = @punctaj WHERE id_angajat = @id_angajat AND id_certificare = @id_certificare
	ELSE
		INSERT INTO CertificariAngajati(id_certificare, id_angajat, data_examinarii, pret, punctaj) VALUES (@id_certificare, @id_angajat, @data_examinarii, @pret, @punctaj)
END
GO

EXEC UpsertCertificariAngajati 9, 3, '2021-11-11', 111.11, 1111

EXEC UpsertCertificariAngajati 9, 3, '2021-07-07', 77.77, 777

SELECT * FROM CertificariAngajati;


GO
CREATE OR ALTER VIEW vw_AngajatiCertificari AS
SELECT MIN(ca.punctaj) AS Punctaj_Minim, MAX(ca.punctaj) AS Punctaj_Maxim, a.nume, a.prenume, a.email
FROM Angajati a
JOIN CertificariAngajati ca ON a.id_angajat = ca.id_angajat
JOIN Certificari c ON ca.id_certificare = c.id_certificare
JOIN Companii com ON c.id_companie = com.id_companie
GROUP BY a.nume, a.prenume, a.email, com.rating
HAVING com.rating >= 3 AND com.rating <= 5
GO


SELECT * FROM vw_AngajatiCertificari;