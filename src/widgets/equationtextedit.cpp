#include "equationtextedit.h"

#include "utils.h"


EquationTextEdit::EquationTextEdit(QWidget *parent) noexcept
    : QTextEdit{parent}
{
    setFixedWidth(325);
    setMaximumHeight(60);
}

void EquationTextEdit::setEquation(const QString &abscissaName, const QString &ordinateName, const QVector<double> &coeffs) noexcept
{
    QString tempEquation = QString{};

    for (auto i = 0ll; i < coeffs.size(); ++i)
        if (i == 0ll)
            tempEquation += QString::number(coeffs[0]);
        else if (i == 1ll)
            tempEquation += " " + utils::sign(coeffs[1]) + " " + QString::number(std::abs(coeffs[1])) + " * " + abscissaName;
        else
            tempEquation += " " + utils::sign(coeffs[i]) + " " + QString::number(std::abs(coeffs[i])) + " * " + abscissaName + "<sup>" + QString::number(i) + "</sup>";

    setHtml(_PATTERN_.arg(ordinateName, tempEquation));
}
