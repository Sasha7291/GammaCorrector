#pragma once

#include "gammacorrectionorderdoublespinbox.h"
#include "offsetplot.h"
#include "polynomialordercombobox.h"
#include "temperaturedoublespinbox.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QPointer>
#include <QRadioButton>


class ApproximatePlotSettingsWidget;

class ApproximatePlotSettingsWidget_Ui
{

public:
    explicit ApproximatePlotSettingsWidget_Ui(ApproximatePlotSettingsWidget *parent);
    ~ApproximatePlotSettingsWidget_Ui() = default;

    QPointer<GammaCorrectionOrderDoubleSpinBox> gammaCorrectionOrderDoubleSpinBox;
    QPointer<OffsetPlot> offsetPlot;
    QPointer<PolynomialOrderComboBox> polynomialOrderComboBox;
    QPointer<TemperatureDoubleSpinBox> temperatureDoubleSpinBox;
    QButtonGroup temperatureButtons;

};
