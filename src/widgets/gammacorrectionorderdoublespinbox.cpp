#include "gammacorrectionorderdoublespinbox.h"

GammaCorrectionOrderDoubleSpinBox::GammaCorrectionOrderDoubleSpinBox(QWidget *parent) noexcept
    : QDoubleSpinBox{parent}
{
    setRange(1.0 / 2.2, 2.2);
    setDecimals(1);
    setSingleStep(0.1);
    setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
}
