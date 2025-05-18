#include "approximateplotprocessor.h"

#include "lsa_approximator.h"
#include "psr_curvesproximity.h"
#include "psr_findpeaks.h"
#include "psr_gaussfilter.h"
#include "psr_line.h"
#include "psr_medianfilter.h"
#include "psr_pearsoncoefficient.h"
#include "psr_polynomial.h"
#include "psr_powerfunction.h"
#include "psr_rationing.h"
#include "psr_spearmancoefficient.h"


QList<QList<double>> ApproximatePlotProcessor::approximatedData(
    const QList<double> &keys,
    const QList<double> &values,
    std::size_t order,
    int offset
) const
{
    const auto slicedX = keys.last(keys.size() - offset);
    const auto slicedY = values.last(values.size() - offset);

    const auto coeffs = lsa::Approximator().polynomial(slicedX, slicedY, order);
    auto [resultKeys, resultValues] = psr::Polynomial<double>{keys.front(), keys.back()}(1024, coeffs);
    std::fill(resultValues.begin(), resultValues.begin() + offset, 0.0);

    return { coeffs, resultKeys, resultValues };
}

QPair<QList<double>, QList<double>> ApproximatePlotProcessor::gammaData(const QPair<double, double> &range, double degree) const
{
    return psr::PowerFunction<double>{range.first, range.second}(1024, 1023.0 / std::pow(range.second, degree), degree);
}

QPair<QList<double>, QList<double>> ApproximatePlotProcessor::normalizedData(
    const QList<double> &keys,
    const QList<double> &values
) const
{
    const auto [minX, maxX] = std::ranges::minmax(keys);
    const auto [minY, maxY] = std::ranges::minmax(values);

    return {
        psr::Rationing<double>{ { minX, maxX }, { 0.0, 1023.0 } }(keys),
        psr::Rationing<double>{ { minY, maxY }, { 0.0, 1023.0 } }(values)
    };
}

QList<std::size_t> ApproximatePlotProcessor::peakData(const QList<double> &values) const
{
    QList<double> tempValues(values.size() - 2);

    for (std::size_t i = 1; i < tempValues.size(); ++i)
        tempValues[i] = std::log(std::abs(values[i + 1] / values[i]));

    // 19 - эмпирически подобранное значение
    const auto peaks = psr::PeakFinder<double>{}(psr::GaussFilter<double>{}(psr::MedianFilter<double>{}(tempValues, 19), 19));

    QList<std::size_t> result;
    result.reserve(peaks.size());
    for (std::size_t i = 0; i < peaks.size(); ++i)
        result.push_back(peaks[i].position);

    return result;
}

QList<double> ApproximatePlotProcessor::statisticsData(
    const QList<double> &keys,
    const QList<double> &values,
    const QList<double> &approximatedValues
) const
{
    return {
        psr::SpearmanCoefficient<double>{}(keys, values),
        psr::CurvesProximity<double>{}(values, approximatedValues)
    };
}

QList<double> ApproximatePlotProcessor::substractLineData(const QList<double> &keys, const QList<double> &values) const
{
    double maxPc = 0.0;
    std::size_t maxPcIndex = 0;

    for (std::size_t i = 0; i < values.size(); ++i)
    {
        auto currentPc = psr::PearsonCoefficient<double>{}(
            { keys.cbegin(), keys.cbegin() + i },
            { values.cbegin(), values.cbegin() + i }
        );
        if (maxPc < currentPc)
        {
            maxPc = currentPc;
            maxPcIndex = i;
        }
    }

    const auto coeffs = lsa::Approximator{}.linear(
        { keys.cbegin(), keys.cbegin() + maxPcIndex },
        { values.cbegin(), values.cbegin() + maxPcIndex }
    );
    auto [_, result] = psr::Line<double>{ keys.front(), keys.back() }(keys.size(), coeffs[1], coeffs[0]);
    std::ranges::transform(values, result, result.begin(), std::minus<>());

    return result;
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
