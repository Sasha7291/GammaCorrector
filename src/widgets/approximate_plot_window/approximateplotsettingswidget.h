#pragma once

#include <QWidget>


class ApproximatePlotSettingsWidget_Ui;

class ApproximatePlotSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApproximatePlotSettingsWidget(QWidget *parent = nullptr);
    ~ApproximatePlotSettingsWidget();

    [[nodiscard]] QPair<double, double> currentRange() const;
    [[nodiscard]] double gammaCorrectionOrder() const;
    [[nodiscard]] int offsetIndex() const;
    [[nodiscard]] QPointF offsetPosition() const;
    [[nodiscard]] int polynomialOrder() const;
    void setOffsetPosition(const QPointF &pos);
    void setOffsetPlotData(const QList<double> &keys, const QList<double> &values);
    void setTemperature(double temperature);
    [[nodiscard]] double temperature() const;
    [[nodiscard]] QPair<double, double> voltageRange() const;

signals:
    void currentRangeChanged(const QPair<double, double> &range);
    void gammaCorrectionDegreeChanged(double degree);
    void offsetChanged(int index, const QPointF &pos);
    void polynomialOrderChanged(std::size_t order);
    void voltageRangeChanged(const QPair<double, double> &range);

private:
    std::unique_ptr<ApproximatePlotSettingsWidget_Ui> ui;

};
