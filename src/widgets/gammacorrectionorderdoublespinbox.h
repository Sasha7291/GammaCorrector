#pragma once

#include <QDoubleSpinBox>


class GammaCorrectionOrderDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit GammaCorrectionOrderDoubleSpinBox(QWidget *parent = nullptr) noexcept;
    ~GammaCorrectionOrderDoubleSpinBox() noexcept = default;

};
