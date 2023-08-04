#ifndef FAT_SECRET_WRAPPER_H
#define FAT_SECRET_WRAPPER_H

#include "Db.h"
#include "CurlWrapper.h"

#include "FatSecretModel.h"

#include "Transformer.h"

class FatSecretWrapper {
public:
    FatSecretWrapper();
    void refreshToken();
    FatSecret::SearchFoods searchFoods(std::string& name);
    FatSecret::GetFood getFood(const std::string& id);
    void addFoodById(const std::string& id);

private:
    Db m_dbConnection;
    CurlWrapper m_curlWrapper;
    FatSecret::FatSecretModel m_fatSecretModel;
    Transformer m_transformer;

    void writeTokenToFile(const std::string& token);
};

#endif // FAT_SECRET_WRAPPER_H