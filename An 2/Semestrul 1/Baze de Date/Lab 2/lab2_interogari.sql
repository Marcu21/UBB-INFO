USE FirmaTaxi3
GO

--5 where 1 2 3 4 5 6
--3 group by 1 2 3
--2 distinct 1 2
--2 having 1 2 3
--7 informatii din mai mult de 2 tabele 1 2 3 4 5 6 7
--2 tabele m-n 1 2

--1. Afiseaza cursele care au costat mai mult de 50 de lei, oferind informatii despre sofer si vehicul
--where + informatii din mai mult de 2 tabele
SELECT c.cod_cursa, s.nume AS Nume_Sofer, v.marca, c.pornire, c.destinatie, c.cost
FROM Curse c
INNER JOIN Soferi s ON c.cod_sofer = s.cod_sofer
INNER JOIN Vehicule v ON c.cod_vehicul = v.cod_vehicul
WHERE c.cost > 50;

--2. Afiseaza vehiculele fabricate dupa 2018 si au un cost mediu de peste 15 lei / cursa, oferind informatii despre cursa si sofer
--where + group by + having + informatii din mai mult de 2 tabele + tabele m-n
SELECT v.marca, numar_inmatriculare, COUNT(*) AS Numar_Curse, AVG(c.cost) AS Cost_Mediu, MIN(s.nume) AS Nume_Sofer
FROM Vehicule v
INNER JOIN Curse c ON v.cod_vehicul = c.cod_vehicul
INNER JOIN Relatie_Soferi_Vehicule rsv ON v.cod_vehicul = rsv.cod_vehicul
INNER JOIN Soferi s ON rsv.cod_sofer = s.cod_sofer
WHERE v.an_fabricatie > 2018
GROUP BY v.marca, v.numar_inmatriculare
HAVING AVG(c.cost) > 15;

--3. Afiseaza detalii despre curse, sofer si client pentru cursele cu distanta de peste 10 km
--where + informatii din mai mult de 2 tabele
SELECT c.cod_cursa, s.nume AS Nume_Sofer, cl.nume AS Nume_Client, c.distanta
FROM Curse c
INNER JOIN Soferi s ON c.cod_sofer = s.cod_sofer
INNER JOIN Clienti cl ON c.cod_client = cl.cod_client
WHERE c.distanta > 10;

--4. Afiseaza clientii cu o singura cursa, cheltuielile, distanta si tipul de plata folosit
--group by + having + informatii din mai mult de 2 tabele
SELECT cl.nume, COUNT(c.cod_cursa) AS Numar_Curse, SUM(c.cost) AS Cheltuieli, SUM(c.distanta) AS KM, p.tip_plata
FROM Clienti cl
LEFT JOIN Curse c ON cl.cod_client = c.cod_client
LEFT JOIN Plati p ON c.cod_plata = p.cod_plata
GROUP BY cl.nume, p.tip_plata
HAVING COUNT(c.cod_cursa) = 1;

--5. Afiseaza clientii unici care au oferit atat rating-uri, cat si reclamatii
--distinct + informatii din mai mult de 2 tabele
SELECT DISTINCT cl.nume
FROM Clienti cl
INNER JOIN Rating ra ON cl.cod_client = ra.cod_client
INNER JOIN Reclamatii re ON cl.cod_client = re.cod_client;

--6. Afiseaza soferii, respectiv masinile pe care le-au condus, intr-un interval de timp specific
--where + informatii din mai mult de 2 tabele + tabele m-n
SELECT s.nume, v.marca, v.model
FROM Soferi s
INNER JOIN Relatie_Soferi_Vehicule rsv ON s.cod_sofer = rsv.cod_sofer
INNER JOIN Vehicule v ON rsv.cod_vehicul = v.cod_vehicul
WHERE rsv.data_inceput > '2024-10-19' AND rsv.data_sfarsit < '2024-10-20';

--7. Afiseaza rating-ul general al fiecarui sofer cu scor mediu sub 3
--group by + having + informatii din mai mult de 2 tabele
SELECT s.nume, AVG(r.scor) AS Scor_Mediu
FROM Soferi s
INNER JOIN Curse c ON s.cod_sofer = c.cod_sofer
INNER JOIN Rating r ON c.cod_cursa = r.cod_cursa
GROUP BY s.nume
HAVING AVG(r.scor) < 3;

--8. Afiseaza toti soferii care au efectuat curse de peste 15km
--where
SELECT DISTINCT s.nume
FROM Soferi s
INNER JOIN Curse c ON s.cod_sofer = c.cod_sofer
WHERE c.distanta > 15;

--9. Afiseaza marcile unice de vehicule
--distinct
SELECT DISTINCT v.marca
FROM Vehicule v

--10. Afiseaza vehiculele aflate in garajul pentru taxiuri
--where
SELECT v.marca, v.model, v.numar_inmatriculare, g.nume AS Nume_Garaj, g.locatie AS Locatie_Garaj
FROM Vehicule v
INNER JOIN Garaje g ON v.cod_garaj = g.cod_garaj
WHERE g.nume = 'Garaj Taxiuri';