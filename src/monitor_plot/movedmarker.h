#pragma once

#include <QObject>
#include <QwtPlotMarker>
#include <QwtPlotPicker>
#include <QwtSymbol>

class Plot;
class Curve;

class MovedMarker : public QObject
{
    Q_OBJECT

public:
    explicit MovedMarker(Plot *parent, Curve *curve);
    MovedMarker(const MovedMarker&) = delete;
    MovedMarker(MovedMarker&&) = delete;
    ~MovedMarker();

    MovedMarker &operator=(const MovedMarker&) = delete;
    MovedMarker &operator=(MovedMarker&&) = delete;

    void hide();
    void reset(const double origin, const double end);
    void setColor(const QColor &color);
    void show();

public slots:
    void setMark();

signals:
    void moved(int index, const QPointF &pos);

private slots:
    void move(const QPointF &pos);

private:
    QwtPlotPicker *picker_;
    QwtPlotMarker *marker_;
    QwtSymbol *symbol_;
    QwtPickerMachine *dragPointStateMachine_;
    Curve *curve_;
    Plot *parent_;

    double origin_;
    double range_;

};
