USE FirmaTaxi3;
GO

CREATE FUNCTION dbo.ValidareCNP(@cnp VARCHAR(13))
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF LEN(@cnp) = 13 AND ISNUMERIC(@cnp) = 1
    BEGIN
        DECLARE @an INT = CAST(SUBSTRING(@cnp, 2, 2) AS INT)
        DECLARE @luna INT = CAST(SUBSTRING(@cnp, 4, 2) AS INT)
        DECLARE @zi INT = CAST(SUBSTRING(@cnp, 6, 2) AS INT)

        IF @luna BETWEEN 1 AND 12 AND @zi BETWEEN 1 AND 31
            SET @valid = 1
    END

    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareNumarTelefon (@numar_telefon VARCHAR(20))
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF LEFT(@numar_telefon, 1) = '0' AND LEN(@numar_telefon) = 10
        SET @valid = 1
    ELSE IF LEFT(@numar_telefon, 3) = '+40' AND LEN(@numar_telefon) = 12
        SET @valid = 1

    RETURN @valid
END
GO

ALTER TABLE Soferi
ADD CONSTRAINT CHK_Soferi_CNP CHECK (LEN(CNP) = 13 AND CNP NOT LIKE '%[^0-9]%');

ALTER TABLE Soferi
ADD CONSTRAINT CHK_Soferi_Numar_Telefon CHECK (LEN(numar_telefon) IN (10, 12) AND numar_telefon LIKE '+40%' OR numar_telefon LIKE '0%');
GO

CREATE FUNCTION dbo.ValidareAnFabricatie(@an INT)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF @an >= 1900 AND @an <= YEAR(GETDATE())
        SET @valid = 1

    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareNumarInmatriculare(@numar VARCHAR(20))
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF LEN(@numar) >= 6 AND LEN(@numar) <= 7
        SET @valid = 1

    RETURN @valid
END
GO

ALTER TABLE Vehicule
ADD CONSTRAINT CHK_Vehicule_An_Fabricatie CHECK (an_fabricatie BETWEEN 1900 AND YEAR(GETDATE()));

ALTER TABLE Vehicule
ADD CONSTRAINT CHK_Vehicule_Numar_Inmatriculare CHECK (LEN(numar_inmatriculare) BETWEEN 6 AND 7);
GO

CREATE FUNCTION dbo.ValidareNotNull(@string VARCHAR(100))
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF @string IS NOT NULL AND LEN(@string) > 0
        SET @valid = 1

    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareNotZero(@nr INT)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0

    IF @nr > 0
        SET @valid = 1

    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareCodSofer(@cod_sofer INT)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0
    IF EXISTS(SELECT 1 FROM Soferi WHERE cod_sofer = @cod_sofer)
        SET @valid = 1
    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareCodVehicul(@cod_vehicul INT)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0
    IF EXISTS(SELECT 1 FROM Vehicule WHERE cod_vehicul = @cod_vehicul)
        SET @valid = 1
    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareZi(@zi VARCHAR(10))
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0
    IF @zi IN ('Luni', 'Marti', 'Miercuri', 'Joi', 'Vineri', 'Sambata', 'Duminica')
        SET @valid = 1
    RETURN @valid
END
GO

CREATE FUNCTION dbo.ValidareOra(@ora TIME)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0
    IF @ora >= '00:00:00' AND @ora <= '23:59:59'
        SET @valid = 1

    RETURN @valid
END
GO

ALTER TABLE Program_Soferi
ADD CONSTRAINT CHK_Program_Soferi_Zi CHECK (ziua IN ('Luni', 'Marti', 'Miercuri', 'Joi', 'Vineri', 'Sambata', 'Duminica'));

ALTER TABLE Program_Soferi
ADD CONSTRAINT CHK_Program_Soferi_Ora CHECK (ora_inceput >= '00:00:00' AND ora_inceput <= '23:59:59' AND ora_sfarsit >= '00:00:00' AND ora_sfarsit <= '23:59:59');
GO

