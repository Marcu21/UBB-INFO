#pragma once
#include <string>
#include "../domain/locatar.h"
using std::string;


class validator
{
public:
    static void validate_locatar(const Locatar& locatar);
};