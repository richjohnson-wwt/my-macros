#ifndef FOOD_EDIT_PRESENTER_H
#define FOOD_EDIT_PRESENTER_H

#include "../view/FoodItemEditView.h"

class IFoodEditModel;
class IFoodListSubject;
class IFoodItemEditView;

class IFoodEditCallback {
public:
    virtual void onSaveFood() = 0;
    virtual void onNewFoodCancel() = 0;
    virtual void initNewPage() = 0;
    virtual void initEditPage() = 0;
};

class FoodEditPresenter : public IFoodEditCallback {
private:
    IFoodEditModel *m_foodModel;
    IFoodItemEditView *m_foodItemEditView;
    IFoodListSubject *m_foodListSubject;

public:
    FoodEditPresenter(IFoodItemEditView *view, IFoodEditModel *model, IFoodListSubject *foodListSubject);

    void onSaveFood() override;
    void onNewFoodCancel() override;

    void initNewPage() override;
    void initEditPage() override;
};


#endif // FOOD_EDIT_PRESENTER_H