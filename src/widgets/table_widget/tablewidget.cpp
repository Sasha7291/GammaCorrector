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
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::MultiSelection);
    verticalHeader()->hide();

    setHorizontalHeader(header_);
    header_->setSectionResizeMode(QHeaderView::Stretch);

    setItemDelegate(new DoubleSpinBoxDelegate{this});

    connect(header_, &CheckBoxHeaderView::sectionChecked, this, &TableWidget::columnChecked);
}

void TableWidget::addRow(int index) noexcept
{
    insertRow(index);
    setRow(index, QList<double>(columnCount(), 0.0));
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

bool TableWidget::isColumnCheckable(int index) const noexcept
{
    return header_->isCheckable(index);
}

bool TableWidget::isColumnChecked(int index) const noexcept
{
    return header_->isChecked(index);
}

void TableWidget::multiSort(
    int primaryColumn,
    int secondaryColumn,
    Qt::SortOrder primaryOrder,
    Qt::SortOrder secondaryOrder
)
{
    auto data = rows({ 0, columnCount() }, { 0, rowCount() });
    auto compare = [primaryColumn, secondaryColumn, primaryOrder, secondaryOrder](const QVector<double> &a, const QVector<double> &b)
    {
        if (a[primaryColumn] != b[primaryColumn])
            return (primaryOrder == Qt::AscendingOrder)
                ? (a[primaryColumn] < b[primaryColumn])
                : (a[primaryColumn] > b[primaryColumn]);

        return secondaryOrder == Qt::AscendingOrder
            ? (a[secondaryColumn] < b[secondaryColumn])
            : (a[secondaryColumn] > b[secondaryColumn]);
    };

    std::sort(data.begin(), data.end(), compare);
    setRows(data);
}

QList<double> TableWidget::row(int index, const QPair<int, int> &columnRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(columnRange.first >= 0);
    Q_ASSERT(columnRange.first < columnRange.second);
    Q_ASSERT(columnRange.second <= columnCount());
#endif

    QList<double> result;
    result.reserve(columnRange.second - columnRange.first);

    for (auto i = columnRange.first; i < columnRange.second; ++i)
        result << item(index, i)->data(Qt::DisplayRole).toString().toDouble();

    return result;
}

QList<QList<double>> TableWidget::rows(const QPair<int, int> &columnRange, const QPair<int, int> &rowRange) const noexcept
{
#ifdef QT_DEBUG
    Q_ASSERT(rowRange.first >= 0);
    Q_ASSERT(rowRange.first < rowRange.second);
    Q_ASSERT(rowRange.second <= rowCount());
#endif

    QList<QList<double>> result;
    result.reserve(rowRange.second - rowRange.first);

    for (auto i = rowRange.first; i < rowRange.second; ++i)
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

void TableWidget::setColumnCheckable(int index, bool checkable)
{
    header_->setCheckable(index, checkable);
}

void TableWidget::setColumnChecked(int index, bool checked)
{
    header_->setChecked(index, checked);
}

void TableWidget::setColumnColor(int index, const QColor &color)
{
    QColor tempColor = color;
    tempColor.setAlphaF(0.5);

    for (int i = 0; i < rowCount(); ++i)
        item(i, index)->setBackground(QBrush{tempColor, Qt::BrushStyle::SolidPattern});
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

void TableWidget::setRowColor(int index, const QColor &color)
{
    QColor tempColor = color;
    tempColor.setAlphaF(0.5);

    for (int i = 0; i < columnCount(); ++i)
        item(index, i)->setBackground(QBrush{tempColor, Qt::SolidPattern});
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
