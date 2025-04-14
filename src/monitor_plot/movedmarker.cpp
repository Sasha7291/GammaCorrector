#include "movedmarker.h"

#include "curve.h"
#include "plot.h"

#include <QMouseEvent>
#include <QPen>
#include <QwtPickerMachine>
#include <QwtScaleDiv>


MovedMarker::MovedMarker(Plot *parent, Curve *curve)
    : QObject(parent)
    , picker_(std::make_unique<QwtPlotPicker>(
        parent->xBottom,
        parent->yLeft,
        QwtPicker::NoRubberBand,
        QwtPicker::AlwaysOn,
        parent->canvas())
    )
    , marker_(std::make_unique<QwtPlotMarker>())
    , symbol_(std::make_unique<QwtSymbol>(
        QwtSymbol::XCross,
        QBrush(Qt::NoBrush),
        QPen(Qt::darkGreen),
        QSize(10, 10)
    ))
    , dragPointStateMachine_(new QwtPickerDragPointMachine)
    , curve_(curve)
    , parent_(parent)
{
    marker_->setLinePen(QPen(Qt::darkGreen, 1.0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    marker_->setLineStyle(QwtPlotMarker::VLine);
    marker_->setSymbol(symbol_.get());
    marker_->attach(parent);

    picker_->setRubberBandPen(Qt::NoPen);
    picker_->setStateMachine(dragPointStateMachine_);

    connect(picker_.get(), SIGNAL(moved(QPointF)), this, SLOT(move(QPointF)));
}

MovedMarker::~MovedMarker()
{
    delete dragPointStateMachine_;
}

void MovedMarker::hide()
{
    shown_ = false;
    marker_->detach();
    disconnect(picker_.get(), SIGNAL(moved(QPointF)), this, SLOT(move(QPointF)));
}

void MovedMarker::reset(const double origin, const double end)
{
    origin_ = origin;
    range_ = end - origin;
    marker_->setValue(origin + 0.05 * range_, 0.0);

    setMark();
}

void MovedMarker::show()
{
    shown_ = true;
    marker_->attach(parent_);
    connect(picker_.get(), SIGNAL(moved(QPointF)), this, SLOT(move(QPointF)));
    setMark();
}

void MovedMarker::setMark()
{
    long unsigned index = std::lround(marker_->xValue() - origin_) / range_ * curve_->dataSize();
    marker_->setValue(curve_->sample(index));
    parent_->replot();

    emit moved(index, marker_->value());
}

void MovedMarker::move(const QPointF &pos)
{
    if (pos.x() < origin_ + 0.005 * range_
        || pos.x() > (origin_ + range_) - 0.005 * range_)
        return;

    int index = (pos.x() - origin_) / range_ * curve_->dataSize();
    marker_->setValue(curve_->sample(index));
    parent_->replot();

    emit moved(index, marker_->value());
}
