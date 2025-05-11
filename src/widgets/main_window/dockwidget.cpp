#include "dockwidget.h"

#include "subwindowwidget.h"
#include "tablewidget.h"

#include <QTabWidget>


DockWidget::DockWidget(QWidget *parent)
    : mainTableWidget_{new TableWidget{this}}
    , tabWidget_{new QTabWidget{this}}
{
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setFloating(false);
    setWidget(tabWidget_);
    tabWidget_->show();

    createMainTableWidget();

    setMinimumHeight(2 * minimumSizeHint().height());
}

QList<QList<double> > DockWidget::data() const
{
    return mainTableWidget_->rows({ 0, mainTableWidget_->columnCount() - 1 }, { 0, mainTableWidget_->rowCount() - 1 });
}

void DockWidget::createTableWidget(SubWindowWidget *subWindowWidget)
{
    tableWidgets_[subWindowWidget] = new TableWidget{this};
    tabWidget_->addTab(
        tableWidgets_[subWindowWidget],
        QIcon{"/:icons/main_icon.png"},
        subWindowWidget->windowTitle()
    );
}

void DockWidget::setQ(SubWindowWidget *subWindowWidget, const QList<double> &Q)
{
    if (tableWidgets_.contains(subWindowWidget))
    {
        setQ(tableWidgets_[subWindowWidget], Q);
        tableWidgets_[subWindowWidget]->setHorizontalHeaderLabels({
            "T, K",
            "Q1, dsc",
            "Q2, dsc",
            "Q3, dsc",
            "Q4, dsc",
            "Q5, dsc",
            "Q6, dsc",
            "Q7, dsc",
            "Q8, dsc"
        });
    }
    else
    {
        setQ(mainTableWidget_, Q);
        mainTableWidget_->setHorizontalHeaderLabels({
            "γ",
            "T, K",
            "V_offset, dsc",
            "Q1, dsc",
            "Q2, dsc",
            "Q3, dsc",
            "Q4, dsc",
            "Q5, dsc",
            "Q6, dsc",
            "Q7, dsc",
            "Q8, dsc"
        });
    }
}

void DockWidget::createMainTableWidget()
{
    tabWidget_->addTab(mainTableWidget_, QIcon{":/icons/main_icon.png"}, "Main");
}

void DockWidget::setQ(TableWidget *tableWidget, const QList<double> &Q)
{
    tableWidget->setRow(tableWidget->rowCount(), Q);
    tableWidget->multiSort(0, 1);
    tableWidget->setColumnColor(0, Qt::darkGreen);
    tableWidget->setColumnColor(1, Qt::darkYellow);
}
