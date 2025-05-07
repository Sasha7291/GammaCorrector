#pragma once

#include "logarithmicplot.h"


class OffsetPlot : public LogarithmicPlot
{
    Q_OBJECT

public:
    explicit OffsetPlot(QWidget *parent = nullptr);
    ~OffsetPlot() override;

    void setData(
        const QList<QList<double>> &keys,
        const QList<QList<double>> &values,
        const QStringList &names
    ) override;
    void setData(
        unsigned index,
        const QList<double> &keys,
        const QList<double> &values,
        const QString &name,
        bool autoScale = false
    ) override;

};
