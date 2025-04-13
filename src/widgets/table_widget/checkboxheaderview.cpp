#include "checkboxheaderview.h"

#include <QPainter>


CheckBoxHeaderView::CheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent) noexcept
    : QHeaderView{orientation, parent}
{
    setSectionsClickable(true);

    connect(this, &QHeaderView::sectionClicked, [this](int logicalIndex)
    {
        if (checkedMap_.contains(logicalIndex))
        {
            checkedMap_[logicalIndex] = !checkedMap_[logicalIndex];
            emit sectionChecked(logicalIndex, checkedMap_[logicalIndex]);
        }
    });
}

bool CheckBoxHeaderView::isCheckable(int index) const noexcept
{
    return checkedMap_.contains(index);
}

bool CheckBoxHeaderView::isChecked(int index) const noexcept
{
    return checkedMap_.value(index, false);
}

void CheckBoxHeaderView::setCheckable(int index, bool checkable) noexcept
{
    if (checkable)
        checkedMap_[index] = false;
    else if (checkedMap_.contains(index))
        checkedMap_.remove(index);
}

void CheckBoxHeaderView::setChecked(int index, bool checked) noexcept
{
    if (checkedMap_.contains(index))
        checkedMap_[index] = checked;
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (checkedMap_.contains(logicalIndex))
    {
        QStyleOptionButton styleOption;
        styleOption.rect = rect.adjusted(3, 0, 0, 0);
        styleOption.state = QStyle::State_Enabled | (checkedMap_[logicalIndex] ? QStyle::State_On : QStyle::State_Off);

        style()->drawControl(QStyle::CE_CheckBox, &styleOption, painter);
    }
}
