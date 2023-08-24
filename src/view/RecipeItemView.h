#ifndef RECIPE_ITEM_VIEW_H
#define RECIPE_ITEM_VIEW_H

#include "../model/MyMacroTypes.h"
#include "RecipeEditView.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"
#include <wx/hyperlink.h>

class IRecipeCallback;

class IRecipeItemView
{
public:
    virtual void setRecipeId(const std::string &id) = 0;
    virtual void setRecipeName(const std::string &name) = 0;
    virtual void setRecipeDescription(const std::string &description) = 0;
    virtual void setRecipeUrl(const std::string &url) = 0;
    virtual void setRecipeServings(const std::string &servings) = 0;
    virtual void setRecipeInstructions(const std::string &instructions) = 0;
    virtual void setRecipeIngredients(const std::vector<Ingredient> &ingredients) = 0;
    virtual void insertNewPage(bool isNew) = 0;
    virtual void setButtonStatus(bool isEdit) = 0;

    virtual void setMacroCalories(const std::string& calories) = 0;
    virtual void setFatPercent(const std::string& percent) = 0;
    virtual void setProteinPercent(const std::string& percent) = 0;
    virtual void setCarbPercent(const std::string& percent) = 0;
};

class RecipeItemView : public wxEvtHandler, public IRecipeItemView
{
private:
    IRecipeCallback *m_recipeCallback;
    wxNotebook *m_parent;
    RecipeEditView *m_recipeEditView;

    void createRightFoodItemPanel(wxPanel *panel);

    wxTextCtrl *m_recipeIdTextCtrl;
    wxTextCtrl *m_recipeNameTextCtrl;
    wxTextCtrl *m_recipeDescriptionTextCtrl;
    wxHyperlinkCtrl *m_recipeUrlHyperlinkCtrl;
    wxTextCtrl *m_recipeServingsTextCtrl;
    wxTextCtrl *m_recipeInstructionsTextCtrl;
    wxListView *m_recipeIngredientsListView;

    wxButton *m_recipeDeleteButton;
    wxButton *m_recipeNewButton;
    wxButton *m_recipeEditButton;

    wxTextCtrl *m_macroCaloriesPerServingTextCtrl;
    wxTextCtrl *m_macroFatPercentPerServingTextCtrl;
    wxTextCtrl *m_macroProteinPercentPerServingTextCtrl;
    wxTextCtrl *m_macroCarbPercentPerServingTextCtrl;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);

protected:
    void onDeleteRecipe(wxCommandEvent &event);
    void onNewRecipe(wxCommandEvent &event);
    void onEditRecipe(wxCommandEvent &event);

public:
    RecipeItemView(IRecipeCallback *callback, RecipeEditView *recipeEditView);

    wxPanel *createRecipeItemPanel(wxNotebook *parent);
    void onNotebookPageChanged();

    void setRecipeId(const std::string &id) override;
    void setRecipeName(const std::string &name) override;
    void setRecipeDescription(const std::string &description) override;
    void setRecipeUrl(const std::string &url) override;
    void setRecipeServings(const std::string &servings) override;
    void setRecipeInstructions(const std::string &instructions) override;
    void setRecipeIngredients(const std::vector<Ingredient> &ingredients) override;

    void insertNewPage(bool isNew) override;
    void setButtonStatus(bool isEdit) override;

    void setMacroCalories(const std::string& calories) override;
    void setFatPercent(const std::string& percent) override;
    void setProteinPercent(const std::string& percent) override;
    void setCarbPercent(const std::string& percent) override;
};

#endif // RECIPE_ITEM_VIEW_H