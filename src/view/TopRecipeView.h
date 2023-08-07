#ifndef TOP_RECIPE_VIEW_H
#define TOP_RECIPE_VIEW_H

#include "RecipeItemView.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/event.h"


class TopRecipeView : public wxEvtHandler
{
private:
    RecipeItemView *m_recipeItemView;

    wxNotebook *m_recipeBookCtrl;

protected:
    void onNotebookPageChanged(wxCommandEvent &event);

public:
    TopRecipeView(RecipeItemView *recipeItemView);

    wxPanel *createRecipePanel(wxNotebook *parent);

};


#endif // TOP_RECIPE_VIEW_H