#include "WeightLossProjector.h"

#include <iostream>

WeightLossProjector::WeightLossProjector(const std::vector<double> &weights)
{
    m_y = weights;
}

void WeightLossProjector::calculate()
{
    for (int i = 1; i < m_y.size() + 1; i++) {
        m_x.push_back(i);
        m_xy.push_back(i * m_y[i - 1]);
        m_x2.push_back(i * i);
    }

    m_sumX = sum(m_x);
    m_sumY = sum(m_y);
    m_sumXY = sum(m_xy);
    m_sumX2 = sum(m_x2);

    long n = m_y.size();
    m_slope = ((n * m_sumXY) - (m_sumX * m_sumY)) / ((n * m_sumX2) - (m_sumX * m_sumX));
    m_intercept = (m_sumY - (m_slope * m_sumX)) / n;
}

double WeightLossProjector::weightAtDay(int day) const
{
    return (m_slope * day) + m_intercept;
}

long WeightLossProjector::numberOfWeeksToGoal(long goal) const
{
    return ((goal - m_intercept) / m_slope) / 7;
}

double WeightLossProjector::sum(const std::vector<double> &v) {
    long returnValue = 0;
    for (auto i : v) {
        returnValue += i;
    }
    return returnValue;
}
