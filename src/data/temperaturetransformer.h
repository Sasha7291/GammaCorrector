#pragma once

#include <qglobal.h>


class TemperatureTransformer
{

public:
    enum Scale
    {
        Kelvin,
        Celsius,
        Fahrenheit
    };

    TemperatureTransformer() = default;
    ~TemperatureTransformer() = default;

    TemperatureTransformer(const TemperatureTransformer &) = delete;
    TemperatureTransformer(TemperatureTransformer &&) = delete;
    TemperatureTransformer &operator=(const TemperatureTransformer &) = delete;
    TemperatureTransformer &operator=(TemperatureTransformer &&) = delete;

    [[nodiscard]] double toCelsius(Scale previous, double value) const;
    [[nodiscard]] double toKelvin(Scale previous, double value) const;
    [[nodiscard]] double toFahrenheit(Scale previous, double value) const;

};
