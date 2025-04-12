#pragma once

#include <QwtLegend>
#include <QwtPlot>

class Legend : public QwtLegend
{

public:
    explicit Legend(QwtPlot *parent)
        : QwtLegend()
        , parent_(parent)
    {
        setFont(QFont("Bahnschrift"));
        setDefaultItemMode(QwtLegendData::Clickable);
        parent->insertLegend(this);
    }
    Legend(const Legend&) = delete;
    Legend(Legend&&) = delete;
    ~Legend() = default;

    Legend &operator=(const Legend&) = delete;
    Legend &operator=(Legend&&) = delete;

private:
    QwtPlot *parent_;

};
