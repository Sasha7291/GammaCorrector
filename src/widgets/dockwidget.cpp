#include "dockwidget.h"

DockWidget::DockWidget(QWidget *parent)
    : tableWidget_{new TableWidget{this}}
{
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setFloating(false);
    setWidget(tableWidget_);

    tableWidget_->setColumnCount(10);
    tableWidget_->setHorizontalHeaderLabels({"T, K", "V_offset, dsc", "Q1, dsc", "Q2, dsc", "Q3, dsc", "Q4, dsc", "Q5, dsc", "Q6, dsc", "Q7, dsc", "Q8, dsc"});
    tableWidget_->show();

    setFixedHeight(2 * minimumSizeHint().height());
}

void DockWidget::setQ(const QList<double> &Q)
{
    tableWidget_->setRow(0, Q);
}
