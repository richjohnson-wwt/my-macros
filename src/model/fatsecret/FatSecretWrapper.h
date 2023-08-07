#ifndef FAT_SECRET_WRAPPER_H
#define FAT_SECRET_WRAPPER_H


#include "CurlWrapper.h"

#include "FatSecretJson.h"
#include "FatSecretModel.h"
#include "Transformer.h"

class FatSecretWrapper {
public:
    FatSecretWrapper(IFatSecretModel *fatSecretModel);
    void refreshToken();
    FatSecret::SearchFoods searchFoods(std::string& name);
    FatSecret::GetFood getFood(const std::string& id);
    void addGetFoodToDb();

private:
    IFatSecretModel *m_fatSecretModel;
    CurlWrapper m_curlWrapper;
    FatSecret::FatSecretJson m_fatSecretJson;
    Transformer m_transformer;

    void writeTokenToFile(const std::string& token);
};

#endif // FAT_SECRET_WRAPPER_H