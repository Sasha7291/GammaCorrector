#include "gammacorrectionorderdoublespinbox.h"

GammaCorrectionOrderDoubleSpinBox::GammaCorrectionOrderDoubleSpinBox(QWidget *parent) noexcept
    : QDoubleSpinBox{parent}
{
    setRange(1.0 / 2.2, 2.2);
    setDecimals(2);
    setSingleStep(0.01);
    setCorrectionMode(CorrectToNearestValue);
    setButtonSymbols(PlusMinus);
}
