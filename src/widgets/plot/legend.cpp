#include "legend.h"

#include <QwtLegendLabel>
#include <QwtPlot>


Legend::Legend(QwtPlot *parent)
    : QwtLegend{}
    , parent_{parent}
{
    setFont(QFont("Bahnschrift"));
    setDefaultItemMode(QwtLegendData::Checkable);
    parent->insertLegend(this);
}

std::optional<bool> Legend::isItemChecked(QwtPlotItem *item) const
{
    if (auto label = static_cast<QwtLegendLabel *>(legendWidget(parent_->itemToInfo(item))))
        return label->isChecked();

    return std::nullopt;
}

void Legend::setItemChecked(QwtPlotItem *item, bool checked)
{
    if (auto label = static_cast<QwtLegendLabel *>(legendWidget(parent_->itemToInfo(item))))
    {
        label->setChecked(checked);
        updateWidget(label, item->legendData().at(0));
    }
}
