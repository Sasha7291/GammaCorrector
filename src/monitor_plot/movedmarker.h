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
    inline bool isShown() const { return shown_; }
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
    std::unique_ptr<QwtPlotPicker> picker_;
    std::unique_ptr<QwtPlotMarker> marker_;
    std::unique_ptr<QwtSymbol> symbol_;
    QwtPickerMachine *dragPointStateMachine_;
    Curve *curve_;
    Plot *parent_;

    double origin_;
    double range_;
    bool shown_;

};
