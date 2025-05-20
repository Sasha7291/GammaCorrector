#include "movedmarker.h"

#include "curve.h"
#include "plot.h"

#include <QMouseEvent>
#include <QPen>
#include <QwtPickerMachine>
#include <QwtScaleDiv>


MovedMarker::MovedMarker(Plot *parent, Curve *curve)
    : QObject{parent}
    , picker_{new QwtPlotPicker{
        parent->xBottom,
        parent->yLeft,
        QwtPicker::NoRubberBand,
        QwtPicker::AlwaysOn,
        parent->canvas()
    }}
    , marker_{new QwtPlotMarker}
    , symbol_{new QwtSymbol{
        QwtSymbol::XCross,
        QBrush(Qt::NoBrush),
        QPen(Qt::darkGreen),
        QSize(10, 10)
    }}
    , dragPointStateMachine_{new QwtPickerDragPointMachine}
    , curve_{curve}
    , parent_{parent}
{
    marker_->setLinePen(QPen(Qt::darkGreen, 1.0, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    marker_->setLineStyle(QwtPlotMarker::VLine);
    marker_->setSymbol(symbol_);
    marker_->attach(parent);
    hide();

    picker_->setRubberBandPen(Qt::NoPen);
    picker_->setStateMachine(dragPointStateMachine_);
}

MovedMarker::~MovedMarker() {}

QPair<std::size_t, QPointF> MovedMarker::currentPosition() const noexcept
{
    auto index = std::min(
        std::max(
            0ull,
            static_cast<std::size_t>(std::llround((marker_->xValue() - origin_) / range_ * curve_->dataSize()))
        ),
        curve_->dataSize()
    );
    return std::make_pair(index, curve_->sample(index));
}

void MovedMarker::hide()
{
    shown_ = false;
    marker_->setVisible(false);
    disconnect(picker_, SIGNAL(moved(QPointF)), this, SLOT(move(QPointF)));
}

void MovedMarker::reset(const double origin, const double end)
{
    origin_ = origin;
    range_ = end - origin;
}

void MovedMarker::setManualMoved(bool moved)
{
    moved
        ? picker_->setStateMachine(dragPointStateMachine_)
        : picker_->setStateMachine(nullptr);
}

void MovedMarker::show()
{
    shown_ = true;
    marker_->setVisible(true);
    connect(picker_, SIGNAL(moved(QPointF)), this, SLOT(move(QPointF)));
    setMark(origin_);
}

void MovedMarker::setMark(double x)
{
    auto index = std::lround((x - origin_) / range_ * curve_->dataSize());
    marker_->setValue(curve_->sample(index));
    parent_->replot();

    emit moved(index, marker_->value());
}

void MovedMarker::move(const QPointF &pos)
{
    if (pos.x() <= origin_ || pos.x() >= origin_ + range_)
        return;

    setMark(pos.x());
}
