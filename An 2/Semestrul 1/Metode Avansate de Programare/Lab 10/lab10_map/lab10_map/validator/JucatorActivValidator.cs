using lab10_map.domain;

namespace lab10_map;

public class JucatorActivValidator : IValidator<JucatorActiv>
{
    public void Validate(JucatorActiv jucatorActiv)
    {
        if (jucatorActiv.NrPuncteInscrise < 0)
            throw new Exception("Points scored cannot be negative.");
        
        if (jucatorActiv.Tip != TipJucator.Rezerva && jucatorActiv.Tip != TipJucator.Participant)
            throw new Exception("Invalid participation type.");
    }
}
