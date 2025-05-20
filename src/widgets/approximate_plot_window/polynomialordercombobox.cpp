#include "polynomialordercombobox.h"


PolynomialOrderComboBox::PolynomialOrderComboBox(QWidget *parent) noexcept
    : QComboBox{parent}
{
    setMaximumPolynomialOrder(7ull);
    connect(this, &QComboBox::currentIndexChanged, [this]([[maybe_unused]] int index) -> void {
        emit currentOrderChanged(currentPolynomialOrder());
    });
}

std::size_t PolynomialOrderComboBox::currentPolynomialOrder() const noexcept
{
    return currentData().toULongLong();
}

void PolynomialOrderComboBox::setCurrentPolynomialOrder(std::size_t order) noexcept
{
    setCurrentText(QString::number(order - 1));
}

void PolynomialOrderComboBox::setMaximumPolynomialOrder(std::size_t order)
{
    clear();
    for (std::size_t i = 2ull; i < order + 1; ++i)
        addItem(QString::number(i), QVariant::fromValue(i + 1));
}
