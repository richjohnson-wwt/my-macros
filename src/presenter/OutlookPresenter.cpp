#include "OutlookPresenter.h"
#include "../model/OutlookModel.h"
#include "../view/OutlookView.h"
#include "WeightLossProjector.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <spdlog/spdlog.h>



OutlookPresenter::OutlookPresenter(IOutlookView *view, IOutlookModel *model) : m_outlookView(view), m_outlookModel(model)
{
    
}

void OutlookPresenter::postInit()
{
    populateCalorieSection();
    populateProgressWeightSection();
    populateGoalWeightSection();
}

void OutlookPresenter::populateCalorieSection()
{
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    auto today_time_t = std::chrono::system_clock::to_time_t(today);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&today_time_t), "%Y-%m-%d");
    std::string endDate = ss.str();

    std::chrono::system_clock::time_point oneWeekAgo = today - std::chrono::hours(7 * 24);
    auto one_week_ago_time_t = std::chrono::system_clock::to_time_t(oneWeekAgo);
    std::stringstream ss2;
    ss2 << std::put_time(std::localtime(&one_week_ago_time_t), "%Y-%m-%d");
    std::string startDate = ss2.str();

    spdlog::info("OutlookPresenter::postInit() one week ago {} to {}", startDate, endDate);
    std::vector<DailyFood> dailyFoods = m_outlookModel->getDailyFoodsByRange(startDate, endDate);
    std::vector<XrefDailyFood> xrefDailyFoods;
    int exerciseCalories = 0;
    for (auto df : dailyFoods)
    {
        exerciseCalories += df.dailyActivityBonusCalories;
        auto xdfs = m_outlookModel->getXrefDailyFoods(df);
        xrefDailyFoods.insert(xrefDailyFoods.end(), xdfs.begin(), xdfs.end());
    }

    int totalCalories = 0;
    for (auto x : xrefDailyFoods)
    {
        spdlog::debug("OutlookPresenter::postInit() adding: {} to total: {}", x.calories, totalCalories );
        totalCalories += x.calories;
    }
    m_outlookView->setTotalCaloriesForWeek(totalCalories);
    m_outlookView->setTotalExerciseCaloriesForWeek(exerciseCalories);
}

void OutlookPresenter::populateGoalWeightSection()
{
    std::string startDate = m_outlookModel->getGoalStartDate();
    std::string endDate = m_timeHelper.getNow();

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
    std::string goalDate = m_timeHelper.getFutureDateInWeeks(m_timeHelper.getTimePointFromString(startDate), numberOfWeeksToGoal);

    m_outlookView->setTargetDate(goalDate);
}

void OutlookPresenter::populateProgressWeightSection()
{
    std::string endDate = m_timeHelper.getNow();

    auto startDate = m_outlookModel->getGoalStartDate();
    auto tpStartDate = m_timeHelper.getTimePointFromString(startDate);

    auto secondsElapsed = m_timeHelper.getSecondsBetweenDateAndToday(tpStartDate);
    auto daysElapsed = secondsElapsed.count() / 60 / 60 / 24;

    std::vector<DailyFood> dailyFoodsSinceStartDate = m_outlookModel->getDailyFoodsByRange(startDate, endDate);
    std::cout << "Point size: " << dailyFoodsSinceStartDate.size() << std::endl;
    std::vector<double> weights;
    for (auto df : dailyFoodsSinceStartDate) {
        weights.push_back(df.weight);
    }

    WeightLossProjector weightLossProjector(weights);
    weightLossProjector.calculate();
    long numberOfWeeksToGoal = weightLossProjector.numberOfWeeksToGoal(m_outlookModel->getGoalTargetWeight());
    double percentage = static_cast<double>(dailyFoodsSinceStartDate.size()) / daysElapsed;
    double numberOfWeeksNormalized = static_cast<double>(numberOfWeeksToGoal) / percentage;

    long numberOfWeeksNormalizedLong = static_cast<long>(numberOfWeeksNormalized);

    std::string goalDate = m_timeHelper.getFutureDateInWeeks(tpStartDate, numberOfWeeksNormalizedLong);

    m_outlookView->setProgressDate(goalDate);
}
