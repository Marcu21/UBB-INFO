using lab10_map.domain;
using lab10_map.repository;

namespace lab10_map.service;

public class Service
{
    private IRepository<Elev, int> elevRepo;
    private IRepository<Echipa, int> echipaRepo;
    private IRepository<Jucator, int> jucatorRepo;
    private IRepository<JucatorActiv, int> jucatorActivRepo;
    private IRepository<Meci, int> meciRepo;


    public Service(IRepository<Elev, int> elevRepo, IRepository<Echipa, int> echipaRepo,
        IRepository<Jucator, int> jucatorRepo, IRepository<JucatorActiv, int> jucatorActivRepo,
        IRepository<Meci, int> meciRepo)
    {
        this.elevRepo = elevRepo;
        this.echipaRepo = echipaRepo;
        this.jucatorRepo = jucatorRepo;
        this.jucatorActivRepo = jucatorActivRepo;
        this.meciRepo = meciRepo;
    }

    public IEnumerable<Jucator> getJucatoriEchipa(int echipaId)
    {
        return jucatorRepo.FindAll().Where(jucator => jucator.echipaId == echipaId);
    }

    public IEnumerable<JucatorActiv> getJucatoriActiviEchipaMeci(int echipaId, int meciId)
    {
        return jucatorActivRepo.FindAll().Where(jucatorActiv =>
            jucatorActiv.MeciId == meciId && jucatorRepo.FindOne(jucatorActiv.JucatorId).echipaId == echipaId);
    }

    public IEnumerable<Meci> getMeciuriPerioada(DateTime start, DateTime end)
    {
        return meciRepo.FindAll().Where(meci => meci.data.CompareTo(start) >= 0 && meci.data.CompareTo(end) <= 0);
    }

    /*public int getScorMeci(int meciId)
    {
        var jucatoriMeci = jucatorActivRepo.FindAll().Where(jucatorActiv => jucatorActiv.MeciId == meciId);
        return jucatoriMeci.Sum(jucatorActiv => jucatorActiv.NrPuncteInscrise);
    }*/
    
    public Dictionary<int, int> getScorMeci(int meciId)
    {
        var jucatoriMeci = jucatorActivRepo.FindAll().Where(jucatorActiv => jucatorActiv.MeciId == meciId);
        
        return jucatoriMeci
            .GroupBy(jucatorActiv => jucatorRepo.FindOne(jucatorActiv.JucatorId).echipaId)
            .ToDictionary(group => group.Key, group => group.Sum(jucatorActiv => jucatorActiv.NrPuncteInscrise));
    }

    public Echipa getEchipa(int echipaId)
    {
        return echipaRepo.FindOne(echipaId);
    }
}