CREATE FUNCTION dbo.ValidareData(@data DATETIME)
RETURNS BIT
AS
BEGIN
    DECLARE @valid BIT = 0;
    DECLARE @dataMinima DATETIME = DATEADD(YEAR, -1, GETDATE());
    DECLARE @dataMaxima DATETIME = DATEADD(YEAR, 1, GETDATE());

    IF @data >= @dataMinima AND @data <= @dataMaxima
        SET @valid = 1;
    ELSE
        SET @valid = 0;

    RETURN @valid;
END;
GO

ALTER TABLE Relatie_Soferi_Vehicule
ADD CONSTRAINT CHK_Relatie_Soferi_Vehicule_Data_Inceput CHECK (data_inceput BETWEEN DATEADD(YEAR, -1, GETDATE()) AND DATEADD(YEAR, 1, GETDATE()));

ALTER TABLE Relatie_Soferi_Vehicule
ADD CONSTRAINT CHK_Relatie_Soferi_Vehicule_Data_Sfarsit CHECK (data_sfarsit BETWEEN DATEADD(YEAR, -1, GETDATE()) AND DATEADD(YEAR, 1, GETDATE()));
GO


-- CRUD Soferi
CREATE PROCEDURE procAddSoferi
    @nume VARCHAR(100),
    @CNP VARCHAR(13),
    @numar_telefon VARCHAR(20)
