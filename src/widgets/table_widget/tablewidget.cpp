#include "tablewidget.h"

#include "checkboxheaderview.h"
#include "doublespinboxdelegate.h"
#include "tablewidgetitem.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>


TableWidget::TableWidget(QWidget *parent) noexcept
    : QTableWidget{parent}
    , header_{new CheckBoxHeaderView{Qt::Horizontal, this}}
{
    setSortingEnabled(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    verticalHeader()->hide();

    setHorizontalHeader(header_);
    header_->setSectionResizeMode(QHeaderView::Stretch);

    setItemDelegate(new DoubleSpinBoxDelegate{this});

    connect(header_, &CheckBoxHeaderView::sectionChecked, this, &TableWidget::columnChecked);
}

void TableWidget::addRow(int row) noexcept
{
    insertRow(row);
    setRow(row, QList<double>(columnCount(), 0.0));
    emit dataUpdated();
}

QList<double> TableWidget::column(int index, const QPair<int, int> &rowRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(rowRange.first >= 0);
    Q_ASSERT(rowRange.first < rowRange.second);
    Q_ASSERT(rowRange.second < rowCount());
#endif

    QList<double> result;
    result.reserve(rowRange.second - rowRange.first);

    for (auto i = rowRange.first; i <= rowRange.second; ++i)
        result << item(i, index)->data(Qt::DisplayRole).toString().toDouble();

    return result;
}

QList<QList<double>> TableWidget::columns(const QPair<int, int> &columnRange, const QPair<int, int> &rowRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(columnRange.first >= 0);
    Q_ASSERT(columnRange.first < columnRange.second);
    Q_ASSERT(columnRange.second < columnCount());
#endif

    QList<QList<double>> result;
    result.reserve(columnRange.second - columnRange.first);

    for (auto i = columnRange.first; i <= columnRange.second; ++i)
        result.push_back(column(i, rowRange));

    return result;
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
    return header_->isCheckable(number);
}

bool TableWidget::isColumnChecked(int number) const noexcept
{
    return header_->isChecked(number);
}

QList<double> TableWidget::row(int index, const QPair<int, int> &columnRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(columnRange.first >= 0);
    Q_ASSERT(columnRange.first < columnRange.second);
    Q_ASSERT(columnRange.second < columnCount());
#endif

    QList<double> result;
    result.reserve(columnRange.second - columnRange.first);

    for (auto i = columnRange.first; i <= columnRange.second; ++i)
        result << item(index, i)->data(Qt::DisplayRole).toString().toDouble();

    return result;
}

QList<QList<double> > TableWidget::rows(const QPair<int, int> &columnRange, const QPair<int, int> &rowRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(rowRange.first >= 0);
    Q_ASSERT(rowRange.first < rowRange.second);
    Q_ASSERT(rowRange.second < rowCount());
#endif

    QList<QList<double>> result;
    result.reserve(rowRange.second - rowRange.first);

    for (auto i = rowRange.first; i <= rowRange.second; ++i)
        result.push_back(row(i, columnRange));

    return result;
}

void TableWidget::setColumn(int index, const QList<double> &values, const QString &name, int fromRow)
{
#ifdef QT_DEBUG
    Q_ASSERT(fromRow >= 0);
#endif

    if (columnCount() <= index)
        setColumnCount(index + 1);
    if (!name.isEmpty())
        setHorizontalHeaderItem(index, new QTableWidgetItem{name});

    for (auto i = 0; i < values.size(); ++i)
        setItem(fromRow + i, index, new TableWidgetItem{values[i]});
}

void TableWidget::setColumnCheckable(int column, bool checkable)
{
    header_->setCheckable(column, checkable);
}

void TableWidget::setColumnChecked(int column, bool checked)
{
    header_->setChecked(column, checked);
}

void TableWidget::setColumns(const QList<QList<double>> &values, const QStringList &headers, const QList<int> &from) noexcept
{
    clear();
    setColumnCount(values.size());
    setRowCount(values[0].size());
    setHorizontalHeaderLabels(headers);
    header_->setSectionResizeMode(QHeaderView::Stretch);
    setMinimumWidth(values.size() * 100);

    for (auto i = 0ll; i < values.size(); ++i)
        setColumn(i, values[i], headers.isEmpty() ? QString{} : headers[i], from.isEmpty() ? 0 : from[i]);
}

void TableWidget::setRow(int index, const QList<double> &values, int fromColumn)
{
#ifdef QT_DEBUG
    Q_ASSERT(fromColumn >= 0);
#endif

    if (rowCount() <= index)
        setRowCount(index + 1);
    setColumnCount(values.size());

    for (auto i = 0; i < values.size(); ++i)
        setItem(index, fromColumn + i, new TableWidgetItem{values[i]});
}

void TableWidget::setRows(const QList<QList<double>> &values, const QList<int> &from) noexcept
{
    clear();
    setRowCount(values.size());
    setColumnCount(values[0].size());
    header_->setSectionResizeMode(QHeaderView::Stretch);
    setMinimumWidth(values.size() * 100);

    for (auto i = 0ll; i < values.size(); ++i)
        setRow(i, values[i], from.isEmpty() ? 0 : from[i]);
}

void TableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse)
    {
        QMenu menu{this};

        menu.addAction("Insert row before", this, [this]() -> void { addRow(currentRow()); });
        menu.addAction("Insert row after", this, [this]() -> void { addRow(currentRow() + 1); });
        menu.addSeparator();
        menu.addAction("Remove row", this, [this]() -> void { removeRow(currentRow()); emit dataUpdated(); });

        menu.exec(mapToGlobal(event->pos()));
    }
}
