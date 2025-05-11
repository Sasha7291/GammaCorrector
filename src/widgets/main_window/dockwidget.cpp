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
        QIcon{":/icons/main_icon.png"},
        subWindowWidget->windowTitle()
    );
}

void DockWidget::removeTableWidget(SubWindowWidget *subWindowWidget)
{
    for (int i = 0; i < tabWidget_->count(); ++i)
        if (tabWidget_->widget(i) == tableWidgets_[subWindowWidget])
        {
            tabWidget_->removeTab(i);
            tableWidgets_.remove(subWindowWidget);
            break;
        }
}

void DockWidget::setQ(SubWindowWidget *subWindowWidget, const QList<double> &Q)
{
    if (tableWidgets_.contains(subWindowWidget))
    {
        tableWidgets_[subWindowWidget]->setRow(tableWidgets_[subWindowWidget]->rowCount(), Q);
        tableWidgets_[subWindowWidget]->sortByColumn(0, Qt::AscendingOrder);
        tableWidgets_[subWindowWidget]->setColumnColor(0, Qt::darkGreen);
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
        mainTableWidget_->setRow(mainTableWidget_->rowCount(), Q);
        mainTableWidget_->multiSort(0, 1);
        mainTableWidget_->setColumnColor(0, Qt::darkGreen);
        mainTableWidget_->setColumnColor(1, Qt::darkYellow);
        mainTableWidget_->setHorizontalHeaderLabels({
            "γ",
            "T, K",
            "V_max, dsc",
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