AS
BEGIN
    IF dbo.ValidareCNP(@CNP) = 0
    BEGIN
        RAISERROR('CNP invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNumarTelefon(@numar_telefon) = 0
    BEGIN
        RAISERROR('Numar de telefon invalid!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@nume) = 0
	BEGIN
        RAISERROR('Nume invalid!', 16, 1);
        RETURN;
    END

    INSERT INTO Soferi (nume, CNP, numar_telefon)
    VALUES (@nume, @CNP, @numar_telefon)
END
GO

EXEC procAddSoferi
    @nume = 'Ion Popescu',
    @CNP = '5040821303708',
    @numar_telefon = '0741123456';

SELECT * FROM Soferi;


CREATE PROCEDURE procGetSoferi
    @cod_sofer INT
AS
BEGIN
    SELECT * FROM Soferi WHERE cod_sofer = @cod_sofer
END
GO

EXEC procGetSoferi
    @cod_sofer = 489; 



CREATE PROCEDURE proc_update_Soferi
    @cod_sofer INT,
    @nume VARCHAR(100),
    @CNP VARCHAR(13),
    @numar_telefon VARCHAR(20)
AS
BEGIN
    IF dbo.ValidareCNP(@CNP) = 0
    BEGIN
        RAISERROR('CNP invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNumarTelefon(@numar_telefon) = 0
    BEGIN
        RAISERROR('Numar de telefon invalid!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@nume) = 0
	BEGIN
        RAISERROR('Nume invalid!', 16, 1);
        RETURN;
    END

    UPDATE Soferi
    SET nume = @nume, CNP = @CNP, numar_telefon = @numar_telefon
    WHERE cod_sofer = @cod_sofer
END
GO

EXEC proc_update_Soferi
    @cod_sofer = 489, 
    @nume = 'George Popescu',
    @CNP = '5040821303707',
    @numar_telefon = '0751234567';


CREATE PROCEDURE procDeleteSoferi
    @cod_sofer INT
AS
BEGIN
    DELETE FROM Soferi WHERE cod_sofer = @cod_sofer
END
GO

EXEC procDeleteSoferi
    @cod_sofer = 504;
GO


-- CRUD Vehicule
CREATE OR ALTER PROCEDURE procAddVehicule
    @marca VARCHAR(100),
    @model VARCHAR(100),
    @an_fabricatie INT,
    @numar_inmatriculare VARCHAR(20),
	@garaj_id INT
AS
BEGIN
	IF dbo.ValidareNotNull(@marca) = 0
	BEGIN
        RAISERROR('Marca invalida!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@model) = 0
	BEGIN
        RAISERROR('Model invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareAnFabricatie(@an_fabricatie) = 0
    BEGIN
        RAISERROR('An de fabricatie invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNumarInmatriculare(@numar_inmatriculare) = 0
    BEGIN
        RAISERROR('Numar de inmatriculare invalid!', 16, 1);
        RETURN;
    END

	IF NOT EXISTS (SELECT 1 FROM Garaje WHERE cod_garaj = @garaj_id)
    BEGIN
        RAISERROR('Garaj invalid!', 16, 1);
        RETURN;
    END

    INSERT INTO Vehicule (marca, model, an_fabricatie, numar_inmatriculare, cod_garaj)
    VALUES (@marca, @model, @an_fabricatie, @numar_inmatriculare, @garaj_id)
END
GO

EXEC procAddVehicule
    @marca = 'Mercedes',
    @model = 'GLE',
    @an_fabricatie = 2023,
    @numar_inmatriculare = 'SM01MRC',
	@garaj_id = 1;

SELECT * FROM Vehicule;
GO


CREATE PROCEDURE procGetVehicule
    @cod_vehicul INT
AS
BEGIN
    SELECT * FROM Vehicule WHERE cod_vehicul = @cod_vehicul
END
GO

EXEC procGetVehicule
    @cod_vehicul = 469;
GO


CREATE OR ALTER PROCEDURE procUpdateVehicule
    @cod_vehicul INT,
    @marca VARCHAR(100),
    @model VARCHAR(100),
    @an_fabricatie INT,
    @numar_inmatriculare VARCHAR(20),
	@garaj_id INT
AS
BEGIN
	IF dbo.ValidareNotNull(@marca) = 0
	BEGIN
        RAISERROR('Marca invalida!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@model) = 0
	BEGIN
        RAISERROR('Model invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareAnFabricatie(@an_fabricatie) = 0
    BEGIN
        RAISERROR('An de fabricatie invalid!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNumarInmatriculare(@numar_inmatriculare) = 0
    BEGIN
        RAISERROR('Numar de inmatriculare invalid!', 16, 1);
        RETURN;
    END

	IF NOT EXISTS (SELECT 1 FROM Garaje WHERE cod_garaj = @garaj_id)
    BEGIN
        RAISERROR('Garaj invalid!', 16, 1);
        RETURN;
    END

    UPDATE Vehicule
    SET marca = @marca, model = @model, an_fabricatie = @an_fabricatie, numar_inmatriculare = @numar_inmatriculare, cod_garaj = @garaj_id
    WHERE cod_vehicul = @cod_vehicul
END
GO

EXEC procUpdateVehicule
    @cod_vehicul = 469, 
    @marca = 'Opel',
    @model = 'Astra',
    @an_fabricatie = 2022,
    @numar_inmatriculare = 'B321CBA',
	@garaj_id = 2;
GO


CREATE PROCEDURE procDeleteVehicule
    @cod_vehicul INT
AS
BEGIN
    DELETE FROM Vehicule WHERE cod_vehicul = @cod_vehicul
END
GO

EXEC procDeleteVehicule
    @cod_vehicul = 472; 
GO


--CRUD Garaje
CREATE OR ALTER PROCEDURE procAddGaraje
    @cod_garaj INT,
    @nume VARCHAR(100),
    @locatie VARCHAR(100),
    @capacitate INT
AS
BEGIN
    IF dbo.ValidareNotNull(@nume) = 0
    BEGIN
        RAISERROR('Nume garaj invalid!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@locatie) = 0
    BEGIN
        RAISERROR('Locatie garaj invalida!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNotZero(@capacitate) = 0
    BEGIN
        RAISERROR('Capacitate garaj invalida!', 16, 1);
        RETURN;
    END

	IF EXISTS (SELECT 1 FROM Garaje WHERE cod_garaj = @cod_garaj)
    BEGIN
        RAISERROR('Un garaj cu acest cod exista deja!', 16, 1);
        RETURN;
    END

    INSERT INTO Garaje (cod_garaj, nume, locatie, capacitate)
    VALUES (@cod_garaj, @nume, @locatie, @capacitate)
END
GO

EXEC procAddGaraje
	@cod_garaj = 3,
    @nume = 'Garaj Central',
    @locatie = 'MV1',
    @capacitate = 50;

SELECT * FROM Garaje;

GO
CREATE PROCEDURE procGetGaraje
    @cod_garaj INT
AS
BEGIN
    SELECT * FROM Garaje WHERE cod_garaj = @cod_garaj
END
GO

EXEC procGetGaraje
    @cod_garaj = 3;

GO

CREATE PROCEDURE procUpdateGaraje
    @cod_garaj INT,
    @nume VARCHAR(100),
    @locatie VARCHAR(100),
    @capacitate INT
AS
BEGIN
    IF dbo.ValidareNotNull(@nume) = 0
    BEGIN
        RAISERROR('Nume garaj invalid!', 16, 1);
        RETURN;
    END

	IF dbo.ValidareNotNull(@locatie) = 0
    BEGIN
        RAISERROR('Locatie garaj invalida!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareNotZero(@capacitate) = 0
    BEGIN
        RAISERROR('Capacitate garaj invalida!', 16, 1);
        RETURN;
    END

    UPDATE Garaje
    SET nume = @nume, locatie = @locatie, capacitate = @capacitate
    WHERE cod_garaj = @cod_garaj
END
GO

EXEC procUpdateGaraje
    @cod_garaj = 3,
    @nume = 'Garaj Nou',
    @locatie = 'MV2',
    @capacitate = 100;


CREATE PROCEDURE procDeleteGaraje
    @cod_garaj INT
AS
BEGIN
    DELETE FROM Garaje WHERE cod_garaj = @cod_garaj
END
GO

EXEC procDeleteGaraje
    @cod_garaj = 3;

SELECT * FROM Garaje;

GO


--CRUD Program_Soferi
CREATE OR ALTER PROCEDURE procAddProgram_Soferi
	@cod_program INT,
    @cod_sofer INT,
    @ziua VARCHAR(10),
    @ora_inceput TIME,
    @ora_sfarsit TIME
AS
BEGIN
    IF dbo.ValidareCodSofer(@cod_sofer) = 0
    BEGIN
        RAISERROR('Cod sofer inexistent!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareZi(@ziua) = 0
    BEGIN
        RAISERROR('Zi invalida!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareOra(@ora_inceput) = 0 OR dbo.ValidareOra(@ora_sfarsit) = 0
    BEGIN
        RAISERROR('Ora invalida!', 16, 1);
        RETURN;
    END

	IF EXISTS (SELECT 1 FROM Program_Soferi WHERE cod_program = @cod_program)
    BEGIN
        RAISERROR('Un program cu acest cod exista deja!', 16, 1);
        RETURN;
    END

    INSERT INTO Program_Soferi (cod_program, cod_sofer, ziua, ora_inceput, ora_sfarsit)
    VALUES (@cod_program, @cod_sofer, @ziua, @ora_inceput, @ora_sfarsit)
END
GO

EXEC procAddProgram_Soferi
    @cod_program = 99,
    @cod_sofer = 499,
    @ziua = 'Luni',
    @ora_inceput = '08:00',
    @ora_sfarsit = '16:00';

SELECT * FROM Program_Soferi;

CREATE PROCEDURE procGetProgram_Soferi
    @cod_program INT
AS
BEGIN
    SELECT * FROM Program_Soferi WHERE cod_program = @cod_program
END
GO

EXEC procGetProgram_Soferi
    @cod_program = 99;


CREATE PROCEDURE procUpdateProgram_Soferi
    @cod_program INT,
    @cod_sofer INT,
    @ziua VARCHAR(10),
    @ora_inceput TIME,
    @ora_sfarsit TIME
AS
BEGIN
        IF dbo.ValidareCodSofer(@cod_sofer) = 0
    BEGIN
        RAISERROR('Cod sofer inexistent!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareZi(@ziua) = 0
    BEGIN
        RAISERROR('Zi invalida!', 16, 1);
        RETURN;
    END

    IF dbo.ValidareOra(@ora_inceput) = 0 OR dbo.ValidareOra(@ora_sfarsit) = 0
    BEGIN
        RAISERROR('Ora invalida!', 16, 1);
        RETURN;
    END

    UPDATE Program_Soferi
    SET cod_sofer = @cod_sofer, ziua = @ziua, ora_inceput = @ora_inceput, ora_sfarsit = @ora_sfarsit
    WHERE cod_program = @cod_program
END
GO

EXEC procUpdateProgram_Soferi
    @cod_program = 99,
    @cod_sofer = 499,
    @ziua = 'Marti',
    @ora_inceput = '09:00',
    @ora_sfarsit = '17:00';



CREATE PROCEDURE procDeleteProgram_Soferi
    @cod_program INT
AS
BEGIN
    DELETE FROM Program_Soferi WHERE cod_program = @cod_program
END
GO

EXEC procDeleteProgram_Soferi
    @cod_program = 99;


--CRUD Relatie_Soferi_Vehicule
CREATE PROCEDURE procAddRelatie_Soferi_Vehicule
    @cod_sofer INT,
    @cod_vehicul INT,
    @data_inceput DATETIME,
    @data_sfarsit DATETIME
AS
BEGIN
    IF dbo.ValidareCodSofer(@cod_sofer) = 0
    BEGIN
        RAISERROR('Cod sofer inexistent.', 16, 1);
        RETURN;
    END

    IF dbo.ValidareCodVehicul(@cod_vehicul) = 0
    BEGIN
        RAISERROR('Cod vehicul inexistent.', 16, 1);
        RETURN;
    END

	IF dbo.ValidareData(@data_inceput) = 0 OR dbo.ValidareData(@data_sfarsit) = 0
	BEGIN
		RAISERROR('Data invalida.', 16, 1);
		RETURN;
	END

    INSERT INTO Relatie_Soferi_Vehicule (cod_sofer, cod_vehicul, data_inceput, data_sfarsit)
    VALUES (@cod_sofer, @cod_vehicul, @data_inceput, @data_sfarsit)
END
GO

EXEC procAddRelatie_Soferi_Vehicule
    @cod_sofer = 501,
    @cod_vehicul = 465,
    @data_inceput = '2024-01-01',
    @data_sfarsit = '2024-12-31';


SELECT * FROM Relatie_Soferi_Vehicule;

CREATE PROCEDURE procGetRelatie_Soferi_Vehicule
    @cod_sofer INT,
    @cod_vehicul INT
AS
BEGIN
    SELECT * FROM Relatie_Soferi_Vehicule
    WHERE cod_sofer = @cod_sofer AND cod_vehicul = @cod_vehicul
END
GO

EXEC procGetRelatie_Soferi_Vehicule
    @cod_sofer = 501,
    @cod_vehicul = 465;


CREATE PROCEDURE procUpdateRelatie_Soferi_Vehicule
    @cod_sofer INT,
    @cod_vehicul INT,
    @data_inceput DATETIME,
    @data_sfarsit DATETIME
AS
BEGIN
    IF dbo.ValidareCodSofer(@cod_sofer) = 0
    BEGIN
        RAISERROR('Cod sofer inexistent.', 16, 1);
        RETURN;
    END

    IF dbo.ValidareCodVehicul(@cod_vehicul) = 0
    BEGIN
        RAISERROR('Cod vehicul inexistent.', 16, 1);
        RETURN;
    END

	IF dbo.ValidareData(@data_inceput) = 0 OR dbo.ValidareData(@data_sfarsit) = 0
	BEGIN
		RAISERROR('Data invalida.', 16, 1);
		RETURN;
	END

    UPDATE Relatie_Soferi_Vehicule
    SET data_inceput = @data_inceput, data_sfarsit = @data_sfarsit
    WHERE cod_sofer = @cod_sofer AND cod_vehicul = @cod_vehicul
END
GO

EXEC procUpdateRelatie_Soferi_Vehicule
    @cod_sofer = 501,
    @cod_vehicul = 465,
    @data_inceput = '2024-12-01',
    @data_sfarsit = '2024-12-03';



CREATE PROCEDURE procDeleteRelatie_Soferi_Vehicule
    @cod_sofer INT,
    @cod_vehicul INT
AS
BEGIN
    DELETE FROM Relatie_Soferi_Vehicule
    WHERE cod_sofer = @cod_sofer AND cod_vehicul = @cod_vehicul
END
GO

EXEC procDeleteRelatie_Soferi_Vehicule
    @cod_sofer = 501,
    @cod_vehicul = 465;


SELECT * FROM Soferi
SELECT * FROM Vehicule
SELECT * FROM Garaje
SELECT * FROM Program_Soferi
SELECT * FROM Relatie_Soferi_Vehicule

SELECT s.nume AS NumeSofer, v.marca, v.model, v.numar_inmatriculare
FROM Soferi s
JOIN Relatie_Soferi_Vehicule rsv ON s.cod_sofer = rsv.cod_sofer
JOIN Vehicule v ON rsv.cod_vehicul = v.cod_vehicul;
GO


-- VIEW si INDEX pentru afisarea vehiculelor care fac parte dintr un garaj specific
CREATE NONCLUSTERED INDEX IDX_Vehicule_CodGaraj_New ON Vehicule(cod_garaj)
INCLUDE (cod_vehicul, marca, model, numar_inmatriculare);

CREATE NONCLUSTERED INDEX IDX_Garaje_Nume_New ON Garaje(nume)
INCLUDE (locatie, cod_garaj);

GO
CREATE OR ALTER VIEW viewVehiculeGarajeTaxiuri AS
SELECT
    v.cod_vehicul,
    v.marca,
    v.model,
    v.numar_inmatriculare,
    g.nume AS NumeGaraj,
    g.locatie AS LocatieGaraj
FROM Vehicule v
JOIN Garaje g ON v.cod_garaj = g.cod_garaj
WHERE g.nume = 'Garaj Taxiuri';
GO


-- VIEW si INDEX pentru afisarea soferilor si orarului de munca intr o anumita zi
CREATE NONCLUSTERED INDEX IDX_Program_Soferi_New ON Program_Soferi (ziua)
INCLUDE (cod_sofer, ora_inceput, ora_sfarsit);
GO

CREATE VIEW viewSoferiProgramLuni AS
SELECT
    s.cod_sofer,
    s.nume AS NumeSofer,
    ps.ziua AS ZiuaProgramului,
    ps.ora_inceput AS OraInceput,
    ps.ora_sfarsit AS OraSfarsit
FROM Soferi s
JOIN Program_Soferi ps ON s.cod_sofer = ps.cod_sofer
WHERE ps.ziua = 'Luni';
GO


-- VIEW si INDEX pentru afisarea soferilor si a vehiculelor pe care le au condus in octombrie 2024
CREATE NONCLUSTERED INDEX IDX_Relatie_SoferiVehicule_New ON Relatie_Soferi_Vehicule(data_inceput)
INCLUDE (cod_sofer, cod_vehicul, data_sfarsit);
GO

CREATE OR ALTER VIEW viewSoferiVehiculeRelatie2024Oct AS
SELECT
    s.nume AS NumeSofer,
    v.marca,
    v.model,
    v.numar_inmatriculare,
    rsv.data_inceput AS DataInceput,
    rsv.data_sfarsit AS DataSfarsit
FROM Soferi s
JOIN Relatie_Soferi_Vehicule rsv ON s.cod_sofer = rsv.cod_sofer
JOIN Vehicule v ON rsv.cod_vehicul = v.cod_vehicul
WHERE rsv.data_inceput >= '2024-10-01' AND rsv.data_inceput < '2024-11-01';
GO


SELECT * FROM viewSoferiProgramLuni;
SELECT * FROM viewVehiculeGarajeTaxiuri;
SELECT * FROM viewSoferiVehiculeRelatie2024Oct;




GO
CREATE VIEW dbo.VwCurseDetalii WITH SCHEMABINDING
AS
    SELECT c.cod_cursa, s.nume AS NumeSofer, cl.nume AS NumeClient
    FROM dbo.Curse c
    JOIN dbo.Soferi s ON c.cod_sofer = s.cod_sofer
    JOIN dbo.Clienti cl ON c.cod_client = cl.cod_client;
GO


CREATE UNIQUE CLUSTERED INDEX IDX_VwCurseDetalii
ON dbo.VwCurseDetalii (cod_cursa);
GO


SELECT * FROM VwCurseDetalii