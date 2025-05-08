#include "temperaturedoublespinbox.h"

TemperatureDoubleSpinBox::TemperatureDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox{parent}
    , suffixes_{" °K", " °C", " °F"}
{
    setRange(-60.0, 50.0);
    setDecimals(2);
    setSingleStep(0.01);
    setSuffix(" °K");
}

TemperatureTransformer::Scale TemperatureDoubleSpinBox::currentScale() const
{
    return scale_;
}

double TemperatureDoubleSpinBox::currentTemparetureInKelvins() const
{
    return TemperatureTransformer{}.toKelvin(scale_, value());
}

void TemperatureDoubleSpinBox::setScale(TemperatureTransformer::Scale scale)
{
    double temp = value();

    switch (scale)
    {
    case TemperatureTransformer::Kelvin:
        setRange(TemperatureTransformer{}.toKelvin(scale_, minimum()), TemperatureTransformer{}.toKelvin(scale_, maximum()));
        temp = TemperatureTransformer{}.toKelvin(scale_, temp);
        break;

    case TemperatureTransformer::Celsius:
        setRange(TemperatureTransformer{}.toCelsius(scale_, minimum()), TemperatureTransformer{}.toCelsius(scale_, maximum()));
        temp = TemperatureTransformer{}.toCelsius(scale_, temp);
        break;

    case TemperatureTransformer::Fahrenheit:
        setRange(TemperatureTransformer{}.toFahrenheit(scale_, minimum()), TemperatureTransformer{}.toFahrenheit(scale_, maximum()));
        temp = TemperatureTransformer{}.toFahrenheit(scale_, temp);
        break;
    }

    setValue(temp);
    setSuffix(suffixes_[scale]);
    scale_ = scale;
}

void TemperatureDoubleSpinBox::setTemperatureInKelvins(double temperature)
{
    switch (scale_)
    {
    case TemperatureTransformer::Kelvin:
        setValue(temperature);
        break;

    case TemperatureTransformer::Celsius:
        setValue(TemperatureTransformer{}.toCelsius(TemperatureTransformer::Kelvin, temperature));
        break;

    case TemperatureTransformer::Fahrenheit:
        setValue(TemperatureTransformer{}.toFahrenheit(TemperatureTransformer::Kelvin, temperature));
        break;
    }
}
