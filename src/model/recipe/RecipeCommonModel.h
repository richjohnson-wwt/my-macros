#ifndef RECIPE_COMMON_MODEL_H
#define RECIPE_COMMON_MODEL_H


class RecipeCommonModel {
private:
    bool m_inEditMode = false;

public:
    bool isInEditMode() const;
    void setInEditMode(bool inEditMode);
};


#endif // RECIPE_COMMON_MODEL_H