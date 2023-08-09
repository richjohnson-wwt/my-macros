#ifndef IOUTLOOK_VIEW_H
#define IOUTLOOK_VIEW_H

class IOutlookView {
public:
    virtual void setTotalCaloriesForWeek(int totalCalories) = 0;
    virtual void setTotalExerciseCaloriesForWeek(int totalCalories) = 0;
    virtual void setProgressDate(const std::string &progressDate) = 0;
    virtual void setTargetDate(const std::string &targetDate) = 0;
    virtual void setPredictedPoundsLost(const std::string &poundsLost) = 0;
    virtual void setActualPoundsLost(const std::string &poundsLost) = 0;
};

#endif // IOUTLOOK_VIEW_H