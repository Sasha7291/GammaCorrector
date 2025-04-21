#pragma once

#include <QColor>
#include <QwtPlotCurve>

class Curve : public QwtPlotCurve
{

public:
    explicit Curve(QwtPlot *parent, const QColor color = Qt::red, const QString &name = "Curve");
    Curve(const Curve&) = delete;
    Curve(Curve&&) = delete;
    ~Curve() = default;

    Curve &operator=(const Curve&) = delete;
    Curve &operator=(Curve&&) = delete;

    void hide() noexcept;
    void setColor(const QColor &color);
    void setData(const QVector<double> &keys, const QVector<double> &values);
    void show() noexcept;

private:
    QwtPlot *parent_;

};
