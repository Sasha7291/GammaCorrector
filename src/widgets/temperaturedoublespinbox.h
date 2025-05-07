#pragma once

#include "temperaturetransformer.h"

#include <QDoubleSpinBox>


class TemperatureDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit TemperatureDoubleSpinBox(QWidget *parent = nullptr);
    ~TemperatureDoubleSpinBox() = default;

    [[nodiscard]] TemperatureTransformer::Scale currentScale() const;
    [[nodiscard]] double currentTemparetureInKelvins() const;
    void setScale(TemperatureTransformer::Scale scale);
    void setTemperatureInKelvins(double temperature);

private:
    TemperatureTransformer::Scale scale_;
    QStringList suffixes_;

};
