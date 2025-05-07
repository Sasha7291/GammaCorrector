#include "plot.h"

#include "curve.h"
#include "grid.h"
#include "legend.h"
#include "movedmarker.h"

#include <QwtLegend>
#include <QwtPlotCanvas>
#include <QwtPlotLayout>
#include <QwtScaleWidget>


Plot::Plot(QWidget *parent)
    : QwtPlot{parent}
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
    , grid_{new Grid{this}}
    , legend_{new Legend{this}}
    , movedMarker_(nullptr)
{
    auto plotCanvas = static_cast<QwtPlotCanvas*>(canvas());
    plotCanvas->setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    plotCanvas->setBorderRadius(10);
    plotLayout()->setAlignCanvasToScales(true);
    setCanvasBackground(QBrush(Qt::white));
    setAxisFont(xBottom, QFont("Bahnschrift"));
    setAxisFont(yLeft, QFont("Bahnschrift"));

    connect(legend_, SIGNAL(checked(QVariant,bool,int)), this, SLOT(legendChecked(QVariant,bool,int)));
}

Plot::~Plot() {}

QPair<int, QPointF> Plot::currentMarkerPosition() const noexcept
{
    if (movedMarker_ != nullptr)
        return movedMarker_->currentPosition();

    return {0, QPointF{}};
}

QList<QList<double>> Plot::data(int index, std::size_t size) const noexcept
{
    QList<QList<double>> result(2, QList<double>(size));

    for (int i = 0; i < size; ++i)
    {
        double x = (curves_[index]->maxXValue() - curves_[index]->minXValue()) / size * i + curves_[index]->minXValue();
        result[Qt::XAxis][i] = x;
        result[Qt::YAxis][i] = curves_[index]->interpolatedValueAt(Qt::Horizontal, x);
    }

    return result;
}

bool Plot::isMovedMarkerShown() const noexcept
{
    return movedMarker_ != nullptr && movedMarker_->isShown();
}

void Plot::setAxisOrigin(QwtAxisId axis, double origin)
{
    setAxisAutoScale(axis, false);
    setAxisScale(axis, origin, axisInterval(axis).maxValue());
    updateAxes();
}

void Plot::setAxisTitles(const QStringList &titles)
{
    axisWidget(QwtAxis::XBottom)->setTitle(titles[Qt::XAxis]);
    axisWidget(QwtAxis::YLeft)->setTitle(titles[Qt::YAxis]);
}

void Plot::setData(
    const QList<QList<double>> &keys,
    const QList<QList<double>> &values,
    const QStringList &names
)
{
    for (auto i = 0ll; i < values.size(); ++i)
        setData(i, keys[i], values[i], names[i]);
}

void Plot::setData(
    unsigned index,
    const QList<double> &keys,
    const QList<double> &values,
    const QString &name,
    bool autoScale
)
{
    if (curves_[index] == nullptr)
        curves_[index] = new Curve(this, colors_[index], name);

    curves_[index]->setData(keys, values);
    if (legend() != nullptr)
        legend_->setItemChecked(curves_[index], true);

    setAxisAutoScale(yLeft, autoScale);
    setAxisAutoScale(xBottom, autoScale);

    replot();
}

void Plot::setManualMoveMarker(bool moved)
{
    if (movedMarker_ != nullptr)
        movedMarker_->setManualMoved(moved);
}

void Plot::setMarkerPosition(const QPointF &pos)
{
    if (movedMarker_ != nullptr)
        movedMarker_->setMark(pos.x());
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
        movedMarker_ = new MovedMarker{this, curves_[0]};
        connect(movedMarker_, &MovedMarker::moved, this, &Plot::markerMoved);
    }

    movedMarker_->reset(curves_[0]->minXValue(), curves_[0]->maxXValue());
    movedMarker_->show();
}

void Plot::legendChecked(const QVariant &itemInfo, bool on, int index)
{
    index = curves_.indexOf(get<QwtPlotItem *>(itemInfo));
    on ? showCurve(index) : hideCurve(index);
}
