using lab10_map;
using lab10_map.domain;
using lab10_map.repository;
using lab10_map.service;

IRepository<Elev, int> elevRepo = new ElevFileRepository("C:\\Users\\emanu\\RiderProjects\\lab10_map\\lab10_map\\data\\elevi.txt");
IRepository<Jucator, int> jucatorRepo = new JucatorFileRepository("C:\\Users\\emanu\\RiderProjects\\lab10_map\\lab10_map\\data\\jucatori.txt");
IRepository<JucatorActiv, int> jucatorActivRepo = new JucatorActivFileRepository("C:\\Users\\emanu\\RiderProjects\\lab10_map\\lab10_map\\data\\jucatoriactivi.txt");
IRepository<Echipa, int> echipaRepo = new EchipaFileRepository("C:\\Users\\emanu\\RiderProjects\\lab10_map\\lab10_map\\data\\echipe.txt");
IRepository<Meci, int> meciRepo = new MeciFileRepository("C:\\Users\\emanu\\RiderProjects\\lab10_map\\lab10_map\\data\\meciuri.txt");

Service service = new Service(elevRepo, echipaRepo, jucatorRepo, jucatorActivRepo, meciRepo);

foreach (var jucator in service.getJucatoriEchipa(1))
{
    Console.WriteLine(jucator);
}

foreach (var jucatorActiv in service.getJucatoriActiviEchipaMeci(1, 1))
{
    Console.WriteLine(jucatorActiv);
}

foreach (var meci in service.getMeciuriPerioada(DateTime.Parse("2023-01-01"), DateTime.Parse("2023-02-01")))
{
    Console.WriteLine(meci);
}

var scorMeci = service.getScorMeci(1);
foreach (var entry in scorMeci)
{
    Console.WriteLine(service.getEchipa(entry.Key).nume + " : " + entry.Value);
}