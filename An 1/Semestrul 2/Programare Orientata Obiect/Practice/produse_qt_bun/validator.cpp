#include "validator.h"
#include <string>
#include <stdexcept>

void Validator::validate_produs(Produs produs)
{
    std::string errors = "";
    if (produs.get_id() < 0)
        errors += "Id-ul este negativ!\n";
    if (produs.get_nume().empty() == 1)
        errors += "Numele produsului este vid!!\n";
    if (produs.get_tip().empty() == 1)
        errors += "Tipul produsului este vid!\n";
    if (produs.get_pret() < 0.0)
        errors += "Pretul produsului este negativ!\n";
    if (errors.size() > 0)
        throw std::runtime_error(errors);
}