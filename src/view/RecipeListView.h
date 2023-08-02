#ifndef RECIPE_LIST_VIEW_H
#define RECIPE_LIST_VIEW_H

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>

#include "wx/listctrl.h"
#include "wx/event.h"

class IRecipeListCallback;

class IRecipeListView {
public:
    virtual void setRecipes(const std::vector<Recipe> &recipes) = 0;
    virtual void setSelected(int idx) = 0;
};

class RecipeListView : public wxEvtHandler, public IRecipeListView
{
private:
    wxListView *m_recipesListView;
    IRecipeListCallback *m_recipeListCallback;

protected:
    void onRecipeSelChange(wxListEvent &event);

public:
    RecipeListView(IRecipeListCallback *callback);

    void createRecipeListPanel(wxPanel *parent);

    void setRecipes(const std::vector<Recipe> &recipes) override;
    void setSelected(int idx) override;

};

#endif // RECIPE_LIST_VIEW_H