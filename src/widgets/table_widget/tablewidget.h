#pragma once

#include "utils.h"

#include <QHeaderView>
#include <QTableWidget>


class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(const QStringList &headers = QStringList{}, QWidget *parent = nullptr) noexcept;
    ~TableWidget() noexcept = default;

    template<utils::Number T>
    [[nodiscard]] QVector<T> column(int number);
    void hideRowFrom(int from) noexcept;
    void hideRowTo(int to) noexcept;
    [[nodiscard]] bool isColumnCheckable(int number) const noexcept;
    [[nodiscard]] bool isColumnChecked(int number) const noexcept;
    template<utils::Number T>
    void setColumnValues(
        int column,
        const QVector<T> &values,
        const QString &label = QString{},
        int from = 0
    );
    void setColumnCheckable(int column, bool checkable = true);
    void setColumnChecked(int column, bool checked = true);
    void setRowEnabled(int row, bool checked = true) noexcept;
    void setRowEnabledFrom(int from, bool checked = true) noexcept;
    void setRowEnabledTo(int to, bool checked = true) noexcept;
    template<utils::Number T>
    void setValues(const QVector<QVector<T>> &values) noexcept;
    template<utils::Number T>
    [[nodiscard]] QVector<QVector<T>> values() const noexcept;

signals:
    void columnChecked(int index, bool checked);

};


template<utils::Number T>
QVector<T> TableWidget::column(int number)
{
    QVector<T> result;
    result.reserve(rowCount());

    for (auto i = 0ull; i < rowCount(); ++i)
        result << get<T>(item(i, number)->data(Qt::DisplayRole));

    return result;
}

template<utils::Number T>
void TableWidget::setColumnValues(
    int column,
    const QVector<T> &values,
    const QString &label,
    int from
)
{
    if (columnCount() <= column)
        setColumnCount(column + 1);
    if (!label.isEmpty())
        setHorizontalHeaderItem(column, new QTableWidgetItem(label));

    for (auto i = 0; i < values.size(); ++i)
    {
        auto item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, values[i]);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        setItem(from + i, column, item);
    }
}

template<utils::Number T>
void TableWidget::setValues(const QVector<QVector<T>> &values) noexcept
{
    QStringList headers;
    for (auto i = 0; i < values[0].size(); ++i)
        headers << horizontalHeaderItem(i)->text();
    clear();
    setColumnCount(values[0].size());
    setRowCount(values.size());
    setHorizontalHeaderLabels(headers);

    for (auto i = 0ll; i < values.size(); ++i)
        for (auto j = 0ll; j < values[i].size(); ++j)
        {
            auto item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole, values[i][j]);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);

            setItem(i, j, item);
        }
}

template<utils::Number T>
QVector<QVector<T>> TableWidget::values() const noexcept
{
    QVector<QVector<T>> result;
    result.reserve(rowCount());

    for (auto i = 0; i < rowCount(); ++i)
    {
        QVector<T> line;
        line.reserve(columnCount());

        for (auto j = 0; j < columnCount(); ++j)
            line << get<T>(item(i, j)->data(Qt::DisplayRole));

        result << line;
    }

    return result;
}
