using lab10_map.domain;

namespace lab10_map.repository;

public class EchipaFileRepository: FileRepository<Echipa, int>
{
    public EchipaFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Echipa StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        string nume = tokens[1];
        return new Echipa { Id = id, nume = nume };
    }

    public static string EntityToString(Echipa echipa)
    {
        return echipa.Id + "," + echipa.nume;
    }
}