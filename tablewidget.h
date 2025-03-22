#pragma once

#include "utils.h"

#include <QHeaderView>
#include <QTableWidget>


class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(const QStringList &headers, QWidget *parent = nullptr) noexcept;
    ~TableWidget() noexcept = default;

    template<utils::Number T>
    [[nodiscard]] QVector<T> column(const int columnNumber);
    template<utils::Number T>
    void setColumn(const int columnNumber, const QString &label, const QVector<T> &values);
    template<utils::Number T>
    void setValues(const QVector<QVector<T>> &values) noexcept;
    template<utils::Number T>
    [[nodiscard]] QVector<QVector<T>> values() const noexcept;

};

template<utils::Number T>
QVector<T> TableWidget::column(const int columnNumber)
{
    QVector<T> result;
    result.reserve(rowCount());

    for (auto i = 0ull; i < rowCount(); ++i)
        result << get<T>(item(i, columnNumber)->data(Qt::DisplayRole));

    return result;
}

template<utils::Number T>
void TableWidget::setColumn(const int columnNumber, const QString &label, const QVector<T> &values)
{
    if (columnCount() <= columnNumber)
        setColumnCount(columnNumber + 1);
    setHorizontalHeaderItem(columnNumber, new QTableWidgetItem(label));

    for (auto i = 0ll; i < values.size(); ++i)
    {
        auto item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, values[i]);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        setItem(i, columnNumber, item);
    }
}

template<utils::Number T>
void TableWidget::setValues(const QVector<QVector<T>> &values) noexcept
{
    QStringList headers;
    for (auto i = 0; i < values[0].size(); ++i)
        headers << horizontalHeaderItem(i)->text();
    clear();
    setHorizontalHeaderLabels(headers);
    setRowCount(values.size());
    setColumnCount(values[0].size());

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
