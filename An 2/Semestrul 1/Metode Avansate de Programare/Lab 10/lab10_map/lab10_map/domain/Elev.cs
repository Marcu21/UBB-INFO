namespace lab10_map.domain;

public class Elev: Entity<int>
{
    public string nume { get; set; }
    public string scoala { get; set; }
    
    public override string ToString()
    {
        return "Elev{Id=" + Id + ", nume=" + nume + ", scoala=" + scoala + "}";
    }
}