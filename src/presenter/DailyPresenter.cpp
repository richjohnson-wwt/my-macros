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
    onDateChanged(today);
}

void DailyPresenter::onDateChanged(const std::string& date)
{
    spdlog::info("DailyPresenter::onDateChanged() {}", date);
    m_dailyModel->setSelectedDate(date);
    DailyFood df = m_dailyModel->getDailyFood();
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);
    populateDailyFood(df, xdfVector);
    populateTotals(xdfVector);
}

void DailyPresenter::populateDailyFood(const DailyFood &df, const std::vector<XrefDailyFood>& xdfVector)
{
    spdlog::info("DailyPresenter::populateView");
    
    m_dailyView->setDailyActivityBonus(std::to_string(df.dailyActivityBonusCalories));
    
    m_dailyView->setDailyFoodList(xdfVector);
}

void DailyPresenter::populateTotals(const std::vector<XrefDailyFood>& xdfVector)
{
    spdlog::info("DailyPresenter::populateTotals");
    // if (xdfVector.size() > 0) {
        // spdlog::info("DailyPresenter::populateView() xdfVector[0].name {}", xdfVector[0].name);
    
        // TODO calc totals TEMP CODE
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
    // }
}

void DailyPresenter::onAddExercise()
{
    spdlog::debug("DailyPresenter::onAddExercise");
    m_dailyModel->addExercise(m_dailyView->getActivityBonus());
}

void DailyPresenter::onAddDailyFood()
{
    spdlog::debug("DailyPresenter::onAddDailyFood");
    DailyFood df = m_dailyModel->getDailyFood();
    XrefDailyFood xdf;
    xdf.dailyFoodId = df.id;
    
    m_dailyModel->addXrefDailyFood(xdf);

    // TODO refresh view
}

void DailyPresenter::onAddDailyRecipe()
{
    spdlog::debug("DailyPresenter::onAddDailyRecipe");
    DailyFood df = m_dailyModel->getDailyFood();
    XrefDailyFood xdf;
    xdf.dailyFoodId = df.id;

    // fill out from recipe

    m_dailyModel->addXrefDailyFood(xdf);

    // TODO refresh view
}