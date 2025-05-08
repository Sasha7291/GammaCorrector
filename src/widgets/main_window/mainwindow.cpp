#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "approximateplotwidget.h"
#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"

#include <QApplication>


MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow{parent}
    , ui{std::make_unique<MainWindow_Ui>(this)}
{
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Open], &QAction::triggered, this, &MainWindow::loadData);
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Save], &QAction::triggered, this, &MainWindow::saveData);
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Exit], &QAction::triggered, qApp, &QApplication::exit);
    connect(ui->toolBar->actions()[ToolBar::CalculateQ], &QAction::triggered, this, [this]() -> void {
        if (MdiArea::instance()->activeSubWindow() != nullptr)
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget*>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->calculateQ();
    });
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *subWindow) -> void {
        if (subWindow != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget*>(subWindow->widget()))
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(true);
                ui->statusBar->setCoefficients(plotWidget->coeffs());

                disconnect(plotWidget, &QObject::destroyed, ui->statusBar, nullptr);
                disconnect(plotWidget, &ApproximatePlotWidget::coeffsChanged, ui->statusBar, nullptr);
                disconnect(plotWidget, &ApproximatePlotWidget::qCalculated, ui->dockWidget, nullptr);
                connect(plotWidget, &QObject::destroyed, ui->statusBar, &StatusBar::clear);
                connect(plotWidget, &ApproximatePlotWidget::coeffsChanged, ui->statusBar, &StatusBar::setCoefficients);
                connect(plotWidget, &ApproximatePlotWidget::qCalculated, ui->dockWidget, &DockWidget::setQ);
            }
            else
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(false);
            }
        }
    });
}

MainWindow::~MainWindow() noexcept {}

void MainWindow::loadData()
{
    try
    {
        auto path = utils::getOpenFileName();
        auto title = path.split("/").back();
        auto plotWidget = new ApproximatePlotWidget{this};

        if (!path.isEmpty())
            MdiArea::openSubWindow(plotWidget, title.first(title.lastIndexOf(".")));

        plotWidget->setData(csv::Reader<double>{csv::Columns}(path.toStdString()));
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void MainWindow::saveData()
{

}
