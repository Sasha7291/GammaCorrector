#include "temperatureplotsettingswidget.h"
#include "temperatureplotsettingswidget_ui.h"


TemperaturePlotSettingsWidget::TemperaturePlotSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , ui{std::make_unique<TemperaturePlotSettingsWidget_Ui>(this)}
{}

TemperaturePlotSettingsWidget::~TemperaturePlotSettingsWidget() {}

void TemperaturePlotSettingsWidget::setTemperatureRange(const QPair<double, double> &range)
{
    auto previousScale = ui->temperatureDoubleSpinBox->currentScale();
    ui->temperatureDoubleSpinBox->setScale(TemperatureTransformer::Kelvin);
    ui->temperatureDoubleSpinBox->setRange(range.first, range.second);
    ui->temperatureDoubleSpinBox->setScale(previousScale);
}

void TemperaturePlotSettingsWidget::setTemperature(double temperature)
{
    ui->temperatureDoubleSpinBox->setTemperatureInKelvins(temperature);
}

double TemperaturePlotSettingsWidget::temperature() const
{
    return ui->temperatureDoubleSpinBox->currentTemparetureInKelvins();
}

