USE FirmaTaxi3;
GO

-- inserare in Tables
INSERT INTO Tables(Name) VALUES
('Soferi'), ('Vehicule'), ('Relatie_Soferi_Vehicule'); 
--('Categorie'), ('Produse'), ('ProduseDepozite'); 

SELECT * FROM Tables
-- afiseaza codul, numele si numarul de telefon pt fiecare sofer
GO
CREATE OR ALTER VIEW VSoferi AS
SELECT cod_sofer, nume, numar_telefon
FROM Soferi;


-- afiseaza numarul de vehicule si anul de fabricatie mediu al lor pentru fiecare garaj
GO
CREATE OR ALTER VIEW VVehicule AS
SELECT g.nume AS GarajNume, COUNT(v.cod_vehicul) AS NumarVehicule, AVG(v.an_fabricatie) AS AnFabricatieMediu
FROM Vehicule v
LEFT JOIN Garaje g ON v.cod_garaj = g.cod_garaj
GROUP BY g.nume;


-- afiseaza detalii despre soferii si vehiculele lor, respectiv in ce data au preluat si au predat masinile
GO
CREATE OR ALTER VIEW VRelatie_Soferi_Vehicule AS
SELECT s.nume AS NumeSofer, v.marca AS MarcaVehicul, v.model, rs.data_inceput, rs.data_sfarsit
FROM Relatie_Soferi_Vehicule rs
JOIN Soferi s ON rs.cod_sofer = s.cod_sofer
JOIN Vehicule v ON rs.cod_vehicul = v.cod_vehicul;

GO
SELECT * FROM VSoferi
SELECT * FROM VVehicule
SELECT * FROM VRelatie_Soferi_Vehicule

-- inserare in Views
INSERT INTO Views VALUES ('VSoferi'), ('VVehicule'), ('VRelatie_Soferi_Vehicule');
SELECT * FROM Views

-- inserare in Tests
INSERT INTO Tests VALUES
	('DIV_SOFERI_10'),
	('DIV_VEHICULE_7'),
	('DIV_Soferi_Vehicule_10')
GO


SELECT * FROM Tests

UPDATE Tests SET Name = 'DIV_Relatie_Soferi_Vehicule_10' WHERE TestID = 10;

-- inserare in tabelul TestTables
INSERT INTO TestTables VALUES
	-- DIV_SOFERI_10
	(8, 1, 10, 1),
	-- DIV_VEHICULE_7
	(9, 2, 7, 2),
	-- DIV_SOFERI_VEHICULE_10
	(10, 1, 10, 3),
	(10, 3, 10, 4);

UPDATE TestTables SET TableID = 2  WHERE TableID = 3;
INSERT INTO TestTables VALUES (10, 3, 10, 5);
SELECT * FROM TestTables;
GO

-- inserare in TestViews
INSERT INTO TestViews(TestID, ViewID) 
VALUES (8, 1), (9, 2), (10, 3)
GO

SELECT * FROM TestViews

-- inserare in tabelul Soferi
GO
CREATE OR ALTER PROCEDURE InsertSoferi (@rows int)
AS
BEGIN
    PRINT 'Inserare Soferi'
    DECLARE @i int = 1;
    DECLARE @nume VARCHAR(100);
    DECLARE @numar_telefon VARCHAR(20);

    WHILE @i <= @rows
    BEGIN
        SET @nume = 'Sofer' + CAST(@i AS VARCHAR(10));
        SET @numar_telefon = '07000000' + RIGHT('00' + CAST(@i AS VARCHAR(10)), 4);

        INSERT INTO Soferi (nume, CNP, numar_telefon)
        VALUES (@nume, '1234567890123', @numar_telefon); 

        SET @i = @i + 1;
    END
END

-- stergere din tabelul Soferi
GO
CREATE OR ALTER PROCEDURE DeleteSoferi
AS
BEGIN
    PRINT 'Stergere Soferi'
    DELETE FROM Soferi;
END
GO

exec InsertSoferi 10
exec DeleteSoferi
SELECT * FROM Soferi
GO

-- inserare in tabelul Vehicule
CREATE OR ALTER PROCEDURE InsertVehicule (@rows int)
AS
BEGIN
    PRINT 'Inserare Vehicule'
    DECLARE @i int = 1;
    DECLARE @marca VARCHAR(100);
    DECLARE @model VARCHAR(100);
    DECLARE @an_fabricatie INT;
    DECLARE @numar_inmatriculare VARCHAR(20);
    DECLARE @cod_garaj INT;

    WHILE @i <= @rows
    BEGIN
        SET @marca = 'Marca' + CAST(@i AS VARCHAR(10));
        SET @model = 'Model' + CAST(@i AS VARCHAR(10));
        SET @an_fabricatie = 2000 + (@i % 24);
        SET @numar_inmatriculare = 'SM' + RIGHT('00' + CAST(@i AS VARCHAR(10)), 2) + 'XYZ';

        SELECT TOP 1 @cod_garaj = cod_garaj FROM Garaje ORDER BY NEWID();

        INSERT INTO Vehicule (marca, model, an_fabricatie, numar_inmatriculare, cod_garaj)
        VALUES (@marca, @model, @an_fabricatie, @numar_inmatriculare, @cod_garaj);

        SET @i = @i + 1;
    END
