#pragma once

#include <qglobal.h>

class TemperaturePlotProcessor
{
public:
    TemperaturePlotProcessor() = default;
    ~TemperaturePlotProcessor() = default;

    TemperaturePlotProcessor(const TemperaturePlotProcessor &) = delete;
    TemperaturePlotProcessor(TemperaturePlotProcessor &&) = delete;
    TemperaturePlotProcessor &operator=(const TemperaturePlotProcessor &) = delete;
    TemperaturePlotProcessor &operator=(TemperaturePlotProcessor &&) = delete;

    [[nodiscard]] QList<QList<double>> approximatedData(
        const QList<double> &keys,
        const QList<double> &values,
        std::size_t order
    ) const;

};
