USE FirmaTaxi3;
GO

CREATE PROCEDURE do_procedura1 AS
BEGIN
ALTER TABLE Soferi
ALTER COLUMN nume VARCHAR(150);
PRINT 'S-a actualizat coloana [nume] din tabelul [Soferi]';
END;
GO

CREATE PROCEDURE do_procedura2 AS
BEGIN
ALTER TABLE Rating
ADD CONSTRAINT DF_descriere DEFAULT 'Fara descriere.' FOR descriere;
PRINT 'S-a introdus o constrangere pentru coloana [descriere] din tabelul [Rating]';
END;
GO

CREATE PROCEDURE do_procedura3 AS
BEGIN
CREATE TABLE Teapa
(cod_teapa INT PRIMARY KEY,
adresa VARCHAR(100),
numar_telefon VARCHAR(20)
);
PRINT 'S-a creat un tabel noul [Teapa]';
END;
GO

CREATE PROCEDURE do_procedura4 AS
BEGIN
ALTER TABLE Teapa
ADD data_teapa DATE;
PRINT 'S-a adaugat coloana [data_teapa] in tabelul [Teapa]';
END;
GO

CREATE PROCEDURE do_procedura5 AS
BEGIN
ALTER TABLE Teapa
ADD CONSTRAINT FK_teapa_cursa FOREIGN KEY(cod_teapa) REFERENCES Curse(cod_cursa);
PRINT 'S-a adaugat o constrangere de cheie straina';
END;
GO

CREATE PROCEDURE undo_procedura1 AS
BEGIN
ALTER TABLE Soferi
ALTER COLUMN nume VARCHAR(100);
PRINT 'S-a reactualizat coloana [nume] din tabelul [Soferi]';
END;
GO

CREATE PROCEDURE undo_procedura2 AS
BEGIN
ALTER TABLE Rating
DROP CONSTRAINT DF_descriere
PRINT 'S-a eliminat o constrangere pentru coloana [descriere] din tabelul [Rating]';
END;
GO

CREATE PROCEDURE undo_procedura3 AS
BEGIN
DROP TABLE Teapa
PRINT 'S-a sters tabelul [Teapa]';
END;
GO

CREATE PROCEDURE undo_procedura4 AS
BEGIN
ALTER TABLE Teapa
DROP COLUMN data_teapa;
PRINT 'S-a eliminat coloana [data_teapa] din tabelul [Teapa]';
END;
GO

CREATE PROCEDURE undo_procedura5 AS
BEGIN
ALTER TABLE Teapa
DROP CONSTRAINT FK_teapa_cursa
PRINT 'S-a eliminat o constrangere de cheie straina';
END;
GO

CREATE TABLE Versiune
(nr_versiune INT);

INSERT INTO Versiune VALUES(0)

SELECT * from Versiune

GO
CREATE OR ALTER PROCEDURE main @versiune INT
AS
BEGIN
	IF (@versiune < 0 OR @versiune > 5)
	BEGIN
		PRINT 'Versiune invalida!'
		RETURN
	END
	
	DECLARE @versiune_curenta INT
	SELECT @versiune_curenta = nr_versiune FROM Versiune

	IF (@versiune = @versiune_curenta)
	BEGIN
		PRINT 'Versiunea este deja cea solicitata!'
		RETURN
	END

	IF (@versiune_curenta < @versiune)
	BEGIN
		WHILE @versiune_curenta < @versiune
		BEGIN
			SET @versiune_curenta += 1
			DECLARE @proc VARCHAR(20) = CONCAT('do_procedura', @versiune_curenta)
			PRINT 'Se executa: ' + @proc
			EXEC @proc
			UPDATE Versiune SET nr_versiune = @versiune_curenta
		END
	END
	ELSE
	BEGIN
		WHILE @versiune_curenta > @versiune
		BEGIN
			DECLARE @undo_proc VARCHAR(20) = CONCAT('undo_procedura', @versiune_curenta)
			PRINT 'Se executa: ' + @undo_proc
			EXEC @undo_proc
			SET @versiune_curenta -= 1
			UPDATE Versiune SET nr_versiune = @versiune_curenta
		END
	END

	IF (@versiune != @versiune_curenta)
	BEGIN
		RAISERROR('Versiunea nu a fost actualizata corect!', 16, 1)
	END
END
GO

exec do_procedura1 
exec undo_procedura1

exec do_procedura2
exec undo_procedura2

exec do_procedura3
exec undo_procedura3

exec do_procedura4
exec undo_procedura4

exec do_procedura5
exec undo_procedura5

exec main 0
exec main 1
exec main 2
exec main 3
exec main 4
exec main 5

exec main -100