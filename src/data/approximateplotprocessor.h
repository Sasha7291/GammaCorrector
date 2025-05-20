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
    [[nodiscard]] inline double dataMax() const { return dataRange().second; }
    [[nodiscard]] inline double dataMin() const { return dataRange().first; }
    [[nodiscard]] inline QPair<double, double> dataRange() const { return std::make_pair(0.0, 1023.0); }
    [[nodiscard]] inline constexpr std::size_t dataSize() const { return 1024ull; }
    [[nodiscard]] QList<double> filterData(const QList<double> &data) const;
    [[nodiscard]] inline constexpr std::size_t filterWidth() const { return 21ull; }
    [[nodiscard]] QPair<QList<double>, QList<double>> gammaData(double degree) const;
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
    [[nodiscard]] QPair<QList<double>, QList<double>> substractLineData(const QList<double> &keys, const QList<double> &values) const;
    [[nodiscard]] QPair<QList<double>, QList<double>> qData(
        const QList<double> &gamma,
        const QList<double> &keys,
        const QList<double> &values,
        double fromKey
    ) const;

};
