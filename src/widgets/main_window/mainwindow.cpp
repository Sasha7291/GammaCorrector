#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "aboutdialog.h"
#include "approximateplotwidget.h"
#include "temperatureplotwidget.h"
#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"

#include <QApplication>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow{parent}
    , ui{std::make_unique<MainWindow_Ui>(this)}
{
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Open], &QAction::triggered, this, &MainWindow::loadData);
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Save], &QAction::triggered, this, &MainWindow::saveData);
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Exit], &QAction::triggered, qApp, &QApplication::exit);
    connect(ui->menuBar->viewMenu->actions()[ViewMenu::CascadeArrange], &QAction::triggered, MdiArea::instance(), &QMdiArea::cascadeSubWindows);
    connect(ui->menuBar->viewMenu->actions()[ViewMenu::TileArrange], &QAction::triggered, MdiArea::instance(), &QMdiArea::tileSubWindows);
    connect(ui->menuBar->viewMenu->actions()[ViewMenu::NextSubWindow], &QAction::triggered, MdiArea::instance(), &MdiArea::activateNextSubWindowWidget);
    connect(ui->menuBar->viewMenu->actions()[ViewMenu::PreviousSubWindow], &QAction::triggered, MdiArea::instance(), &MdiArea::activatePreviousSubWindowWidget);
    connect(ui->menuBar->viewMenu->actions()[ViewMenu::CloseAllSubWindows], &QAction::triggered, MdiArea::instance(), &QMdiArea::closeAllSubWindows);
    connect(ui->menuBar->aboutMenu->actions()[AboutMenu::About], &QAction::triggered, this, [this]() -> void {
        (new AboutDialog{this})->show();
    });
    connect(ui->menuBar->aboutMenu->actions()[AboutMenu::AboutQt], &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->toolBar->actions()[ToolBar::CalculateQ], &QAction::triggered, this, [this]() -> void {
        if (MdiArea::instance()->activeSubWindow() != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->calculateQ();
            else if (auto plotWidget = qobject_cast<TemperaturePlotWidget *>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->calculateQ();
        }
    });
    connect(ui->toolBar->actions()[ToolBar::FindOffset], &QAction::triggered, this, [this]() -> void {
        if (MdiArea::instance()->activeSubWindow() != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->findOffset();
        }
    });
    connect(ui->toolBar->actions()[ToolBar::SubstractLine], &QAction::triggered, this, [this]() -> void {
        if (MdiArea::instance()->activeSubWindow() != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(MdiArea::instance()->activeSubWindow()->widget()))
                plotWidget->substractLine();
        }
    });
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *subWindow) -> void {
        if (subWindow != nullptr)
        {
            if (auto plotWidget = qobject_cast<ApproximatePlotWidget *>(subWindow->widget()))
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(true);
                ui->toolBar->actions()[ToolBar::FindOffset]->setEnabled(true);
                ui->toolBar->actions()[ToolBar::SubstractLine]->setEnabled(true);
                ui->statusBar->setCoefficients(plotWidget->coeffs());
            }
            else if (auto plotWidget = qobject_cast<TemperaturePlotWidget *>(subWindow->widget()))
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(true);
                ui->toolBar->actions()[ToolBar::FindOffset]->setEnabled(false);
                ui->toolBar->actions()[ToolBar::SubstractLine]->setEnabled(false);
            }
            else
            {
                ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(false);
                ui->toolBar->actions()[ToolBar::FindOffset]->setEnabled(false);
                ui->toolBar->actions()[ToolBar::SubstractLine]->setEnabled(false);
            }
        }
        else
        {
            ui->toolBar->actions()[ToolBar::CalculateQ]->setEnabled(false);
            ui->toolBar->actions()[ToolBar::FindOffset]->setEnabled(false);
            ui->toolBar->actions()[ToolBar::SubstractLine]->setEnabled(false);
        }
    });
}

MainWindow::~MainWindow() noexcept {}

void MainWindow::loadData()
{
    try
    {
        auto paths = utils::getOpenFileNames();
        for (auto &path : paths)
            if (!path.isEmpty())
            {
                auto title = path.split("/").back();
                auto data = csv::Reader<double>{csv::Columns}(QDir{path}.filesystemAbsolutePath());

                if (data.size() == 2)
                {
                    auto plotWidget = new ApproximatePlotWidget{this};

                    MdiArea::openSubWindow(plotWidget, title.first(title.lastIndexOf(".")));
                    plotWidget->setData(data);
                    ui->statusBar->setCoefficients(plotWidget->coeffs());

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
                        QList<QList<double>> tempData(data.size() - 1, QList<double>{});

                        for (int i = 0; i < data[0].size(); i++)
                            if (data[0][i] == gamma)
                                for (int j = 1; j < data.size(); ++j)
                                    tempData[j - 1] << data[j][i];

                        MdiArea::openSubWindow(plotWidget, "γ = " + QString::number(gamma) + ": " + title.first(title.lastIndexOf(".")));
                        plotWidget->setData(tempData);
                        ui->dockWidget->createTableWidget(plotWidget);

                        connect(plotWidget, &QObject::destroyed, this, [this, plotWidget]() -> void {
                            ui->dockWidget->removeTableWidget(plotWidget);
                        });
                        connect(plotWidget, &TemperaturePlotWidget::qCalculated, this, [this, plotWidget](const QList<double> &Q) -> void {
                            ui->dockWidget->setQ(plotWidget, Q);
                        });
                    }
                }
                else
                {
                    qWarning() << "Invalid data!";
                }
            }
    }
    catch (const csv::Exception &exception)
    {
        qWarning() << exception.what();
    }
}

void MainWindow::saveData()
{
    try
    {
        csv::Writer<double>{csv::Rows}(
            QDir{utils::getSaveFileName()}.filesystemAbsolutePath(),
            ui->dockWidget->data()
        );
    }
    catch (const csv::Exception &exception)
    {
        qWarning() << exception.what();
    }
}
