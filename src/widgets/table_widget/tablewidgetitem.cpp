#include "tablewidgetitem.h"

TableWidgetItem::TableWidgetItem(double value) noexcept
    : QTableWidgetItem{}
{
    setTextAlignment(Qt::AlignCenter);
    setFlags(flags() | Qt::ItemIsEditable);
    setData(Qt::DisplayRole, QString::number(value, 'g', 10));
    setData(Qt::EditRole, value);
}
