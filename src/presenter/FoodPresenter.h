#ifndef FOOD_PRESENTER_H
#define FOOD_PRESENTER_H

#include "../model/FoodModel.h"
#include "../model/FoodListModel.h"
#include "../view/TopFoodView.h"

class IFoodSubject;
class IFoodModel;

class IFoodCallback {
public:

};

class FoodPresenter : public IFoodCallback, public IFoodListObserver {
private:
    IFoodModel *m_foodModel;
    ITopFoodView *m_topFoodView;
    IFoodListSubject *m_foodListSubject;

public:
    FoodPresenter(ITopFoodView *view, IFoodModel *model, IFoodListSubject *foodListSubject);

    void update() override;

    void postInit();

};


#endif // FOOD_PRESENTER_H