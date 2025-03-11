USE FirmaTaxi3
GO
INSERT INTO Garaje (cod_garaj, nume, locatie, capacitate) VALUES
(1, 'Garaj Personal', 'MV80', 10),
(2, 'Garaj Taxiuri', 'MV80', 60);
INSERT INTO Vehicule (marca, model, an_fabricatie, numar_inmatriculare, cod_garaj) VALUES
('Mercedes', 'Cls', 2020, 'SM80MRC', 1),
('Mercedes', 'E-Coupe', 2019, 'SM21MRC', 1),
('Opel', 'Astra-K', 2022, 'SM10NOP', 2),
('Opel', 'Astra-J', 2016, 'SM63VON', 2);
INSERT INTO Soferi (nume, CNP, numar_telefon) VALUES
('Emanuel Marcu', '5040821303709', '0753557733'),
('Csabi Sandor', '1890715123456', '0723123456'),
('Florentina Popescu', '2900520123456', '0723123457'),
('Marius Craiut', '1880501123456', '0723123458');
INSERT INTO Clienti (cod_client, nume, numar_telefon) VALUES
(1, 'Raul Parau', '0752683911'),
(2, 'Alex Danciu', '0743794108'),
(3, 'Gyuri Bae', '0756123458');
INSERT INTO Tarife (cod_tarif, pret_pornire, pret_km) VALUES
(1, 3.20, 3.20),
(2, 5, 5);
INSERT INTO Plati (cod_plata, tip_plata) VALUES
(1, 'cash'),
(2, 'card');
INSERT INTO Curse (cod_cursa, cod_sofer, cod_vehicul, cod_client, pornire, destinatie, distanta, cost, cod_tarif, cod_plata) VALUES
(1, 1, 1, 1, 'Statie Carei', 'Mall Satu Mare', 33.5, 172.5, 2, 1),
(2, 2, 2, 2, 'Bizarre Foods', 'Grande', 3.0, 20.00, 2, 2),
(3, 3, 3, 3, 'Times', 'Gara', 4.5, 17.6, 1, 1),
(4, 4, 4, 1, 'Dindesti', 'Continental Carei', 23, 76.8, 1, 1);
INSERT INTO Reclamatii (cod_cursa, cod_client, descriere, data_reclamatie) VALUES
(1, 1, 'Soferul conduce prea agresiv', '2024-10-19'),
(3, 3, 'Masina era murdara', '2024-10-06');
INSERT INTO Rating (cod_cursa, cod_client, scor, descriere) VALUES
(1, 1, 1, 'Era sa mor!'),
(2, 2, 5, 'Foarte curat si punctual'),
(3, 3, 2, 'Masina nu a fost curata'),
(4, 1, 5, 'Soferul mi-a pus Tzanca Uraganu');
INSERT INTO Program_Soferi (cod_program, cod_sofer, ziua, ora_inceput, ora_sfarsit) VALUES
(1, 1, 'Sambata', '08:00', '16:00'),
(2, 1, 'Duminica', '12:00', '14:00'),
(3, 2, 'Luni', '07:00', '19:00'),
(4, 2, 'Marti', '05:00', '14:00'),
(5, 3, 'Miercuri', '14:00', '23:59'),
(6, 4, 'Miercuri', '05:00', '18:00');
INSERT INTO Relatie_Soferi_Vehicule (cod_relatie, cod_sofer, cod_vehicul, data_inceput, data_sfarsit) VALUES
(1, 1, 1, '2024-10-19 08:00:00', '2024-10-19 16:00:00'),
(2, 2, 2, '2024-10-19 07:00:00', '2024-10-19 19:00:00'),
(3, 1, 2, '2024-10-20 12:00:00', '2024-10-20 14:00:00'),
(4, 3, 3, '2024-10-23 14:00:00', '2024-10-20 23:59:59'),
(5, 4, 3, '2024-10-23 05:00:00', '2024-10-23 18:00:00');

