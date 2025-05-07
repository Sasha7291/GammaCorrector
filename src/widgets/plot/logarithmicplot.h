#pragma once

#include "plot.h"
#include <qglobal.h>

class LogarithmicPlot : public Plot
{
    Q_OBJECT

public:
    enum AxisFlag
    {
        X = 0x01,
        Y = 0x02,
        Both = X | Y
    };
    Q_DECLARE_FLAGS(Axis, AxisFlag)

    explicit LogarithmicPlot(Axis axis, QWidget *parent = nullptr);
    virtual ~LogarithmicPlot() override;

    void setData(
        unsigned index,
        const QList<double> &keys,
        const QList<double> &values,
        const QString &name,
        bool autoScale = false
    ) override;

};
