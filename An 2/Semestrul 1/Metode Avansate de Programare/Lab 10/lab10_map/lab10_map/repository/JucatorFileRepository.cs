using lab10_map.domain;

namespace lab10_map.repository;

public class JucatorFileRepository: FileRepository<Jucator, int>
{
    public JucatorFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Jucator StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        string nume = tokens[1];
        string scoala = tokens[2];
        int echipaId = int.Parse(tokens[3]);
        return new Jucator { Id = id, nume = nume, scoala = scoala, echipaId = echipaId };
    }

    public static string EntityToString(Jucator jucator)
    {
        return jucator.Id + "," + jucator.nume + "," + jucator.scoala + "," + jucator.echipaId;
    }
}