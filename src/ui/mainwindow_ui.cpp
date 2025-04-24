#include "mainwindow_ui.h"

#include "mainwindow.h"


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : tabWidget{new TabWidget{parent}}
    , menuBar{new MenuBar{parent}}
{
    parent->setMenuBar(menuBar);
    parent->setCentralWidget(tabWidget);
}
