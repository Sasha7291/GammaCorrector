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
    , temperatureButtons{new QButtonGroup{parent}}
{
    auto layout = new QVBoxLayout{parent};

    auto layout_1 = new QFormLayout;
    layout_1->addRow("Polynomial order", polynomialOrderComboBox);
    layout_1->addRow("Gamma correction \norder", gammaCorrectionOrderDoubleSpinBox);

    auto layout_2 = new QFormLayout;
    layout_2->addRow("Temperature", temperatureDoubleSpinBox);

    temperatureButtons.addButton(new QRadioButton{" °K", parent}, TemperatureTransformer::Kelvin);
    temperatureButtons.addButton(new QRadioButton{" °C", parent}, TemperatureTransformer::Celsius);
    temperatureButtons.addButton(new QRadioButton{" °F", parent}, TemperatureTransformer::Fahrenheit);
    temperatureButtons.setExclusive(true);

    auto layout_3 = new QHBoxLayout;
    for (auto &button : temperatureButtons.buttons())
        layout_3->addWidget(button);

    layout->addLayout(layout_1);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addLayout(layout_2);
    layout->addLayout(layout_3);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addWidget(offsetPlot, 1);

    parent->setLayout(layout);

    temperatureButtons.buttons().at(TemperatureTransformer::Celsius)->setChecked(true);
    temperatureDoubleSpinBox->setScale(TemperatureTransformer::Celsius);
}
