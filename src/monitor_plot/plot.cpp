#include "plot.h"

#include "curve.h"

#include <QwtLegend>
#include <QwtPlotCanvas>
#include <QwtPlotLayout>
#include <QwtScaleWidget>


Plot::Plot(QWidget *parent)
    : QwtPlot(parent)
    , curves_{12}
    , colors_{
        Qt::red,
        Qt::blue,
        Qt::cyan,
        Qt::magenta,
        Qt::yellow,
        Qt::gray,
        Qt::darkRed,
        Qt::darkBlue,
        Qt::darkCyan,
        Qt::darkMagenta,
        Qt::darkYellow,
        Qt::darkGray
    }
    , grid_(std::make_unique<Grid>(this))
    , legend_(std::make_unique<Legend>(this))
    , movedMarker_(nullptr)
{
    auto plotCanvas = static_cast<QwtPlotCanvas*>(canvas());
    plotCanvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    plotCanvas->setBorderRadius(10);
    plotLayout()->setAlignCanvasToScales(true);
    setCanvasBackground(QBrush(Qt::white));
    setAxisFont(xBottom, QFont("Bahnschrift"));
    setAxisFont(yLeft, QFont("Bahnschrift"));
}

std::pair<int, QPointF> Plot::currentMarkerPosition() const noexcept
{
    return movedMarker_->currentPosition();
}

bool Plot::isMovedMarkerShown() const noexcept
{
    return movedMarker_ != nullptr && movedMarker_->isShown();
}

void Plot::setData(
    const QVector<QVector<double>> &keys,
    const QVector<QVector<double>> &values,
    const QStringList &names
)
{
    for (auto i = 0ll; i < values.size(); ++i)
        setData(i, keys[i], values[i], names[i]);

    replot();
}

void Plot::setData(
    unsigned index,
    const QVector<double> &keys,
    const QVector<double> &values,
    const QString &name
)
{
    if (curves_[index] == nullptr)
    {
        curves_[index] = new Curve(this, colors_[index], name);
        curves_[index]->setZ(index);
    }

    curves_[index]->setData(keys, values);

    setAxisAutoScale(yLeft, true);
    setAxisAutoScale(xBottom, true);
}

void Plot::hideCurve(int index)
{
    if (curves_[index] != nullptr)
        curves_[index]->hide();
}

void Plot::hideMarker()
{
    if (movedMarker_ != nullptr)
        movedMarker_->hide();
}

void Plot::showCurve(int index)
{
    if (curves_[index] != nullptr)
        curves_[index]->show();
}

void Plot::showMarker()
{
    if (movedMarker_ == nullptr)
    {
        movedMarker_ = std::make_unique<MovedMarker>(this, curves_[0]);
        connect(movedMarker_.get(), &MovedMarker::moved, this, &Plot::markerMoved);
    }

    movedMarker_->reset(curves_[0]->minXValue(), curves_[0]->maxXValue());
    movedMarker_->show();
}
