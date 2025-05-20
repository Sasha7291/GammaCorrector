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
    connect(&ui->temperatureButtons, &QButtonGroup::idClicked, ui->temperatureDoubleSpinBox, [this](int index) -> void {
        ui->temperatureDoubleSpinBox->setScale(static_cast<TemperatureTransformer::Scale>(index));
    });
}

ApproximatePlotSettingsWidget::~ApproximatePlotSettingsWidget() {}

double ApproximatePlotSettingsWidget::gammaCorrectionOrder() const
{
    return ui->gammaCorrectionOrderDoubleSpinBox->value();
}

std::size_t ApproximatePlotSettingsWidget::offsetIndex() const
{
    return ui->offsetPlot->currentMarkerPosition().first;
}

QPointF ApproximatePlotSettingsWidget::offsetPosition() const
{
    return ui->offsetPlot->currentMarkerPosition().second;
}

std::size_t ApproximatePlotSettingsWidget::polynomialOrder() const
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
    ui->offsetPlot->showMarker();
    ui->offsetPlot->setAxisOrigin(QwtPlot::xBottom, 1.0);
    // ui->offsetPlot->setAxisOrigin(QwtPlot::yLeft, 1.0);
}

void ApproximatePlotSettingsWidget::setTemperature(double temperature)
{
    ui->temperatureDoubleSpinBox->setTemperatureInKelvins(temperature);
}

double ApproximatePlotSettingsWidget::temperature() const
{
    return ui->temperatureDoubleSpinBox->currentTemparetureInKelvins();
}
