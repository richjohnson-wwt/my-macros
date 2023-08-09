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

    OutlookPresenter testObject(&mockView.get(), &mockModel.get());
    SECTION("test")
    {
        REQUIRE(true);
        // REQUIRE(presenter.test() == true);
    }
}