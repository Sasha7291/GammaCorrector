#include "checkboxheaderview.h"

#include <QPainter>


CheckBoxHeaderView::CheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent) noexcept
    : QHeaderView{orientation, parent}
{
    setSectionsClickable(true);

    connect(this, &QHeaderView::sectionClicked, [this](int index)
    {
        setChecked(index, !isChecked(index));
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
    else if (isCheckable(index))
        checkedMap_.remove(index);
}

void CheckBoxHeaderView::setChecked(int index, bool checked) noexcept
{
    if (isCheckable(index))
    {
        checkedMap_[index] = checked;
        emit sectionChecked(index, checked);
    }
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (isCheckable(logicalIndex))
    {
        QStyleOptionButton styleOption;
        styleOption.rect = rect.adjusted(3, 0, 0, 0);
        styleOption.state = QStyle::State_Enabled | (isChecked(logicalIndex) ? QStyle::State_On : QStyle::State_Off);

        style()->drawControl(QStyle::CE_CheckBox, &styleOption, painter);
    }
}
