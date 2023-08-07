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
    virtual void onNewFood() = 0;
    virtual void onEditFood() = 0;
    virtual bool isInEditMode() = 0;
    virtual void onFocus() = 0;
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
    void onNewFood() override;
    void onEditFood() override;
    bool isInEditMode() override;
    void onFocus() override;
    
};


#endif // FOOD_PRESENTER_H