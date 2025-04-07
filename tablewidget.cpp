#include "tablewidget.h"

#include "checkboxheaderview.h"


TableWidget::TableWidget(const QStringList &headers, QWidget *parent) noexcept
    : QTableWidget(parent)
{
    setColumnCount(headers.size());
    setSortingEnabled(false);
    verticalHeader()->hide();

    setHorizontalHeader(new CheckBoxHeaderView(Qt::Horizontal, this));
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headers);
    static_cast<CheckBoxHeaderView *>(horizontalHeader())->setColumnCheckable(1);
}
