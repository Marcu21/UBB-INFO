using lab10_map.domain;

namespace lab10_map.repository;

public class MeciFileRepository: FileRepository<Meci, int>
{
    public MeciFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Meci StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        int idEchipa1 = int.Parse(tokens[1]);
        int idEchipa2 = int.Parse(tokens[2]);
        DateTime data = DateTime.Parse(tokens[3]);
        return new Meci { Id = id, gazdaId = idEchipa1, oaspeteId = idEchipa2, data = data };
    }

    public static string EntityToString(Meci meci)
    {
        return meci.Id + "," + meci.gazdaId + "," + meci.oaspeteId + "," + meci.data;
    }
}