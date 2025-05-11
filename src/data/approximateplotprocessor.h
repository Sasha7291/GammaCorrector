#pragma once

#include <qglobal.h>

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
        double fromKey
    ) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> gammaData(const QPair<double, double> &range, double degree) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> normalizedData(
        const QList<double> &keys,
        const QList<double> &values
    ) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> qData(
        const QList<double> &gamma,
        const QList<double> &keys,
        const QList<double> &values,
        double fromKey
    ) const;

};
