using lab10_map.domain;

namespace lab10_map.repository;

public class JucatorActivFileRepository: FileRepository<JucatorActiv, int>
{
    public JucatorActivFileRepository(string filePath) : base(filePath, StringToEntity, EntityToString){}
    public static JucatorActiv StringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        int idJucator = int.Parse(tokens[1]);
        int idMeci = int.Parse(tokens[2]);
        int nrPuncteInscrise = int.Parse(tokens[3]);
        TipJucator tip = (TipJucator)Enum.Parse(typeof(TipJucator), tokens[4]);
        return new JucatorActiv { Id = id, JucatorId = idJucator, MeciId = idMeci, NrPuncteInscrise = nrPuncteInscrise, Tip = tip };
    }

    public static string EntityToString(JucatorActiv jucatorActiv)
    {
        return jucatorActiv.Id + "," + jucatorActiv.JucatorId + "," + jucatorActiv.MeciId + "," + jucatorActiv.NrPuncteInscrise + "," + jucatorActiv.Tip;
    }
}