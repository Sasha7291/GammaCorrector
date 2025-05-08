#include "equationlabel.h"

#include "utils.h"


EquationLabel::EquationLabel(QWidget *parent) noexcept
    : QLabel{parent}
    , coeffs_{}
{
    setTextFormat(Qt::RichText);
}

QList<double> EquationLabel::coefficients() const
{
    return coeffs_;
}

void EquationLabel::setEquation(const QString &abscissaName, const QString &ordinateName, const QVector<double> &coeffs) noexcept
{
    coeffs_ = coeffs;
    QString temp = QString{};

    for (auto i = 0ll; i < coeffs.size(); ++i)
        if (i == 0ll)
            temp += QString::number(coeffs[0]);
        else if (i == 1ll)
            temp += " " + utils::sign(coeffs[1]) + " " + QString::number(std::abs(coeffs[1])) + " * " + abscissaName;
        else [[likely]]
            temp += " " + utils::sign(coeffs[i]) + " " + QString::number(std::abs(coeffs[i])) + " * " + abscissaName
                        + "<sup>" + QString::number(i) + "</sup>";

    setText(_PATTERN_.arg(ordinateName, temp));
}