END
GO

-- stergere din tabelul Vehicule
CREATE OR ALTER PROCEDURE DeleteVehicule
AS
BEGIN
    PRINT 'Stergere Vehicule'
    DELETE FROM Vehicule;
END
GO

exec InsertVehicule 10
exec DeleteVehicule
SELECT * FROM Vehicule

GO


-- inserare in tabelul Relatie_Soferi_Vehicule
CREATE OR ALTER PROCEDURE InsertRelatie_Soferi_Vehicule (@rows INT)
AS
BEGIN
    PRINT 'Inserare Relatii';
    
    DECLARE @i INT = 1;
    DECLARE @cod_sofer INT;
    DECLARE @cod_vehicul INT;
    DECLARE @data_inceput DATETIME;
    DECLARE @data_sfarsit DATETIME;

    WHILE @i <= @rows
    BEGIN
        BEGIN
            SELECT @cod_sofer = cod_sofer FROM Soferi ORDER BY NEWID() OFFSET 0 ROWS FETCH NEXT 1 ROWS ONLY;

            SELECT @cod_vehicul = cod_vehicul FROM Vehicule ORDER BY NEWID() OFFSET 0 ROWS FETCH NEXT 1 ROWS ONLY;

            IF NOT EXISTS (
                SELECT 1 
                FROM Relatie_Soferi_Vehicule 
                WHERE cod_sofer = @cod_sofer AND cod_vehicul = @cod_vehicul
            )
            BEGIN
                SET @data_inceput = DATEADD(DAY, @i - 1, DATEFROMPARTS(YEAR(GETDATE()), 1, 1));
                SET @data_sfarsit = DATEADD(DAY, @i, DATEFROMPARTS(YEAR(GETDATE()), 1, 1));

                INSERT INTO Relatie_Soferi_Vehicule (cod_sofer, cod_vehicul, data_inceput, data_sfarsit)
                VALUES (@cod_sofer, @cod_vehicul, @data_inceput, @data_sfarsit);
				SET @i = @i + 1;
            END
			SET @i = @i - 1;
        END

        SET @i = @i + 1;
    END

    PRINT 'Inserare completa.';
END
GO





-- stergere din tabelul Relatie_Soferi_Vehicule
CREATE OR ALTER PROCEDURE DeleteRelatie_Soferi_Vehicule
AS
BEGIN
    PRINT 'Stergere Relatii'
    DELETE FROM Relatie_Soferi_Vehicule;
END
GO

exec InsertRelatie_Soferi_Vehicule 10
exec DeleteRelatie_Soferi_Vehicule
SELECT * FROM Relatie_Soferi_Vehicule
SELECT * FROM Soferi;
SELECT * FROM Vehicule;

