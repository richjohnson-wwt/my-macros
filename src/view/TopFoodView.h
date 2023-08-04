#ifndef FOOD_VIEW_H
#define FOOD_VIEW_H

#include "FatSecretView.h"
#include "FoodItemView.h"

#include <wx/wx.h>
#include "wx/notebook.h"

class TopFoodView
{
private:
    FatSecretView *m_fatSecretView;
    FoodItemView *m_foodItemView;

    wxNotebook *m_foodFatSecretBookCtrl;

public:
    TopFoodView(FoodItemView *foodItemView, FatSecretView *fatSecretView);

    wxPanel *createFoodPanel(wxNotebook *parent);

};

#endif // FOOD_VIEW_H