#include "mainwindow_ui.h"

#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : mdiArea{MdiArea::create(parent)}
    , menuBar{new MenuBar{parent}}
    , toolBar{new ToolBar{parent}}
    , statusBar{new StatusBar{parent}}
    , dockWidget{new DockWidget{parent}}
{
    parent->setMenuBar(menuBar);
    parent->addToolBar(toolBar);
    parent->setCentralWidget(mdiArea);
    parent->setStatusBar(statusBar);
    parent->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
}
