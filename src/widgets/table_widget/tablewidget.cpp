#include "tablewidget.h"


TableWidget::TableWidget(const QStringList &headers, QWidget *parent) noexcept
    : QTableWidget(parent)
{
    setColumnCount(headers.size());
    setSortingEnabled(false);
    verticalHeader()->hide();

    setHorizontalHeader(new CheckBoxHeaderView(Qt::Horizontal, this));
    auto header = static_cast<CheckBoxHeaderView *>(horizontalHeader());
    header->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderLabels(headers);
    header->setColumnCheckable(1);
    header->setColumnChecked(1);

    connect(header, &CheckBoxHeaderView::columnSectionClicked, this, &TableWidget::columnChecked);
}
