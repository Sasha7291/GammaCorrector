#pragma once

#include <QWidget>


class TemperaturePlotSettingsWidget_Ui;

class TemperaturePlotSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemperaturePlotSettingsWidget(QWidget *parent = nullptr);
    ~TemperaturePlotSettingsWidget();

    [[nodiscard]] std::size_t polynomialOrder() const;
    void setMaximumPolynomialOrder(std::size_t order);
    void setTemperatureRange(const QPair<double, double> &range);
    void setTemperature(double temperature);
    [[nodiscard]] double temperature() const;

signals:
    void polynomialOrderChanged(std::size_t order);

private:
    std::unique_ptr<TemperaturePlotSettingsWidget_Ui> ui;

};
