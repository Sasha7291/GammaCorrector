#include "temperatureplotwidget.h"
#include "temperatureplotwidget_ui.h"

#include "temperatureplotprocessor.h"

#include <QContextMenuEvent>


TemperaturePlotWidget::TemperaturePlotWidget(QWidget *parent)
    : SubWindowWidget{parent}
    , ui{std::make_unique<TemperaturePlotWidget_Ui>(this)}
    , coeffs_{8}
{
    connect(ui->settingsWindow, &TemperaturePlotSettingsWidget::polynomialOrderChanged, this, [this](std::size_t order) -> void {
        setData(data_);
    });
}

TemperaturePlotWidget::~TemperaturePlotWidget() {}

void TemperaturePlotWidget::setData(const QList<QList<double>> &data)
{
    data_ = data;
    ui->settingsWindow->setTemperatureRange({ std::ranges::min(data[0]), std::ranges::max(data[0]) });
    ui->plot->setAxisTitles({ "T, K", "Q, dsc" });

    const auto maxVoltage = std::ranges::max(data[1]);
    for (int i = 2; i < data.size(); ++i)
    {
        auto tempData = data[i];
        for (int j = 0; j < tempData.size(); ++j)
            tempData[j] = tempData[j] / data[1][j] * maxVoltage;
        approximateData(static_cast<CurveName>(i - 2), data[0], data[i], ui->settingsWindow->polynomialOrder());
    }
}

void TemperaturePlotWidget::calculateQ()
{
    QList<double> result{ ui->settingsWindow->temperature() };

    for (int i = 0; i < 8; ++i)
    {
        double resultValue = 0.0;
        for (int j = 0; j < ui->settingsWindow->polynomialOrder(); ++j)
            resultValue += coeffs_[i][j] * std::pow(ui->settingsWindow->temperature(), j);

        result.push_back(std::round(resultValue));
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
    ui->plot->setData(curve, approximatedData[1], approximatedData[2], "Q" + QString::number(curve + 1), true);
}
