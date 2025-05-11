#pragma once

#include "temperaturedoublespinbox.h"

#include <QButtonGroup>
#include <QPointer>
#include <QRadioButton>


class TemperaturePlotSettingsWidget;

class TemperaturePlotSettingsWidget_Ui
{

public:
    TemperaturePlotSettingsWidget_Ui(TemperaturePlotSettingsWidget *parent);
    ~TemperaturePlotSettingsWidget_Ui() = default;

    QPointer<TemperatureDoubleSpinBox> temperatureDoubleSpinBox;
    QButtonGroup temperatureButtons;

};
