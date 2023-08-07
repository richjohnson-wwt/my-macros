#ifndef FOOD_COMMON_MODEL_H
#define FOOD_COMMON_MODEL_H


class FoodCommonModel {
private:
    bool m_inEditMode = false;

public:
    bool isInEditMode() const;
    void setInEditMode(bool inEditMode);
};


#endif // FOOD_COMMON_MODEL_H