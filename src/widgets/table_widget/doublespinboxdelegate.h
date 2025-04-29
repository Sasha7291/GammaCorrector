#pragma once

#include <QStyledItemDelegate>


class DoubleSpinBoxDelegate : public QStyledItemDelegate
{

public:
    explicit DoubleSpinBoxDelegate(QObject *parent = nullptr) noexcept;
    ~DoubleSpinBoxDelegate() noexcept = default;

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
