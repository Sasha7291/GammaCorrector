#include "checkboxheaderview.h"

#include <QPainter>


CheckBoxHeaderView::CheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent) noexcept
    : QHeaderView{orientation, parent}
{
    setSectionsClickable(true);

    connect(this, &QHeaderView::sectionClicked, [this](int logicalIndex)
    {
        if (columnCheckedMap_.contains(logicalIndex))
        {
            columnCheckedMap_[logicalIndex] = !columnCheckedMap_[logicalIndex];
            emit columnSectionClicked(logicalIndex, columnCheckedMap_[logicalIndex]);
        }
    });
}

bool CheckBoxHeaderView::columnChecked(int column) const noexcept
{
    return columnCheckedMap_.value(column, false);
}

void CheckBoxHeaderView::setColumnCheckable(int column, bool checkable) noexcept
{
    if (checkable)
        columnCheckedMap_[column] = false;
    else if (columnCheckedMap_.contains(column))
        columnCheckedMap_.remove(column);
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (columnCheckedMap_.contains(logicalIndex))
    {
        QStyleOptionButton styleOption;
        styleOption.rect = rect.adjusted(3, 0, 0, 0);
        styleOption.state = QStyle::State_Enabled | (columnCheckedMap_[logicalIndex] ? QStyle::State_On : QStyle::State_Off);

        style()->drawControl(QStyle::CE_CheckBox, &styleOption, painter);
    }
}
