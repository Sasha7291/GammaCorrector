#pragma once

#include <QList>


class ApproximatePlotProcessor
{

public:
    ApproximatePlotProcessor() = default;
    ~ApproximatePlotProcessor() = default;

    ApproximatePlotProcessor(const ApproximatePlotProcessor &) = delete;
    ApproximatePlotProcessor(ApproximatePlotProcessor &&) = delete;
    ApproximatePlotProcessor &operator=(const ApproximatePlotProcessor &) = delete;
    ApproximatePlotProcessor &operator=(ApproximatePlotProcessor &&) = delete;

    [[nodiscard]] QList<QList<double>> approximatedData(
        const QList<double> &keys,
        const QList<double> &values,
        std::size_t order,
        int offset
    ) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> gammaData(const QPair<double, double> &range, double degree) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> normalizedData(
        const QList<double> &keys,
        const QList<double> &values
    ) const;
    [[nodiscard]] QList<std::size_t> peakData(const QList<double> &values) const;
    [[nodiscard]] QList<double> statisticsData(
        const QList<double> &keys,
        const QList<double> &values,
        const QList<double> &approximatedValues
    ) const;
    [[nodiscard]] QList<double> substractLineData(const QList<double> &keys, const QList<double> &values) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> qData(
        const QList<double> &gamma,
        const QList<double> &keys,
        const QList<double> &values,
        double fromKey
    ) const;

};
