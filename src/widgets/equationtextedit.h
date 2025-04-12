#pragma once

#include <QTextEdit>


class EquationTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    EquationTextEdit(QWidget *parent = nullptr) noexcept;
    ~EquationTextEdit() noexcept = default;

    void setEquation(const QString &abscissaName, const QString &ordinateName, const QVector<double> &coeffs) noexcept;

private:
    const QString _PATTERN_ =
    R"(
    %1 = %2
    )";

};
