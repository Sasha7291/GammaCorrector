#include "tablewidget.h"


TableWidget::TableWidget(const QStringList &headers, QWidget *parent) noexcept
    : QTableWidget(parent)
{
    setColumnCount(headers.size());
    setHorizontalHeaderLabels(headers);
    setSortingEnabled(false);
    verticalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
