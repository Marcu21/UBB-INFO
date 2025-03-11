#include <stdexcept>
#include "validator.h"

void Validator::validate(Utilaj u) {
    //Valideaza un utilaj
    string errors = "";
    if (u.get_id() < 0)
        errors += "Id-ul nu poate fi negativ!\n";
    if (u.get_denumire().empty() == 1)
        errors += "Denumirea nu poate fi vida!\n";
    if (u.get_tip().empty() == 1)
        errors += "Tipul nu poate fi vid!\n";
    if (u.get_cilindrii() != 1 && u.get_cilindrii() != 2 && u.get_cilindrii() != 4 && u.get_cilindrii() != 6 && u.get_cilindrii() != 8)
        errors += "Numarul de cilindrii nu poate fi negativ!\n";
    if (errors.size() > 0)
        throw std::runtime_error(errors);
}