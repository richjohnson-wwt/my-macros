#include "FatSecretModel.h"
#include <spdlog/spdlog.h>

FatSecretModel::FatSecretModel(DbFood *db): m_dbFood(db)
{
}

Unit FatSecretModel::getUnit(const std::string &name)
{
    return m_dbFood->getUnit(name);
}

void FatSecretModel::saveFood(const Food& f) {
    spdlog::info("FatSecretModel::saveFood");
    m_dbFood->addNewFood(f);
}