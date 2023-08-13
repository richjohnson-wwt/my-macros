#include "OutlookPresenter.h"
#include "../model/OutlookModel.h"
#include "../view/OutlookView.h"
#include "WeightLossProjector.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <spdlog/spdlog.h>

OutlookPresenter::OutlookPresenter(
    IOutlookView *view, 
    IOutlookModel *model, 
    TimeHelper *timeHelper, 
    IDbDailySubject *dailySubject) 
: m_outlookView(view), m_outlookModel(model), m_timeHelper(timeHelper), m_dbDailySubject(dailySubject)
{
    
}

void OutlookPresenter::update() {
    refresh();
}

void OutlookPresenter::postInit()
{
    m_dbDailySubject->attach(this);
    refresh();
}

void OutlookPresenter::refresh() {
    populateCalorieSection();
    populateProgressWeightSection();
    populateGoalWeightSection();
    populateActualWeightLostLastWeek();
}

void OutlookPresenter::populateCalorieSection()
{
    std::string endDate = m_timeHelper->getNow();

    std::string startDate = m_timeHelper->getOneWeekAgo();

    spdlog::info("OutlookPresenter::populateCalorieSection() one week ago {} to {}", startDate, endDate);
    std::vector<DailyFood> dailyFoods = m_outlookModel->getDailyFoodsByRange(startDate, endDate);
    std::vector<XrefDailyFood> xrefDailyFoods;
    int exerciseCalories = 0;
    for (auto df : dailyFoods)
    {
        exerciseCalories += df.dailyActivityBonusCalories;
        auto xdfs = m_outlookModel->getXrefDailyFoods(df);
        xrefDailyFoods.insert(xrefDailyFoods.end(), xdfs.begin(), xdfs.end());
    }
    m_outlookView->setTotalExerciseCaloriesForWeek(exerciseCalories);

    int totalCalories = 0;
    for (auto x : xrefDailyFoods)
    {
        spdlog::debug("OutlookPresenter::populateCalorieSection() adding: {} to total: {}", x.calories, totalCalories );
        totalCalories += x.calories;
    }
    m_outlookView->setTotalCaloriesForWeek(totalCalories);

    auto bmr = m_outlookModel->getBmr();
    auto sevenDaysCalories = bmr * 7;
    auto sevenDaysCaloriesPlusExercise = sevenDaysCalories + exerciseCalories;
    auto deficit = sevenDaysCaloriesPlusExercise - totalCalories;
    double poundsLost = static_cast<double>(deficit) / 3500;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << poundsLost;
    m_outlookView->setPredictedPoundsLost(ss.str());

    m_outlookView->setDeficitCalories(std::to_string(deficit));
    m_outlookView->setBmrPlusExercise(std::to_string(sevenDaysCaloriesPlusExercise));
}

void OutlookPresenter::populateGoalWeightSection()
{
    std::string startDate = m_outlookModel->getGoalStartDate();
    std::string endDate = m_timeHelper->getNow();

    std::vector<DailyFood> dailyFoodsSinceStartDate = m_outlookModel->getDailyFoodsByRange(startDate, endDate);
    auto startWeight = dailyFoodsSinceStartDate[0].weight;
    auto goalWeight = m_outlookModel->getGoalTargetWeight();

    std::vector<double> weights;
    double x = startWeight;
    while (x > goalWeight) {
        weights.push_back(x);
        x -= 0.165;
    }

    WeightLossProjector weightLossProjector(weights);
    weightLossProjector.calculate();
    long numberOfWeeksToGoal = weightLossProjector.numberOfWeeksToGoal(goalWeight);
    std::string goalDate = m_timeHelper->getFutureDateInWeeks(m_timeHelper->getTimePointFromString(startDate), numberOfWeeksToGoal);

    m_outlookView->setTargetDate(goalDate);
}

void OutlookPresenter::populateActualWeightLostLastWeek()
{
    std::string sevenDaysAgo = m_timeHelper->getOneWeekAgo();
    std::string endDate = m_timeHelper->getNow();

    std::vector<DailyFood> dailyFoodsSinceStartDate = m_outlookModel->getDailyFoodsByRange(sevenDaysAgo, endDate);
    double high = 0;
    double low = 1000;
    for (auto df : dailyFoodsSinceStartDate) {
        if (df.weight > 0) {
            // std::cout << "weight: " << df.weight << std::endl;
            if (df.weight > high) {
                high = df.weight;
            }
            if (df.weight < low) {
                low = df.weight;
            }
            // std::cout << "\thigh: " << high << std::endl;
            // std::cout << "\tlow: " << low << std::endl;
        }
    }
    double diff = high - low;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << diff;
    m_outlookView->setActualPoundsLost(ss.str());
}

void OutlookPresenter::populateProgressWeightSection()
{
    spdlog::info("OutlookPresenter::populateProgressWeightSection()");
    std::string endDate = m_timeHelper->getNow();

    auto startDate = m_outlookModel->getGoalStartDate();
    auto tpStartDate = m_timeHelper->getTimePointFromString(startDate);

    auto secondsElapsed = m_timeHelper->getSecondsBetweenDateAndToday(tpStartDate);
    spdlog::info("OutlookPresenter::populateProgressWeightSection() secondsElapsed: {}", secondsElapsed.count());
    auto daysElapsed = secondsElapsed.count() / 60 / 60 / 24;
    spdlog::info("OutlookPresenter::populateProgressWeightSection() daysElapsed: {}", daysElapsed);

    std::vector<DailyFood> dailyFoodsSinceStartDate = m_outlookModel->getDailyFoodsByRange(startDate, endDate);
    spdlog::info("OutlookPresenter::populateProgressWeightSection() dailyFoodsSinceStartDate: {}", dailyFoodsSinceStartDate.size());
    std::vector<double> weights;
    for (auto df : dailyFoodsSinceStartDate) {
        if (df.weight > 0) {
            spdlog::debug("OutlookPresenter::populateProgressWeightSection() adding weight: {}", df.weight);
            weights.push_back(df.weight);
        }
    }

    WeightLossProjector weightLossProjector(weights);
    weightLossProjector.calculate();

    auto fooSlope = weightLossProjector.getSlope();
    auto barIntercept = weightLossProjector.getIntercept();

    spdlog::info("OutlookPresenter::populateProgressWeightSection() fooSlope: {} barIntercept: {}", fooSlope, barIntercept);
    long numberOfWeeksToGoal = weightLossProjector.numberOfWeeksToGoal(m_outlookModel->getGoalTargetWeight());
    spdlog::info("OutlookPresenter::populateProgressWeightSection() numberOfWeeksToGoal: {}", numberOfWeeksToGoal);
    double percentage = static_cast<double>(dailyFoodsSinceStartDate.size()) / daysElapsed;
    double numberOfWeeksNormalized = static_cast<double>(numberOfWeeksToGoal) / percentage;
    spdlog::info("OutlookPresenter::populateProgressWeightSection() numberOfWeeksNormalized: {}", numberOfWeeksNormalized);

    long numberOfWeeksNormalizedLong = static_cast<long>(numberOfWeeksNormalized);

    std::string goalDate = m_timeHelper->getFutureDateInWeeks(tpStartDate, numberOfWeeksNormalizedLong);
    spdlog::info("OutlookPresenter::populateProgressWeightSection() goalDate: {}", goalDate);

    m_outlookView->setProgressDate(goalDate);
}
