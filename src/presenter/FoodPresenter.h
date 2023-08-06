#ifndef FOOD_PRESENTER_H
#define FOOD_PRESENTER_H

#include "../model/FoodModel.h"
#include "../model/FoodListModel.h"
#include "../view/FoodItemView.h"

class IFoodSubject;
class IFoodModel;

class IFoodCallback {
public:
    virtual void onDeleteFood() = 0;
    // virtual void onSaveFood() = 0;
    virtual void onNewFood() = 0;
    // virtual void onNewFoodCancel() = 0;
    virtual void onEditFood() = 0;
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

    void onDeleteFood() override;
    // void onSaveFood() override;
    void onNewFood() override;
    // void onNewFoodCancel() override;
    void onEditFood() override;
    

};


#endif // FOOD_PRESENTER_H