#pragma once

#include <QComboBox>
#include <qglobal.h>

class FilterWidthComboBox : public QComboBox
{

public:
    explicit FilterWidthComboBox(QWidget *parent = nullptr) noexcept;
    ~FilterWidthComboBox() noexcept = default;

    [[nodiscard]] int currentWidth() const noexcept;

};
