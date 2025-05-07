#pragma once

#include <QWidget>


class SettingsWindow_Ui;

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    [[nodiscard]] int filterWidth() const;
    [[nodiscard]] double gammaCorrectionOrder() const;
    [[nodiscard]] bool isFilter() const;
    [[nodiscard]] int offsetIndex() const;
    [[nodiscard]] QPointF offsetPosition() const;
    [[nodiscard]] int polynomialOrder() const;
    void setOffsetPlotData(const QList<double> &keys, const QList<double> &values);
    void setTemperature(double temperature);
    [[nodiscard]] double temperature() const;

signals:
    void filterChecked(bool checked);
    void filterWidthChanged(int width);
    void gammaCorrectionDegreeChanged(double degree);
    void polynomialOrderChanged(std::size_t order);
    void offsetChanged(int index, const QPointF &pos);

private:
    std::unique_ptr<SettingsWindow_Ui> ui;

};
