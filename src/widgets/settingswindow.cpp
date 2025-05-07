#include "settingswindow.h"
#include "settingswindow_ui.h"


SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , ui{std::make_unique<SettingsWindow_Ui>(this)}
{
    setWindowFlag(Qt::Window, true);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
    setWindowFlag(Qt::CustomizeWindowHint, true);
    setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    setWindowTitle("Settings");

    connect(ui->filterCheckBox, &QCheckBox::checkStateChanged, this, &SettingsWindow::filterChecked);
    connect(ui->filterWidthComboBox, &FilterWidthComboBox::currentWidthChanged, this, &SettingsWindow::filterWidthChanged);
    connect(ui->gammaCorrectionOrderDoubleSpinBox, &GammaCorrectionOrderDoubleSpinBox::valueChanged, this, &SettingsWindow::gammaCorrectionDegreeChanged);
    connect(ui->polynomialOrderComboBox, &PolynomialOrderComboBox::currentOrderChanged, this, &SettingsWindow::polynomialOrderChanged);
    connect(ui->offsetPlot, &Plot::markerMoved, this, &SettingsWindow::offsetChanged);
    connect(ui->filterCheckBox, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state) -> void {
        ui->filterWidthComboBox->setEnabled(state == Qt::Checked);
    });
    connect(&ui->temperatureButtons, &QButtonGroup::idClicked, ui->temperatureDoubleSpinBox, [this](int index) -> void {
        ui->temperatureDoubleSpinBox->setScale(static_cast<TemperatureTransformer::Scale>(index));
    });
}

SettingsWindow::~SettingsWindow() {}

int SettingsWindow::filterWidth() const
{
    return ui->filterWidthComboBox->currentWidth();
}

double SettingsWindow::gammaCorrectionOrder() const
{
    return ui->gammaCorrectionOrderDoubleSpinBox->value();
}

bool SettingsWindow::isFilter() const
{
    return ui->filterCheckBox->checkState() == Qt::Checked;
}

int SettingsWindow::offsetIndex() const
{
    return ui->offsetPlot->currentMarkerPosition().first;
}

QPointF SettingsWindow::offsetPosition() const
{
    return ui->offsetPlot->currentMarkerPosition().second;
}

int SettingsWindow::polynomialOrder() const
{
    return ui->polynomialOrderComboBox->currentPolynomialOrder();
}

void SettingsWindow::setOffsetPlotData(const QList<double> &keys, const QList<double> &values)
{
    ui->offsetPlot->setData(0, keys, values, "", true);
}

void SettingsWindow::setTemperature(double temperature)
{
    ui->temperatureDoubleSpinBox->setTemperatureInKelvins(temperature);
}

double SettingsWindow::temperature() const
{
    return ui->temperatureDoubleSpinBox->currentTemparetureInKelvins();
}
