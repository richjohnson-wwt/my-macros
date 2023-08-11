#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <fakeit.hpp>

#include "../src/presenter/OutlookPresenter.h"
#include "../src/view/IOutlookView.h"
#include "../src/model/OutlookModel.h"

using Catch::Approx;
using namespace fakeit;

TEST_CASE("OutlookPresenter")
{
    Mock<IOutlookView> mockView;
    Mock<IOutlookModel> mockModel;
    Mock<TimeHelper> mockTimeHelper;
    Mock<IDbDailySubject> mockDbDailySubject;

    OutlookPresenter testObject(&mockView.get(), &mockModel.get(), &mockTimeHelper.get(), &mockDbDailySubject.get());
    SECTION("populateCalorieSection empty foods")
    {
        std::vector<std::string> values;
        When(Method(mockTimeHelper, getNow)).Return("2020-01-08");
        When(Method(mockTimeHelper, getOneWeekAgo)).Return("2020-01-01");
        When(Method(mockModel, getDailyFoodsByRange)).Return({});
        When(Method(mockModel, getBmr)).Return(2000);
        When(Method(mockView, setTotalExerciseCaloriesForWeek)).AlwaysReturn();
        When(Method(mockView, setTotalCaloriesForWeek)).AlwaysReturn();
        When(Method(mockView, setPredictedPoundsLost)).AlwaysDo([&](const std::string &poundsLost) {
            values.push_back(poundsLost);
        });

        testObject.populateCalorieSection();

        Verify(Method(mockView, setTotalExerciseCaloriesForWeek).Using(0)).Once();
        Verify(Method(mockView, setTotalCaloriesForWeek).Using(0)).Once();
        CHECK(values.size() == 1);
        CHECK(values[0] == "4.0"); // bmr 2000 * 7 = 14000 / 3500 = 4.0
    }
}