#pragma once

#include <QwtLegend>


class QwtPlot;
class QwtPlotItem;

class Legend : public QwtLegend
{

public:
    explicit Legend(QwtPlot *parent);
    Legend(const Legend &) = delete;
    Legend(Legend &&) = delete;
    ~Legend() = default;

    Legend &operator=(const Legend &) = delete;
    Legend &operator=(Legend &&) = delete;

    [[nodiscard]] std::optional<bool> isItemChecked(QwtPlotItem *item) const;
    void setItemChecked(QwtPlotItem *item, bool checked);

private:
    QwtPlot *parent_;

};
