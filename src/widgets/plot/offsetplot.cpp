#include "offsetplot.h"

#include "offsetplotscaledraw.h"


OffsetPlot::OffsetPlot(QWidget *parent)
    : LogarithmicPlot{LogarithmicPlot::Y, parent}
{
    insertLegend(nullptr);
    setFixedSize(233, 200);
    setAxisScaleDraw(QwtPlot::xBottom, new OffsetPlotScaleDraw{QFont{"Arial", 6}});
    setAxisScaleDraw(QwtPlot::yLeft, new OffsetPlotScaleDraw{QFont{"Arial", 6}});
}

OffsetPlot::~OffsetPlot() {}

void OffsetPlot::setData(
    const QList<QList<double>> &keys,
    const QList<QList<double>> &values,
    const QStringList &names
)
{
    Plot::setData(keys, values, names);

    showMarker();
}

void OffsetPlot::setData(
    unsigned index,
    const QList<double> &keys,
    const QList<double> &values,
    const QString &name,
    bool autoScale
)
{
    LogarithmicPlot::setData(index, keys, values, name, autoScale);

    if (index == 0)
        showMarker();
}