-- procedura generala pt inserare
GO
CREATE OR ALTER PROCEDURE InsertGeneral
@idTest INT
AS
BEGIN
	DECLARE @numeTest NVARCHAR(50) = (SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	DECLARE @numeTabela NVARCHAR(50);
	DECLARE @NoOfRows INT;
	DECLARE @procedura NVARCHAR(50);

	DECLARE cursorTab CURSOR FORWARD_ONLY FOR
		SELECT Tab.Name, Test.NoOfRows FROM TestTables Test
		INNER JOIN Tables Tab ON Test.TableID = Tab.TableID
		WHERE Test.TestID = @idTest
		ORDER BY Test.Position;
	OPEN cursorTab;

	FETCH NEXT FROM cursorTab INTO @numeTabela, @NoOfRows;
	WHILE (@numeTest NOT LIKE N'DIV_' + @numeTabela + N'_' + CONVERT(NVARCHAR(10), @NoOfRows)) AND (@@FETCH_STATUS = 0)
	BEGIN
		SET @procedura = N'Insert' + @numeTabela;
		EXECUTE @procedura @NoOfRows;
		FETCH NEXT FROM cursorTab INTO @numeTabela, @NoOfRows;
	END

	SET @procedura = N'Insert' + @numeTabela;
	EXECUTE @procedura @NoOfRows;

	CLOSE cursorTab;
	DEALLOCATE cursorTab;
END
GO

SELECT Tab.Name, Test.NoOfRows FROM TestTables Test
		INNER JOIN Tables Tab ON Test.TableID = Tab.TableID
		WHERE Test.TestID = 10
		ORDER BY Test.Position;

execute InsertGeneral 8;
SELECT * FROM Soferi;
execute InsertGeneral 9;
SELECT * FROM Vehicule;
execute InsertGeneral 10;
SELECT * FROM Relatie_Soferi_Vehicule;

-- procedura generala pt stergere
GO
CREATE PROCEDURE StergereGeneral
@idTest INT
AS
BEGIN
	DECLARE @numeTest NVARCHAR(50) = (SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	DECLARE @numeTabela NVARCHAR(50);
	DECLARE @NoOfRows INT;
	DECLARE @procedura NVARCHAR(50);

	DECLARE cursorTab CURSOR FORWARD_ONLY FOR
		SELECT Tab.Name, Test.NoOfRows FROM TestTables Test
		INNER JOIN Tables Tab ON Test.TableID = Tab.TableID
		WHERE Test.TestID = @idTest
		ORDER BY Test.Position DESC;
	OPEN cursorTab;

	FETCH NEXT FROM cursorTab INTO @numeTabela, @NoOfRows;
	WHILE (@numeTest NOT LIKE N'DIV_' + @numeTabela + N'_' + CONVERT(NVARCHAR(10), @NoOfRows)) AND (@@FETCH_STATUS = 0)
	BEGIN
		SET @procedura = N'Delete' + @numeTabela;
		EXECUTE @procedura;
		FETCH NEXT FROM cursorTab INTO @numeTabela, @NoOfRows;
	END

	SET @procedura = N'Delete' + @numeTabela;
	EXECUTE @procedura;

	CLOSE cursorTab;
	DEALLOCATE cursorTab;
END

execute StergereGeneral 8;
SELECT * FROM Soferi;
execute StergereGeneral 9;
SELECT * FROM Vehicule;
execute StergereGeneral 10;
SELECT * FROM Relatie_Soferi_Vehicule;


-- procedura generala pentru view
GO
CREATE PROCEDURE GeneralView
@idTest INT
AS
BEGIN
	DECLARE @viewName NVARCHAR(50) = 
		(SELECT V.Name FROM Views V
		INNER JOIN TestViews TV ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @idTest);

	DECLARE @comanda NVARCHAR(55) = 
		N'SELECT * FROM ' + @viewName;
	
	EXECUTE (@comanda);
END

execute GeneralView 8;
execute GeneralView 9;
execute GeneralView 10;


GO
CREATE PROCEDURE RunTest
@idTest INT
AS
BEGIN
	DECLARE @startTime DATETIME;
	DECLARE @interTime DATETIME;
	DECLARE @endTime DATETIME;

	SET @startTime = GETDATE();
	
	EXECUTE StergereGeneral @idTest;
	EXECUTE InsertGeneral @idTest;
	
	SET @interTime = GETDATE();
	
	EXECUTE GeneralView @idTest;

	SET @endTime = GETDATE();

	-- var pt insert
	DECLARE @testName NVARCHAR(50) =
		(SELECT T.Name FROM Tests T WHERE T.TestID = @idTest);
	INSERT INTO TestRuns VALUES (@testName, @startTime, @endTime);

	DECLARE @viewID INT =
		(SELECT V.ViewID FROM Views V
		INNER JOIN TestViews TV ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @idTest);
	DECLARE @tableID INT =
		(SELECT TB.TableID FROM Tests T
		INNER JOIN TestTables TT ON T.TestID = TT.TestID
		INNER JOIN Tables TB ON TB.TableID = TT.TableID
		WHERE T.TestID = @idTest AND 
		T.Name LIKE N'DIV_' + TB.Name + N'_' + CONVERT(NVARCHAR(10), TT.NoOfRows));
	DECLARE @testRunID INT = 
		(SELECT TOP 1 T.TestRunID FROM TestRuns T
		WHERE T.Description = @testName
		ORDER BY T.TestRunID DESC);
	
	INSERT INTO TestRunTables VALUES (@testRunID, @tableID, @startTime, @interTime);
	INSERT INTO TestRunViews VALUES (@testRunID, @viewID, @interTime, @endTime);

	PRINT CHAR(10) + 'finalizat: ' + 
		 CONVERT(VARCHAR(10), DATEDIFF(millisecond, @startTime, @endTime)) +
		 'ms'
END

execute RunTest 8;
execute RunTest 9;
execute RunTest 10;

Select * from TestRuns;
Select * from TestRunTables;
Select * from TestRunViews;
