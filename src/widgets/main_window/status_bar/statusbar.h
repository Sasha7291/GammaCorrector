#pragma once

#include <QPointer>
#include <QStatusBar>


class EquationLabel;

class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() = default;

    [[nodiscard]] QList<double> coefficients() const;

public slots:
    void clear();
    void setCoefficients(const QList<double> &coeffs);

private:
    QPointer<EquationLabel> equationLabel_;

};
