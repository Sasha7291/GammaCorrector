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
    try
    {
        data_ = data;
        const auto [minT, maxT] = std::ranges::minmax(data[0]);
        ui->settingsWindow->setTemperatureRange({ minT, maxT });
        // disconnect(ui->settingsWindow, &TemperaturePlotSettingsWidget::polynomialOrderChanged, this, nullptr);
        // ui->settingsWindow->setMaximumPolynomialOrder(std::min(7ll, data[0].size()));
        // connect(ui->settingsWindow, &TemperaturePlotSettingsWidget::polynomialOrderChanged, this, [this](std::size_t order) -> void {
        //     setData(data_);
        // });
        ui->plot->setAxisTitles({ "T, K", "Q, dsc" });

        const auto offset = data[1][data[0].indexOf(minT)];
        const auto maxVoltage = std::ranges::max(data[2]) - offset;
        for (int i = 3; i < data.size(); ++i)
        {
            auto tempData = data[i];
            for (int j = 0; j < tempData.size(); ++j)
                tempData[j] = (tempData[j] / 1023.0 * data[1][j] - offset) / maxVoltage * 1023.0;
            approximateData(static_cast<CurveName>(i - 3), data[0], data[i], ui->settingsWindow->polynomialOrder());
        }
    }
    catch (const std::exception &exception)
    {
        qWarning() << exception.what();
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
