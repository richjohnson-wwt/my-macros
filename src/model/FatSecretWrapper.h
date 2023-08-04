#ifndef FAT_SECRET_WRAPPER_H
#define FAT_SECRET_WRAPPER_H

#include "DbFood.h"
#include "CurlWrapper.h"

#include "FatSecretModel.h"

#include "Transformer.h"

class FatSecretWrapper {
public:
    FatSecretWrapper(DbFood *dbFood);
    void refreshToken();
    FatSecret::SearchFoods searchFoods(std::string& name);
    FatSecret::GetFood getFood(const std::string& id);
    void addGetFoodToDb();

private:
    DbFood *m_dbFood;
    CurlWrapper m_curlWrapper;
    FatSecret::FatSecretModel m_fatSecretModel;
    Transformer m_transformer;

    void writeTokenToFile(const std::string& token);
};

#endif // FAT_SECRET_WRAPPER_H