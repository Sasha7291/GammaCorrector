#include "mainwindow.h"

#include "mainwindow_ui.h"

#include <QApplication>


MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow{parent}
    , ui{std::make_unique<MainWindow_Ui>(this)}
{
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Open], &QAction::triggered, this, [this]() -> void {
        static_cast<AbstractTabWidget *>(ui->tabWidget->currentWidget())->loadData();
    });
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Save], &QAction::triggered, this, [this]() -> void {
        static_cast<AbstractTabWidget *>(ui->tabWidget->currentWidget())->saveData();
    });
    connect(ui->menuBar->fileMenu->actions()[FileMenu::Exit], &QAction::triggered, qApp, &QApplication::exit);
}

MainWindow::~MainWindow() noexcept {}
