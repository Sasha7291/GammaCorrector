#include "approximateplotsettingswidget.h"
#include "approximateplotsettingswidget_ui.h"


ApproximatePlotSettingsWidget::ApproximatePlotSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , ui{std::make_unique<ApproximatePlotSettingsWidget_Ui>(this)}
{
    setWindowFlag(Qt::Window, true);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
    setWindowFlag(Qt::CustomizeWindowHint, true);
    setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setWindowTitle("Settings");

    connect(ui->gammaCorrectionOrderDoubleSpinBox, &GammaCorrectionOrderDoubleSpinBox::valueChanged, this, &ApproximatePlotSettingsWidget::gammaCorrectionDegreeChanged);
    connect(ui->polynomialOrderComboBox, &PolynomialOrderComboBox::currentOrderChanged, this, &ApproximatePlotSettingsWidget::polynomialOrderChanged);
    connect(ui->offsetPlot, &Plot::markerMoved, this, &ApproximatePlotSettingsWidget::offsetChanged);
    connect(ui->minCurrentDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [this](double value) -> void {
        emit currentRangeChanged({ value, ui->maxCurrentDoubleSpinBox->value() });
    });
    connect(ui->maxCurrentDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [this](double value) -> void {
        emit currentRangeChanged({ ui->minCurrentDoubleSpinBox->value(), value });
    });
    connect(ui->minVoltageDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [this](double value) -> void {
        emit voltageRangeChanged({ value, ui->maxVoltageDoubleSpinBox->value() });
    });
    connect(ui->maxVoltageDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, [this](double value) -> void {
        emit voltageRangeChanged({ ui->minVoltageDoubleSpinBox->value(), value });
    });
    connect(&ui->temperatureButtons, &QButtonGroup::idClicked, ui->temperatureDoubleSpinBox, [this](int index) -> void {
        ui->temperatureDoubleSpinBox->setScale(static_cast<TemperatureTransformer::Scale>(index));
    });
}

ApproximatePlotSettingsWidget::~ApproximatePlotSettingsWidget() {}

QPair<double, double> ApproximatePlotSettingsWidget::currentRange() const
{
    return { ui->minCurrentDoubleSpinBox->value(), ui->maxCurrentDoubleSpinBox->value() };
}

double ApproximatePlotSettingsWidget::gammaCorrectionOrder() const
{
    return ui->gammaCorrectionOrderDoubleSpinBox->value();
}

int ApproximatePlotSettingsWidget::offsetIndex() const
{
    return ui->offsetPlot->currentMarkerPosition().first;
}

QPointF ApproximatePlotSettingsWidget::offsetPosition() const
{
    return ui->offsetPlot->currentMarkerPosition().second;
}

int ApproximatePlotSettingsWidget::polynomialOrder() const
{
    return ui->polynomialOrderComboBox->currentPolynomialOrder();
}

void ApproximatePlotSettingsWidget::setOffsetPosition(const QPointF &pos)
{
    ui->offsetPlot->setMarkerPosition(pos);
}

void ApproximatePlotSettingsWidget::setOffsetPlotData(const QList<double> &keys, const QList<double> &values)
{
    ui->offsetPlot->setData(0, keys, values, "", true);
}

void ApproximatePlotSettingsWidget::setTemperature(double temperature)
{
    ui->temperatureDoubleSpinBox->setTemperatureInKelvins(temperature);
}

double ApproximatePlotSettingsWidget::temperature() const
{
    return ui->temperatureDoubleSpinBox->currentTemparetureInKelvins();
}

QPair<double, double> ApproximatePlotSettingsWidget::voltageRange() const
{
    return { ui->minVoltageDoubleSpinBox->value(), ui->maxVoltageDoubleSpinBox->value() };
}
