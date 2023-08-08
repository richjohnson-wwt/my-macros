#include "OutlookPresenter.h"
#include "../model/OutlookModel.h"
#include "../view/OutlookView.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <spdlog/spdlog.h>

OutlookPresenter::OutlookPresenter(IOutlookView *view, IOutlookModel *model): m_outlookView(view), m_outlookModel(model)
{
    
}

void OutlookPresenter::postInit()
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
        spdlog::info("OutlookPresenter::postInit() adding: {} to total: {}", x.calories, totalCalories );
        totalCalories += x.calories;
    }
    m_outlookView->setTotalCaloriesForWeek(totalCalories);
    m_outlookView->setTotalExerciseCaloriesForWeek(exerciseCalories);
}