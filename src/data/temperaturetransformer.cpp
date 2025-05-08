#include "temperaturetransformer.h"


double TemperatureTransformer::toCelsius(Scale previous, double value) const
{
    switch (previous)
    {
    case Kelvin:
        return value - 273.15;

    case Fahrenheit:
        return 5.0 / 9.0 * (value - 32.0);

    default:
        return value;
    }
}

double TemperatureTransformer::toKelvin(Scale previous, double value) const
{
    switch (previous)
    {
    case Celsius:
        return value + 273.15;

    case Fahrenheit:
        return toCelsius(Fahrenheit, value) + 273.15;

    default:
        return value;
    }
}

double TemperatureTransformer::toFahrenheit(Scale previous, double value) const
{
    switch (previous)
    {
    case Celsius:
        return 1.8 * value + 32.0;

    case Kelvin:
        return toFahrenheit(Celsius, value - 273.15);

    default:
        return value;
    }
}
