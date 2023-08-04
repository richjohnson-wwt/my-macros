#include "DailyPresenter.h"

#include <spdlog/spdlog.h>
#include <chrono>
#include <iomanip>
#include <sstream>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model)
: m_dailyModel(model), m_dailyView(view)
{
}

void DailyPresenter::postInit()
{
    spdlog::debug("DailyPresenter::postInit() Populate today");

    // Get todays date in iso format yyyy-mm-dd using std::chrono
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    std::string today = ss.str();
    spdlog::info("DailyPresenter::postInit() today {}", today);
    m_dailyModel->setSelectedDate(today);
    populateView();
    
    
}

void DailyPresenter::onDateChanged(const std::string& date)
{
    spdlog::info("DailyPresenter::onDateChanged() {}", date);
    m_dailyModel->setSelectedDate(date);
    populateView();
}

void DailyPresenter::populateView()
{
    spdlog::info("DailyPresenter::populateView");
    DailyFood df = m_dailyModel->getDailyFood();
    spdlog::info("DailyPresenter::populateView() df.id {} {}", df.id, df.date);
    m_dailyView->setDailyActivityBonus(std::to_string(df.dailyActivityBonusCalories));
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);
    m_dailyView->setDailyFoodList(xdfVector);

    if (xdfVector.size() > 0) {
        spdlog::info("DailyPresenter::populateView() xdfVector[0].name {}", xdfVector[0].name);
    
        // TODO calc totals
        std::vector<XrefDailyFood> totalsXdf;
        XrefDailyFood remaining;
        remaining.name = "Remaining";
        remaining.calories = 0;
        remaining.carb = 0;
        remaining.fat = 0;
        remaining.protein = 0;

        XrefDailyFood goal;
        goal.name = "Your daily goal";
        goal.calories = 2000;
        goal.carb = 25;
        goal.fat = 168;
        goal.protein = 101;

        XrefDailyFood totals;
        totals.name = "Totals";
        totals.calories = 0;
        totals.carb = 0;
        totals.fat = 0;
        totals.protein = 0;

        totalsXdf.push_back(totals);
        totalsXdf.push_back(goal);
        totalsXdf.push_back(remaining);

        m_dailyView->setTotalsList(totalsXdf);
    }
}