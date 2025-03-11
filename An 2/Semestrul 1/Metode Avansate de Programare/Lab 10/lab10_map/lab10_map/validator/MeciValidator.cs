using lab10_map.domain;

namespace lab10_map;

public class MeciValidator : IValidator<Meci>
{
    public void Validate(Meci meci)
    {
        if (meci.data == default)
            throw new Exception("Match date must be set.");
        if(meci.gazdaId <= 0 || meci.oaspeteId <= 0)
            throw new Exception("Team IDs must be positive.");
        if (meci.gazdaId == meci.oaspeteId)
            throw new Exception("A match cannot have the same team on both sides.");
    }
}
