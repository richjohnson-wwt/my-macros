#include "FoodCommonModel.h"

#include <spdlog/spdlog.h>

bool FoodCommonModel::isInEditMode() const
{
    spdlog::debug("FoodCommonModel::isInEditMode {}", m_inEditMode);
    return m_inEditMode;
}

void FoodCommonModel::setInEditMode(bool inEditMode)
{
    spdlog::debug("FoodCommonModel::setInEditMode {}", inEditMode);
    m_inEditMode = inEditMode;
}