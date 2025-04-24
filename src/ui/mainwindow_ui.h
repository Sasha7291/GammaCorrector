#pragma once

#include "menubar.h"
#include "tabwidget.h"


class MainWindow;

class MainWindow_Ui
{

public:
    explicit MainWindow_Ui(MainWindow *parent) noexcept;
    ~MainWindow_Ui() noexcept = default;

    QPointer<TabWidget> tabWidget;
    QPointer<MenuBar> menuBar;

};
