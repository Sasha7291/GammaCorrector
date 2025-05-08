#include "approximateplotprocessor.h"

#include "lsa_approximator.h"
#include "psr_polynomial.h"
#include "psr_powerfunction.h"
#include "psr_rationing.h"


QList<QList<double> > ApproximatePlotProcessor::approximatedData(
    const QList<double> &keys,
    const QList<double> &values,
    std::size_t order,
    double fromKey
) const
{
    const auto offsetIt = std::find_if(keys.cbegin(), keys.cend(), [fromKey](double value) -> bool {
        return value > fromKey;
    });
    const auto offsetIndex = keys.indexOf(*offsetIt);
    const auto slicedX = QList<double>{ offsetIt, keys.cend() };
    const auto slicedY = values.last(values.size() - offsetIndex);

    const auto coeffs = lsa::Approximator().polynomial(slicedX, slicedY, order);
    auto [resultKeys, resultValues] = psr::Polynomial<double>{keys.front(), keys.back()}(1024, coeffs);
    std::fill(resultValues.begin(), resultValues.begin() + offsetIndex, 0.0);

    return { coeffs, resultKeys, resultValues };
}

QPair<QList<double>, QList<double>> ApproximatePlotProcessor::gammaData(const QPair<double, double> &range, double degree) const
{
    return psr::PowerFunction<double>{range.first, range.second}(1024, 1023.0 / std::pow(range.second, degree), degree);
}

QPair<QList<double>, QList<double>> ApproximatePlotProcessor::normalizedData(const QList<double> &keys, const QList<double> &values) const
{
    const auto [minX, maxX] = std::ranges::minmax(keys);
    const auto [minY, maxY] = std::ranges::minmax(values);

    return {
        psr::Rationing<double>{{ minX, maxX }, { 0.0, 1023.0 }}(keys),
        psr::Rationing<double>{{ minY, maxY }, { 0.0, 1023.0 }}(values)
    };
}

QPair<QList<double>, QList<double>> ApproximatePlotProcessor::qData(
    const QList<double> &gamma,
    const QList<double> &keys,
    const QList<double> &values,
    double fromKey
) const
{
    QList<double> resultX(8);
    QList<double> resultY(8);

    for (int i = 0; i < 7; ++i)
    {
        resultX[i] = std::pow(2, i + 1) - 1;
        double currentGammaValue = gamma[resultX[i]];
        double minimumDifferece = std::abs(values[0] - currentGammaValue);
        int index = 0;

        for (int j = 0; j < values.size(); ++j)
        {
            double currentDifference = std::abs(values[j] - currentGammaValue);
            if (minimumDifferece > currentDifference)
            {
                minimumDifferece = currentDifference;
                index = j;
            }
        }

        resultY[i] = (keys[index] > fromKey)
            ? std::round(keys[index])
            : std::numeric_limits<double>::quiet_NaN();
        resultX[i] = 4 * resultX[i] + 3;
    }

    resultX[7] = 1023.0;
    resultY[7] = 1023.0;
    return { resultX, resultY };
}
