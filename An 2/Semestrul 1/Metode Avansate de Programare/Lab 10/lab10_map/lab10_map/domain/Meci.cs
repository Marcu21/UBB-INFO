namespace lab10_map.domain;

public class Meci: Entity<int>
{
    public int gazdaId { get; set; }
    public int oaspeteId { get; set; }
    public DateTime data { get; set; }
    
    public override string ToString()
    {
        return "Meci{Id=" + Id + ", gazdaId=" + gazdaId + ", oaspeteId=" + oaspeteId + ", data=" + data + "}";
    }
}