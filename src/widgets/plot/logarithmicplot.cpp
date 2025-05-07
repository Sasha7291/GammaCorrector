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
    QMap<double, double> data;

    for (int i = 0; i < keys.size(); ++i)
        data[keys[i]] = values[i];
    for (auto it = data.begin(); it != data.end(); )
        (it.key() <= std::numeric_limits<double>::epsilon()
         || it.value() <= std::numeric_limits<double>::epsilon())
            ? it = data.erase(it)
            : ++it;

    const auto logKeys = data.keys();
    const auto logValues = data.values();
    const auto [minX, maxX] = std::ranges::minmax(logKeys);
    const auto [minY, maxY] = std::ranges::minmax(logValues);

    Plot::setData(index, logKeys, logValues, name, autoScale);

    setAxisScale(QwtAxis::XBottom, minX, maxX);
    setAxisScale(QwtAxis::YLeft, minY, maxY);
}
