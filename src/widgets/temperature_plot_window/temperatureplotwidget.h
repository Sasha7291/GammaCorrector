#pragma once

#include "subwindowwidget.h"


class TemperaturePlotWidget_Ui;

class TemperaturePlotWidget : public SubWindowWidget
{
    Q_OBJECT

public:
    TemperaturePlotWidget(QWidget *parent = nullptr);
    ~TemperaturePlotWidget() override;

    void setData(const QList<QList<double>> &data);

public slots:
    void calculateQ();

signals:
    void qCalculated(const QList<double> &Q);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    enum CurveName
    {
        Q1,
        Q2,
        Q3,
        Q4,
        Q5,
        Q6,
        Q7,
        Q8
    };

    void approximateData(
        CurveName curve,
        const QList<double> &keys,
        const QList<double> &values,
        std::size_t order
    );

    std::unique_ptr<TemperaturePlotWidget_Ui> ui;
    QList<QList<double>> coeffs_;
    QList<QList<double>> data_;

};
