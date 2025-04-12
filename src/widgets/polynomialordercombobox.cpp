#include "polynomialordercombobox.h"

PolynomialOrderComboBox::PolynomialOrderComboBox(QWidget *parent) noexcept
    : QComboBox{parent}
{
    for (auto i = 2ull; i < 6ull; ++i)
        addItem(QString::number(i), QVariant::fromValue(i + 1));
}

std::size_t PolynomialOrderComboBox::currentPolynomialOrder() const noexcept
{
    return currentData().toULongLong();
}

void PolynomialOrderComboBox::setCurrentPolynomialOrder(std::size_t order) noexcept
{
    setCurrentText(QString::number(order - 1));
}
