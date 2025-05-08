#include "statusbar.h"

#include "equationlabel.h"


StatusBar::StatusBar(QWidget *parent)
    : QStatusBar{parent}
    , equationLabel_{new EquationLabel{parent}}
{
    addPermanentWidget(equationLabel_, 1);
}

QList<double> StatusBar::coefficients() const
{
    return equationLabel_->coefficients();
}

void StatusBar::clear()
{
    equationLabel_->clear();
}

void StatusBar::setCoefficients(const QList<double> &coeffs)
{
    equationLabel_->setEquation("V", "I", coeffs);
}
