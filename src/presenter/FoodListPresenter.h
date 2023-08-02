#ifndef FOOD_LIST_PRESENTER_H
#define FOOD_LIST_PRESENTER_H

#include "../model/FoodModel.h"
#include "../view/FoodView.h"

class IFoodListCallback {
public:
    virtual void onFoodSelected(int id) = 0;
    virtual void onFoodBookPageChanged() = 0;
};

class FoodListPresenter : public IFoodListCallback {
private:
    IFoodModel *m_foodModel;
    IFoodListView *m_foodListView;

public:
    FoodListPresenter(IFoodListView *view, IFoodModel *model);

    void setActive();

    void onFoodSelected(int id) override;
    void onFoodBookPageChanged() override;


};


#endif // FOOD_LIST_PRESENTER_H