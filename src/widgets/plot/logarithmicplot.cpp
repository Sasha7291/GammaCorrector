#include "logarithmicplot.h"

#include <QwtLogTransform>
#include <QwtLogScaleEngine>


LogarithmicPlot::LogarithmicPlot(Axis axis, QWidget *parent)
    : Plot{parent}
{
    if (axis.testFlag(X))
        setAxisScaleEngine(QwtAxis::XBottom, new QwtLogScaleEngine);
    if (axis.testFlag(Y))
        setAxisScaleEngine(QwtAxis::YLeft, new QwtLogScaleEngine);
}

LogarithmicPlot::~LogarithmicPlot() {}

void LogarithmicPlot::setData(
    unsigned index,
    const QList<double> &keys,
    const QList<double> &values,
    const QString &name,
    bool autoScale
)
{
    auto logKeys = keys;
    auto logValues = values;

    for (std::size_t i = 0ull; i < keys.size() - 1; ++i)
    {
        if (keys[i] <= std::numeric_limits<double>::epsilon())
            logKeys[i] = std::abs(keys[i + 1]);
        if (values[i] <= std::numeric_limits<double>::epsilon())
            logValues[i] = std::abs(values[i + 1]);
    }

    const auto [minX, maxX] = std::ranges::minmax(logKeys);
    const auto [minY, maxY] = std::ranges::minmax(logValues);

    Plot::setData(index, logKeys, logValues, name, autoScale);

    setAxisScale(QwtAxis::XBottom, minX, maxX);
    setAxisScale(QwtAxis::YLeft, minY, maxY);
}
