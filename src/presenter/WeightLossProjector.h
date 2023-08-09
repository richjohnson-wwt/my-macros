#ifndef WEIGHT_LOSS_PROJECTOR_H
#define WEIGHT_LOSS_PROJECTOR_H

#include <vector>

class WeightLossProjector {
private:
    std::vector<double> m_x;
    std::vector<double> m_y;
    std::vector<double> m_xy;
    std::vector<double> m_x2;

    double m_sumX;
    double m_sumY;
    double m_sumXY;
    double m_sumX2;

    double m_intercept;
    double m_slope;

    double sum(const std::vector<double>& v);

public:
    WeightLossProjector(const std::vector<double>& weights);

    void calculate();

    double weightAtDay(int day) const;
    long numberOfWeeksToGoal(long goal) const;

    double getSlope() const { return m_slope; }
    double getIntercept() const { return m_intercept; }

};

#endif //WEIGHT_LOSS_PROJECTOR_H