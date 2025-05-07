#pragma once

#include "dockwidget.h"
#include "mdiarea.h"
#include "menubar.h"
#include "statusbar.h"
#include "toolbar.h"


class MainWindow;

class MainWindow_Ui
{

public:
    explicit MainWindow_Ui(MainWindow *parent) noexcept;
    ~MainWindow_Ui() noexcept = default;

    QPointer<MdiArea> mdiArea;
    QPointer<MenuBar> menuBar;
    QPointer<ToolBar> toolBar;
    QPointer<StatusBar> statusBar;
    QPointer<DockWidget> dockWidget;

};
