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

    [[nodiscard]] QPair<std::size_t, QPointF> currentPosition() const noexcept;
    void hide();
    [[nodiscard]] inline bool isShown() const noexcept { return shown_; }
    void reset(const double origin, const double end);
    void setColor(const QColor &color);
    void setManualMoved(bool moved);
    void show();

public slots:
    void setMark(double x);

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
    bool shown_;

};
