#include "validator.h"
#include <string>
#include <stdexcept>

using std::string;

void Validator::validate_melodie(const Melodie& melodie)
{
    string errors = "";
    if (melodie.get_id() < 0)
        errors += "Id-ul nu poate fi negativ!\n";
    if (melodie.get_titlu().size() == 0)
        errors += "Titlul nu poate fi vid!\n";
    if (melodie.get_artist().size() == 0)
        errors += "Artistul nu poate fi vid!\n";
    if (melodie.get_rank() < 1 || melodie.get_rank() > 10)
        errors += "Rank-ul trebuie safie intre 1 si 10!\n";
    if (errors.size() > 0)
        throw std::runtime_error(errors);
}