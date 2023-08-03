#ifndef FOOD_LIST_PRESENTER_H
#define FOOD_LIST_PRESENTER_H

#include "../model/FoodModel.h"
#include "../view/FoodListView.h"

class IFoodListCallback {
public:
    virtual void onFoodSelected(int id) = 0;
    virtual void onFoodBookPageChanged() = 0;
    virtual void setActive() = 0;
};

class FoodListPresenter : public IFoodListCallback {
private:
    IFoodModel *m_foodModel;
    IFoodListView *m_foodListView;

public:
    FoodListPresenter(IFoodListView *view, IFoodModel *model);

    void setActive() override;

    void onFoodSelected(int id) override;
    void onFoodBookPageChanged() override;


};


#endif // FOOD_LIST_PRESENTER_H