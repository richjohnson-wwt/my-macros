#ifndef FAT_SECRET_WRAPPER_H
#define FAT_SECRET_WRAPPER_H


#include "CurlWrapper.h"

#include "FatSecretModel.h"

#include "Transformer.h"

class IFoodEditModel;

class FatSecretWrapper {
public:
    FatSecretWrapper(IFoodEditModel *foodModel);
    void refreshToken();
    FatSecret::SearchFoods searchFoods(std::string& name);
    FatSecret::GetFood getFood(const std::string& id);
    void addGetFoodToDb();

private:
    IFoodEditModel *m_foodModel;
    CurlWrapper m_curlWrapper;
    FatSecret::FatSecretModel m_fatSecretModel;
    Transformer m_transformer;

    void writeTokenToFile(const std::string& token);
};

#endif // FAT_SECRET_WRAPPER_H