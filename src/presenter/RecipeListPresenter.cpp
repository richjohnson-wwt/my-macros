#include "RecipeListPresenter.h"

#include <spdlog/spdlog.h>

RecipeListPresenter::RecipeListPresenter(RecipeListView *view, IRecipeModel *model)
: m_recipeModel(model), m_recipeListView(view) {

}

void RecipeListPresenter::onRecipeSelected(int id) {
    spdlog::debug("RecipeListPresenter::onRecipeSelected({})", id);
    m_recipeModel->setSelectedId(id);
}

void RecipeListPresenter::setActive() {
    spdlog::debug("RecipeListPresenter::setActive with id({})", m_recipeModel->getSelectedId());
    m_recipeListView->setRecipes(m_recipeModel->getRecipes());
    m_recipeListView->setSelected(m_recipeModel->getSelectedId());
}
