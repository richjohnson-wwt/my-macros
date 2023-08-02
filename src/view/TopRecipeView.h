#ifndef TOP_RECIPE_VIEW_H
#define TOP_RECIPE_VIEW_H

#include "RecipeListView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IRecipeCallback;

class ITopRecipeView {
public:    
};

class TopRecipeView : public wxEvtHandler, public ITopRecipeView {
private:
    RecipeListView *m_recipeListView;
    wxSplitterWindow *m_splitter;

    IRecipeCallback *m_recipeCallback;

    wxPanel *createRightFoodItemPanel(wxWindow *parent);
    wxPanel *createRecipeItemPanel(wxWindow *parent);

    wxTextCtrl *m_recipeIdTextCtrl;
    wxTextCtrl *m_recipeNameTextCtrl;
    wxTextCtrl *m_recipeDescriptionTextCtrl;
    wxTextCtrl *m_recipeUrlTextCtrl;
    wxTextCtrl *m_recipeServingsTextCtrl;
    wxTextCtrl *m_recipeInstructionsTextCtrl;

    wxListView *m_recipeIngredientsListView;

    wxTextCtrl *m_recipeIngredientMultiplierTextCtrl;
    wxButton *m_addRecipeIngredientButton;
    wxButton *m_deleteRecipeIngredientButton;

    wxButton *m_recipeDeleteButton;
    wxButton *m_recipeSaveButton;
    wxButton *m_recipeNewButton;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel, 
        const wxString& label,
         wxTextCtrl *text);

protected:
    protected:
    // Left List View
    void OnPositionChanging(wxSplitterEvent &event);

    // Right Item View
    void onAddIngredient(wxCommandEvent &event);
    void onDeleteIngredient(wxCommandEvent& event);
    void onIngredientSelChange(wxListEvent& event);
    void onDeleteRecipe(wxCommandEvent &event);
    void onSaveRecipe(wxCommandEvent &event);
    void onNewRecipe(wxCommandEvent &event);
    
public:
    TopRecipeView(IRecipeCallback *callback, RecipeListView *recipeListView);

    wxPanel *createRecipePanel(wxNotebook *parent);
};

#endif // TOP_RECIPE_VIEW_H