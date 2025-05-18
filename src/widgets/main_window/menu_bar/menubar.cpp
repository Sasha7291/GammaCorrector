#include "menubar.h"


MenuBar::MenuBar(QWidget *parent) noexcept
    : QMenuBar{parent}
    , aboutMenu{new AboutMenu{this}}
    , fileMenu{new FileMenu{this}}
    , viewMenu{new ViewMenu{this}}
{
    addMenu(fileMenu);
    addMenu(viewMenu);
    addMenu(aboutMenu);
}
