#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "../src/presenter/WeightLossProjector.h"

using Catch::Approx;

TEST_CASE("WeightLossProjector", "[WeightLossProjector]") {
    std::vector<double> weights = {200, 190, 192, 188, 187, 186, 186};
    WeightLossProjector testObject(weights);
    testObject.calculate();

    CHECK(testObject.getSlope() == Approx(-1.96).epsilon(0.01));
    CHECK(testObject.getIntercept() == Approx(197.714).epsilon(0.01));

    CHECK(testObject.weightAtDay(0) == Approx(197.71).epsilon(0.01));
    CHECK(testObject.weightAtDay(1) == Approx(195.75).epsilon(0.01));
    CHECK(testObject.weightAtDay(2) == Approx(193.78).epsilon(0.01));
    CHECK(testObject.weightAtDay(3) == Approx(191.82).epsilon(0.01));
    CHECK(testObject.weightAtDay(4) == Approx(189.85).epsilon(0.01));
    CHECK(testObject.weightAtDay(5) == Approx(187.88).epsilon(0.01));
    CHECK(testObject.weightAtDay(6) == Approx(186.85).epsilon(0.01));

}

TEST_CASE("WeightLossProjector target", "[WeightLossProjector]") {
    // Example: Weight is 223  and goal is 160
    std::vector<double> weights;
    double x = 223;
    while (x > 160) {
        weights.push_back(x);
        x = x - 0.2;
    }
    WeightLossProjector testObject(weights);
    testObject.calculate();

    long numberOfWeeks = testObject.numberOfWeeksToGoal(160);

    CHECK(45 == numberOfWeeks);
}

