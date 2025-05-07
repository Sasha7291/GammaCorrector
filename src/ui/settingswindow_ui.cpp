#include "settingswindow_ui.h"

#include "settingswindow.h"
#include "splitter.h"

#include <QFormLayout>
#include <QVBoxLayout>


SettingsWindow_Ui::SettingsWindow_Ui(SettingsWindow *parent)
    : filterCheckBox{new QCheckBox{"Filter", parent}}
    , filterWidthComboBox{new FilterWidthComboBox{parent}}
    , gammaCorrectionOrderDoubleSpinBox{new GammaCorrectionOrderDoubleSpinBox{parent}}
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
    layout_2->addRow("", filterCheckBox);
    layout_2->addRow("Filter width", filterWidthComboBox);

    auto layout_3 = new QFormLayout;
    layout_3->addRow("Temperature", temperatureDoubleSpinBox);

    temperatureButtons.addButton(new QRadioButton{" °K", parent}, TemperatureTransformer::Kelvin);
    temperatureButtons.addButton(new QRadioButton{" °C", parent}, TemperatureTransformer::Celsius);
    temperatureButtons.addButton(new QRadioButton{" °F", parent}, TemperatureTransformer::Fahrenheit);
    temperatureButtons.setExclusive(true);

    auto layout_4 = new QHBoxLayout;
    for (auto &button : temperatureButtons.buttons())
        layout_4->addWidget(button);

    layout->addLayout(layout_1);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addLayout(layout_2);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addLayout(layout_3);
    layout->addLayout(layout_4);
    layout->addWidget(new Splitter{Splitter::Horizontal, parent});
    layout->addWidget(offsetPlot, 1);

    parent->setLayout(layout);

    filterCheckBox->setCheckState(Qt::Unchecked);
    filterWidthComboBox->setEnabled(false);
    temperatureButtons.buttons().at(TemperatureTransformer::Celsius)->setChecked(true);
    temperatureDoubleSpinBox->setScale(TemperatureTransformer::Celsius);
}
