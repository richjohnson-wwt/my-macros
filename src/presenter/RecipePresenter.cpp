#include "RecipePresenter.h"

#include <spdlog/spdlog.h>

RecipePresenter::RecipePresenter(ITopRecipeView *view, IRecipeModel *model): m_recipeModel(model), m_topRecipeView(view)
{
}

void RecipePresenter::setActive()
{
    spdlog::info("RecipePresenter::setActive");
    
}
