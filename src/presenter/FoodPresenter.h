#ifndef FOOD_PRESENTER_H
#define FOOD_PRESENTER_H

#include "../model/FoodModel.h"
#include "../view/TopFoodView.h"

class IFoodSubject;
class IFoodModel;

class IFoodCallback {
public:

};

class FoodPresenter : public IFoodCallback, public IFoodObserver {
private:
    IFoodModel *m_foodModel;
    ITopFoodView *m_topFoodView;
    IFoodSubject *m_foodSubject;

public:
    FoodPresenter(ITopFoodView *view, IFoodModel *model, IFoodSubject *foodSubject);

    void update() override;

    void postInit();

};


#endif // FOOD_PRESENTER_H