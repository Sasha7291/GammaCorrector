#pragma once

#include <QWidget>


class TemperaturePlotSettingsWidget_Ui;

class TemperaturePlotSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemperaturePlotSettingsWidget(QWidget *parent = nullptr);
    ~TemperaturePlotSettingsWidget();

    void setTemperatureRange(const QPair<double, double> &range);
    void setTemperature(double temperature);
    [[nodiscard]] double temperature() const;

private:
    std::unique_ptr<TemperaturePlotSettingsWidget_Ui> ui;

};
