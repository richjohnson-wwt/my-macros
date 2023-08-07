#ifndef FAT_SECRET_MODEL_H
#define FAT_SECRET_MODEL_H

#include "../MyMacroTypes.h"
#include "../db/DbFood.h"

class IFatSecretModel {
public:
    virtual Unit getUnit(const std::string& name) = 0;
    virtual void saveFood(const Food& f) = 0;
};

class FatSecretModel : public IFatSecretModel {
private:
    DbFood *m_dbFood;

public:
    FatSecretModel(DbFood *db);
    Unit getUnit(const std::string& name) override;
    void saveFood(const Food& f) override;

};

#endif // FAT_SECRET_MODEL_H