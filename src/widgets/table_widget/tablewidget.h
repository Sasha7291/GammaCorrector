#pragma once

#include <QTableWidget>
#include <QPointer>


class CheckBoxHeaderView;

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr) noexcept;
    ~TableWidget() noexcept = default;

    void addRow(int index) noexcept;
    [[nodiscard]] QList<double> column(int index, const QPair<int, int> &rowRange) const noexcept;
    [[nodiscard]] QList<QList<double>> columns(const QPair<int, int> &columnRange, const QPair<int, int> &rowRange) const noexcept;
    void hideRowFrom(int from) noexcept;
    void hideRowTo(int to) noexcept;
    [[nodiscard]] bool isColumnCheckable(int index) const noexcept;
    [[nodiscard]] bool isColumnChecked(int index) const noexcept;
    void multiSort(
        int primaryColumn,
        int secondaryColumn,
        Qt::SortOrder primaryOrder = Qt::AscendingOrder,
        Qt::SortOrder secondaryOrder = Qt::AscendingOrder
    );
    [[nodiscard]] QList<double> row(int index, const QPair<int, int> &columnRange) const noexcept;
    [[nodiscard]] QList<QList<double>> rows(const QPair<int, int> &columnRange, const QPair<int, int> &rowRange) const noexcept;
    void setColumn(int index, const QList<double> &values, const QString &name = QString{}, int fromRow = 0);
    void setColumnCheckable(int index, bool checkable = true);
    void setColumnChecked(int index, bool checked = true);
    void setColumnColor(int index, const QColor &color);
    void setColumns(const QList<QList<double>> &values, const QStringList &headers = QStringList{}, const QList<int> &from = QList<int>{}) noexcept;
    void setRow(int index, const QList<double> &values, int fromColumn = 0);
    void setRowColor(int index, const QColor &color);
    void setRows(const QList<QList<double>> &values, const QList<int> &from = QList<int>{}) noexcept;

signals:
    void columnChecked(int index, bool checked);
    void dataUpdated();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QPointer<CheckBoxHeaderView> header_;
    QList<std::optional<QColor>> colors_;

};
