#pragma once

#include <QLabel>


class EquationLabel : public QLabel
{
    Q_OBJECT

public:
    EquationLabel(QWidget *parent = nullptr) noexcept;
    ~EquationLabel() noexcept = default;

    [[nodiscard]] QList<double> coefficients() const;
    void setEquation(const QString &abscissaName, const QString &ordinateName, const QVector<double> &coeffs) noexcept;

private:
    const QString _PATTERN_ =
    R"(
    %1 = %2
    )";

    QList<double> coeffs_;

};
