#pragma once

#include <QPen>
#include <QwtPlotGrid>

class Grid : public QwtPlotGrid
{

public:
    explicit Grid(QwtPlot* parent)
        : QwtPlotGrid()
        , parent_(parent)
    {
        setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
        enableX(true);
        enableXMin(false);
        enableY(true);
        enableYMin(false);
        attach(parent);
    }
    Grid(const Grid&) = delete;
    Grid(Grid&&) = delete;
    ~Grid() = default;

    Grid &operator=(const Grid&) = delete;
    Grid &operator=(Grid&&) = delete;

private:
    QwtPlot *parent_;

};
