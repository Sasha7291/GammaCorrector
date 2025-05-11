#include "temperatureplotwidget.h"
#include "temperatureplotwidget_ui.h"

#include "temperatureplotprocessor.h"

#include <QContextMenuEvent>


TemperaturePlotWidget::TemperaturePlotWidget(QWidget *parent)
    : SubWindowWidget{parent}
    , ui{std::make_unique<TemperaturePlotWidget_Ui>(this)}
    , coeffs_{8}
{}

TemperaturePlotWidget::~TemperaturePlotWidget() {}

void TemperaturePlotWidget::setData(const QList<QList<double>> &data)
{
    ui->settingsWindow->setTemperatureRange({ std::ranges::min(data[0]), std::ranges::max(data[0]) });
    ui->plot->setAxisTitles({ "T, K", "Q, dsc" });

    for (int i = 2; i < data.size(); ++i)
        approximateData(static_cast<CurveName>(i - 2), data[0], data[i], 3);
}

void TemperaturePlotWidget::calculateQ()
{
    QList<double> result{ ui->settingsWindow->temperature() };

    for (int i = 0; i < 8; ++i)
    {
        double resultValue = 0.0;
        for (int j = 0; j < 4; ++j)
            resultValue += coeffs_[i][j] * std::pow(ui->settingsWindow->temperature(), j);

        result.push_back(resultValue);
    }

    emit qCalculated(result);
}

void TemperaturePlotWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse)
        ui->showContextMenu(event->pos());
}

void TemperaturePlotWidget::approximateData(CurveName curve, const QList<double> &keys, const QList<double> &values, std::size_t order)
{
    const auto approximatedData = TemperaturePlotProcessor{}.approximatedData(keys, values, order);
    coeffs_[curve] = approximatedData[0];
    ui->plot->setData(curve, approximatedData[1], approximatedData[2], "I_app", true);
}
