#include "filterwidthcombobox.h"

FilterWidthComboBox::FilterWidthComboBox(QWidget *parent) noexcept
    : QComboBox{parent}
{
    for (int i = 1; i < 6; ++i)
        addItem(QString::number(2 * i + 1), QVariant::fromValue(2 * i + 1));

    connect(this, &QComboBox::currentIndexChanged, [this]([[maybe_unused]] int index) -> void {
        emit currentWidthChanged(currentWidth());
    });
}

int FilterWidthComboBox::currentWidth() const noexcept
{
    return itemData(currentIndex()).toInt();
}
