namespace lab10_map.domain;

public class Echipa: Entity<int>
{ 
    public string nume { get; set; }

    public override string ToString()
    {
        return "Echipa{Id=" + Id + ", nume=" + nume + "}";
    }
}