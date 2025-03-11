using lab10_map.domain;

namespace lab10_map;

public class JucatorValidator: IValidator<Jucator>
{
    public void Validate(Jucator jucator)
    {
        if (string.IsNullOrEmpty(jucator.nume))
            throw new Exception("Player name cannot be null or empty.");
        
        if (string.IsNullOrEmpty(jucator.scoala))
            throw new Exception("Player must be associated with a school.");
        
        if (jucator.echipaId <= 0)
            throw new Exception("Player must be associated with a valid team.");
    }
}