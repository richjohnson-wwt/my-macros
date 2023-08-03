#ifndef FOOD_VM_H
#define FOOD_VM_H

#include "../model/FoodModel.h"
#include "../view/TopFoodView.h"

class IFoodCallback {
public:

};

class FoodPresenter : public IFoodCallback {
private:
    IFoodModel *m_foodModel;
    ITopFoodView *m_topFoodView;

public:
    FoodPresenter(ITopFoodView *view, IFoodModel *model);

    void setActive();

};


#endif // FOOD_VM_H