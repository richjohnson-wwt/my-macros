#ifndef DAILY_MODEL_H
#define DAILY_MODEL_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IDailyModel {
public:
    virtual void setFoodSource() = 0;
    virtual void setRecipeSource() = 0;

};

class DailyModel : public IDailyModel {
private:
    Db m_db;


public:
    DailyModel();
    void setFoodSource() override {}
    void setRecipeSource() override {}

};

#endif // DAILY_MODEL_H