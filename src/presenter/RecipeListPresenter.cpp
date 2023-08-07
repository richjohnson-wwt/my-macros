#include "RecipeListPresenter.h"
#include "../model/db/DbRecipe.h"
#include <spdlog/spdlog.h>

RecipeListPresenter::RecipeListPresenter(RecipeListView *view, IRecipeListModel *model, IDbRecipeSubject *recipeSubject)
: m_recipeListModel(model), m_recipeListView(view), m_dbRecipeSubject(recipeSubject) {

}

void RecipeListPresenter::postInit() {
    spdlog::debug("RecipeListPresenter::postInit");
    m_dbRecipeSubject->attach(this);
    update();
}

void RecipeListPresenter::onRecipeSelected(int id) {
    spdlog::debug("RecipeListPresenter::onRecipeSelected({})", id);
    m_recipeListModel->setSelectedId(id);
}

void RecipeListPresenter::update() {
    spdlog::debug("RecipeListPresenter::update");
    m_recipeListView->setRecipes(m_recipeListModel->getRecipes());
    m_recipeListView->setSelected(m_recipeListModel->getSelectedId());
}