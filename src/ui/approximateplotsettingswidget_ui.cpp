#include "approximateplotsettingswidget_ui.h"

#include "approximateplotsettingswidget.h"
#include "splitter.h"

#include <QFormLayout>
#include <QVBoxLayout>


ApproximatePlotSettingsWidget_Ui::ApproximatePlotSettingsWidget_Ui(ApproximatePlotSettingsWidget *parent)
    : gammaCorrectionOrderDoubleSpinBox{new GammaCorrectionOrderDoubleSpinBox{parent}}
    , offsetPlot{new OffsetPlot{parent}}
    , polynomialOrderComboBox{new PolynomialOrderComboBox{parent}}
    , temperatureDoubleSpinBox{new TemperatureDoubleSpinBox{parent}}
    , minVoltageDoubleSpinBox{new QDoubleSpinBox{parent}}
    , maxVoltageDoubleSpinBox{new QDoubleSpinBox{parent}}
    , minCurrentDoubleSpinBox{new QDoubleSpinBox{parent}}
    , maxCurrentDoubleSpinBox{new QDoubleSpinBox{parent}}
    , temperatureButtons{new QButtonGroup{parent}}
{
    auto layout = new QVBoxLayout{parent};

    auto layout_1 = new QFormLayout;
    layout_1->addRow("Polynomial order", polynomialOrderComboBox);
    layout_1->addRow("Gamma correction \norder", gammaCorrectionOrderDoubleSpinBox);

    auto layout_2 = new QFormLayout;
    layout_2->addRow("Voltage from", minVoltageDoubleSpinBox);
    layout_2->addRow("Current from", minCurrentDoubleSpinBox);

    auto layout_3 = new QFormLayout;
    layout_3->addRow("to", maxVoltageDoubleSpinBox);
    layout_3->addRow("to", maxCurrentDoubleSpinBox);

    auto layout_4 = new QHBoxLayout;
    layout_4->addLayout(layout_2);
    layout_4->addLayout(layout_3);

    auto layout_5 = new QFormLayout;
    layout_5->addRow("Temperature", temperatureDoubleSpinBox);

    temperatureButtons.addButton(new QRadioButton{" °K", parent}, TemperatureTransformer::Kelvin);
    temperatureButtons.addButton(new QRadioButton{" °C", parent}, TemperatureTransformer::Celsius);
    temperatureButtons.addButton(new QRadioButton{" °F", parent}, TemperatureTransformer::Fahrenheit);
    temperatureButtons.setExclusive(true);

    auto layout_6 = new QHBoxLayout;
    for (auto &button : temperatureButtons.buttons())
        layout_6->addWidget(button);

    layout->addLayout(layout_1);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addLayout(layout_4);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addLayout(layout_5);
    layout->addLayout(layout_6);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addWidget(offsetPlot, 1);

    parent->setLayout(layout);

    temperatureButtons.buttons().at(TemperatureTransformer::Celsius)->setChecked(true);
    temperatureDoubleSpinBox->setScale(TemperatureTransformer::Celsius);
    minCurrentDoubleSpinBox->setValue(0.0);
    minCurrentDoubleSpinBox->setSuffix(" A");
    maxCurrentDoubleSpinBox->setValue(0.05);
    maxCurrentDoubleSpinBox->setSuffix(" A");
    minVoltageDoubleSpinBox->setValue(0.0);
    minVoltageDoubleSpinBox->setSuffix(" V");
    maxVoltageDoubleSpinBox->setValue(5.00);
    maxVoltageDoubleSpinBox->setSuffix(" V");
}
