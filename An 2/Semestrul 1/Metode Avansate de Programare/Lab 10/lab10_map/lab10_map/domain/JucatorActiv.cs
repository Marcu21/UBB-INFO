namespace lab10_map.domain;

public enum TipJucator
{
    Rezerva,
    Participant
}

public class JucatorActiv : Entity<int>
{
    public int JucatorId { get; set; }
    public int MeciId { get; set; }
    public int NrPuncteInscrise { get; set; }
    public TipJucator Tip { get; set; }

    public override string ToString()
    {
        return "JucatorActiv{Id=" + Id + ", JucatorId=" + JucatorId + ", MeciId=" + MeciId + ", NrPuncteInscrise=" + NrPuncteInscrise + ", Tip=" + Tip + "}";
    }
}