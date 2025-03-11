using lab10_map.domain;

namespace lab10_map;

public class EchipaValidator : IValidator<Echipa>
{
    public void Validate(Echipa echipa)
    {
        if (string.IsNullOrEmpty(echipa.nume))
            throw new Exception("Team name cannot be null or empty.");
    }
}
