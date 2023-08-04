#ifndef EXPLORER_NOTEBOOK_H
#define EXPLORER_NOTEBOOK_H

#include "FoodListView.h"
#include "RecipeListView.h"

#include <wx/wx.h>
#include "wx/listctrl.h"
#include "wx/srchctrl.h"
#include "wx/notebook.h"
#include <wx/event.h>

class ExplorerNotebook : public wxEvtHandler {
public:
    ExplorerNotebook(wxFrame* parent, FoodListView *foodListView, RecipeListView *recipeListView);
    wxNotebook *createExplorerBookCtrl();

protected:
    
private:
    wxFrame *m_wxFrame;
    wxNotebook *m_explorerBookCtrl;
    FoodListView *m_foodListView;
    RecipeListView *m_recipeListView;

    wxPanel *CreateExplorerFoodPage(wxBookCtrlBase *parent);
    wxPanel *CreateExplorerRecipePage(wxBookCtrlBase *parent);
};

#endif // EXPLORER_NOTEBOOK_H