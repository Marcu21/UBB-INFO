#include <stdexcept>
#include "validator.h"

void Validator::validate(Melodie melodie) {
    string errors = "";
    if(melodie.get_id() < 0)
        errors += "Id-ul nu poate fi negativ!\n";
    if(melodie.get_titlu().empty() == 1)
        errors += "Titlul nu poate fi vid!\n";
    if(melodie.get_artist().empty() == 1)
        errors += "Artistul nu poate fi vid!\n";
    if(!(melodie.get_gen()=="pop"||melodie.get_gen()=="rock"||melodie.get_gen()=="folk"||melodie.get_gen()=="disco"))
        errors += "Genul este invalid!\n";
    if (errors.size() > 0)
        throw std::runtime_error(errors);
}