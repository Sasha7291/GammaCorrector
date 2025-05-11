#pragma once

#include <QWidget>


class ApproximatePlotSettingsWidget_Ui;

class ApproximatePlotSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApproximatePlotSettingsWidget(QWidget *parent = nullptr);
    ~ApproximatePlotSettingsWidget();

    [[nodiscard]] double gammaCorrectionOrder() const;
    [[nodiscard]] int offsetIndex() const;
    [[nodiscard]] QPointF offsetPosition() const;
    [[nodiscard]] int polynomialOrder() const;
    void setOffsetPosition(const QPointF &pos);
    void setOffsetPlotData(const QList<double> &keys, const QList<double> &values);
    void setTemperature(double temperature);
    [[nodiscard]] double temperature() const;

signals:
    void gammaCorrectionDegreeChanged(double degree);
    void offsetChanged(int index, const QPointF &pos);
    void polynomialOrderChanged(std::size_t order);

private:
    std::unique_ptr<ApproximatePlotSettingsWidget_Ui> ui;

};
