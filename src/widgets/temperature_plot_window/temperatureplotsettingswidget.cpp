#include "temperatureplotsettingswidget.h"
#include "temperatureplotsettingswidget_ui.h"


TemperaturePlotSettingsWidget::TemperaturePlotSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , ui{std::make_unique<TemperaturePlotSettingsWidget_Ui>(this)}
{
    connect(ui->polynomialOrderComboBox, &PolynomialOrderComboBox::currentOrderChanged, this, &TemperaturePlotSettingsWidget::polynomialOrderChanged);
}

TemperaturePlotSettingsWidget::~TemperaturePlotSettingsWidget() {}

std::size_t TemperaturePlotSettingsWidget::polynomialOrder() const
{
    return ui->polynomialOrderComboBox->currentPolynomialOrder();
}

void TemperaturePlotSettingsWidget::setMaximumPolynomialOrder(std::size_t order)
{
    ui->polynomialOrderComboBox->setMaximumPolynomialOrder(order);
}

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

