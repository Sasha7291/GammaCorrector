#include "doublespinboxdelegate.h"

#include <QDoubleSpinBox>


DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) noexcept
    : QStyledItemDelegate{parent}
{}

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox{parent};

    editor->setFrame(false);
    editor->setDecimals(10);
    editor->setSingleStep(1e-6);
    editor->setRange(-1e10, 1e10);

    return editor;
}
