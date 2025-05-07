#pragma once

#include "filterwidthcombobox.h"
#include "gammacorrectionorderdoublespinbox.h"
#include "offsetplot.h"
#include "polynomialordercombobox.h"
#include "temperaturedoublespinbox.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QPointer>
#include <QRadioButton>


class SettingsWindow;

class SettingsWindow_Ui
{

public:
    explicit SettingsWindow_Ui(SettingsWindow *parent);
    ~SettingsWindow_Ui() = default;

    QPointer<QCheckBox> filterCheckBox;
    QPointer<FilterWidthComboBox> filterWidthComboBox;
    QPointer<GammaCorrectionOrderDoubleSpinBox> gammaCorrectionOrderDoubleSpinBox;
    QPointer<OffsetPlot> offsetPlot;
    QPointer<PolynomialOrderComboBox> polynomialOrderComboBox;
    QPointer<TemperatureDoubleSpinBox> temperatureDoubleSpinBox;
    QButtonGroup temperatureButtons;

};
