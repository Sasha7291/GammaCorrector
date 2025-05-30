#include "temperatureplotsettingswidget_ui.h"

#include "splitter.h"
#include "temperatureplotsettingswidget.h"

#include <QFormLayout>
#include <QVBoxLayout>


TemperaturePlotSettingsWidget_Ui::TemperaturePlotSettingsWidget_Ui(TemperaturePlotSettingsWidget *parent)
    : polynomialOrderComboBox{new PolynomialOrderComboBox{parent}}
    , temperatureDoubleSpinBox{new TemperatureDoubleSpinBox{parent}}
    , temperatureButtons{new QButtonGroup{parent}}
{
    auto layout = new QVBoxLayout{parent};

    auto layout_1 = new QFormLayout;
    layout_1->addRow("Order", polynomialOrderComboBox);

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
    layout->addWidget(new Splitter{Splitter::Horizontal});
    layout->addLayout(layout_2);
    layout->addLayout(layout_3);

    parent->setLayout(layout);

    temperatureButtons.buttons().at(TemperatureTransformer::Celsius)->setChecked(true);
    temperatureDoubleSpinBox->setScale(TemperatureTransformer::Celsius);
}
