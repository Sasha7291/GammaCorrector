#include "tablewidget.h"


TableWidget::TableWidget(const QStringList &headers, QWidget *parent) noexcept
    : QTableWidget(parent)
{
    setColumnCount(headers.size());
    setSortingEnabled(false);
    verticalHeader()->hide();

    auto header = new CheckBoxHeaderView(Qt::Horizontal, this);
    setHorizontalHeader(header);
    setHorizontalHeaderLabels(headers);
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setCheckable(I);
    header->setChecked(I);

    connect(header, &CheckBoxHeaderView::sectionChecked, this, &TableWidget::columnChecked);
}

void TableWidget::hideRowFrom(int from) noexcept
{
    for (auto i = 0; i < from; ++i)
        showRow(i);
    for (auto i = from; i < rowCount(); ++i)
        hideRow(i);
}

void TableWidget::hideRowTo(int to) noexcept
{
    for (auto i = 0; i < to; ++i)
        hideRow(i);
    for (auto i = to; i < rowCount(); ++i)
        showRow(i);
}

bool TableWidget::isColumnCheckable(int number) const noexcept
{
    return static_cast<CheckBoxHeaderView *>(horizontalHeader())->isCheckable(number);
}

bool TableWidget::isColumnChecked(int number) const noexcept
{
    return static_cast<CheckBoxHeaderView *>(horizontalHeader())->isChecked(number);
}

void TableWidget::setRowEnabled(int row, bool checked) noexcept
{
    for (auto i = 0ll; i < columnCount(); ++i)
        item(row, i)->setFlags(checked ? item(row, i)->flags() | Qt::ItemIsEnabled : item(row, i)->flags() & ~Qt::ItemIsEnabled);
}

void TableWidget::setRowEnabledFrom(int from, bool checked) noexcept
{
    for (auto i = 0; i < from; ++i)
        setRowEnabled(i, !checked);
    for (auto i = from; i < rowCount(); ++i)
        setRowEnabled(i, checked);
}

void TableWidget::setRowEnabledTo(int to, bool checked) noexcept
{
    for (auto i = 0; i < to; ++i)
        setRowEnabled(i, checked);
    for (auto i = to; i < rowCount(); ++i)
        setRowEnabled(i, !checked);
}
