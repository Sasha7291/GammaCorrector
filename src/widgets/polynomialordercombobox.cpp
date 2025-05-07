#include "polynomialordercombobox.h"

PolynomialOrderComboBox::PolynomialOrderComboBox(QWidget *parent) noexcept
    : QComboBox{parent}
{
    for (auto i = 2ull; i < 8ull; ++i)
        addItem(QString::number(i), QVariant::fromValue(i + 1));

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
