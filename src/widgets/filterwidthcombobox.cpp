#include "filterwidthcombobox.h"

FilterWidthComboBox::FilterWidthComboBox(QWidget *parent) noexcept
    : QComboBox{parent}
{
    for (int i = 1; i < 6; ++i)
        addItem(QString::number(2 * i + 1), QVariant::fromValue(2 * i + 1));
}

int FilterWidthComboBox::currentWidth() const noexcept
{
    return itemData(currentIndex()).toInt();
}
