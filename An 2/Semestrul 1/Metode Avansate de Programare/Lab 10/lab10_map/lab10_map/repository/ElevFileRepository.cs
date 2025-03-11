using lab10_map.domain;

namespace lab10_map.repository;


public class ElevFileRepository: FileRepository<Elev, int>
{
    public ElevFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static Elev StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        if (tokens.Length != 3)
        {
            throw new FormatException($"Line '{line}' does not contain exactly three comma-separated values.");
        }
        int id = int.Parse(tokens[0]);
        string nume = tokens[1];
        string scoala = tokens[2];
        return new Elev { Id = id, nume = nume, scoala = scoala };
    }

    public static string EntityToString(Elev elev)
    {
        return elev.Id + "," + elev.nume + "," + elev.scoala;
    }
}