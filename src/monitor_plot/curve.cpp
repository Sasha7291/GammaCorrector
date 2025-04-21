#include "curve.h"

#include <QPen>
#include <QwtPlot>


Curve::Curve(QwtPlot *parent, const QColor color, const QString &name)
    : QwtPlotCurve{}
    , parent_{parent}
{
    setPen(QPen(color, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setCurveAttribute(Fitted);
    setRenderHint(QwtPlotItem::RenderAntialiased);
    setPaintAttribute(QwtPlotCurve::ClipPolygons);
    setLegendAttribute(QwtPlotCurve::LegendShowLine);
    setTitle(name);
    attach(parent);
}

void Curve::hide() noexcept
{
    detach();
    parent_->replot();
}

void Curve::setColor(const QColor &color)
{
    QPen p = pen();
    p.setColor(color);
    setPen(p);
}

void Curve::setData(const QVector<double> &keys, const QVector<double> &values)
{
    setSamples(keys, values);
}

void Curve::show() noexcept
{
    attach(parent_);
    parent_->replot();
}
