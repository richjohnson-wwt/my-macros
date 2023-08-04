#ifndef FOOD_LIST_PRESENTER_H
#define FOOD_LIST_PRESENTER_H

#include "../model/FoodModel.h"
#include "../model/FoodListModel.h"
#include "../view/FoodListView.h"

class IFoodListCallback {
public:
    virtual void onFoodSelected(int id) = 0;
};

class FoodListPresenter : public IFoodListCallback, IFoodObserver {
private:
    IFoodListModel *m_foodListModel;
    IFoodSubject *m_foodSubject;
    IFoodListView *m_foodListView;

public:
    FoodListPresenter(IFoodListView *view, IFoodListModel *model, IFoodSubject *foodSubject);

    void postInit();

    void onFoodSelected(int id) override;

    void update() override;


};


#endif // FOOD_LIST_PRESENTER_H