#ifndef FATSECRET_H
#define FATSECRET_H

#include "MyMacroTypes.h"
#include "FatSecretModel.h"


class Transformer {
private:

public:
    Food convert(const FatSecret::GetFood& getFood, Unit unit);
};

#endif // FATSECRET_H