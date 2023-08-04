#ifndef FOOD_PRESENTER_H
#define FOOD_PRESENTER_H

#include "../model/FoodModel.h"
#include "../model/FoodListModel.h"
#include "../view/FoodItemView.h"

class IFoodSubject;
class IFoodModel;

class IFoodCallback {
public:

};

class FoodPresenter : public IFoodCallback, public IFoodListObserver {
private:
    IFoodModel *m_foodModel;
    IFoodItemView *m_foodItemView;
    IFoodListSubject *m_foodListSubject;

public:
    FoodPresenter(IFoodItemView *view, IFoodModel *model, IFoodListSubject *foodListSubject);

    void update() override;

    void postInit();

};


#endif // FOOD_PRESENTER_H