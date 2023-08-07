#include "RecipeCommonModel.h"

#include <spdlog/spdlog.h>

bool RecipeCommonModel::isInEditMode() const
{
    spdlog::debug("RecipeCommonModel::isInEditMode {}", m_inEditMode);
    return m_inEditMode;
}

void RecipeCommonModel::setInEditMode(bool inEditMode)
{
    spdlog::debug("RecipeCommonModel::setInEditMode {}", inEditMode);
    m_inEditMode = inEditMode;
}