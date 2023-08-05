#ifndef FAT_SECRET_WRAPPER_H
#define FAT_SECRET_WRAPPER_H

#include "FoodModel.h"
#include "CurlWrapper.h"

#include "FatSecretModel.h"

#include "Transformer.h"

class FatSecretWrapper {
public:
    FatSecretWrapper(IFoodModel *foodModel);
    void refreshToken();
    FatSecret::SearchFoods searchFoods(std::string& name);
    FatSecret::GetFood getFood(const std::string& id);
    void addGetFoodToDb();

private:
    IFoodModel *m_foodModel;
    CurlWrapper m_curlWrapper;
    FatSecret::FatSecretModel m_fatSecretModel;
    Transformer m_transformer;

    void writeTokenToFile(const std::string& token);
};

#endif // FAT_SECRET_WRAPPER_H