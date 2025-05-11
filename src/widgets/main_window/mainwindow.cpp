#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "approximateplotwidget.h"
#include "temperatureplotwidget.h"
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
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->calculateQ();
    });
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *subWindow) -> void {
        if (subWindow != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(subWindow->widget()))
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(true);
                ui->statusBar->setCoefficients(plotWidget->coeffs());
            }
            else if (auto plotWidget = qobject_cast<TemperaturePlotWidget *>(subWindow->widget()))
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(true);
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
        if (!path.isEmpty())
        {
            auto title = path.split("/").back();
            auto data = csv::Reader<double>{csv::Columns}(path.toStdString());

            if (data.size() == 2)
            {
                auto plotWidget = new ApproximatePlotWidget{this};

                MdiArea::openSubWindow(plotWidget, title.first(title.lastIndexOf(".")));
                plotWidget->setData(data);

                connect(plotWidget, &QObject::destroyed, ui->statusBar, &StatusBar::clear);
                connect(plotWidget, &ApproximatePlotWidget::coeffsChanged, ui->statusBar, &StatusBar::setCoefficients);
                connect(plotWidget, &ApproximatePlotWidget::qCalculated, this, [this, plotWidget](const QList<double> &Q) -> void {
                    ui->dockWidget->setQ(plotWidget, Q);
                });
            }
            else if (data.size() == 11)
            {
                QSet gammas(data[0].cbegin(), data[0].cend());

                for (const auto &gamma : gammas)
                {
                    auto plotWidget = new TemperaturePlotWidget{this};

                    MdiArea::openSubWindow(plotWidget, "γ = " + QString::number(gamma) + ": " + title.first(title.lastIndexOf(".")));
                    plotWidget->setData(data);

                    connect(plotWidget, &TemperaturePlotWidget::qCalculated, this, [this, plotWidget](const QList<double> &Q) -> void {
                        ui->dockWidget->setQ(plotWidget, Q);
                    });
                }
            }
            else
            {
                utils::showWarningMessage("Invalid data!");
            }
        }
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void MainWindow::saveData()
{
    try
    {
        csv::Writer<double>{csv::Rows}(utils::getSaveFileName().toStdString(), ui->dockWidget->data());
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}
