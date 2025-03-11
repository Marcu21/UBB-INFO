namespace lab10_map.domain;

public class Jucator: Elev
{
    public int echipaId { get; set; }
    
    public override string ToString()
    {
        return "Jucator{Id=" + Id + ", nume=" + nume + ", scoala=" + scoala + ", echipaId=" + echipaId + "}";
    }
}