#include "menubar.h"

MenuBar::MenuBar(QWidget *parent) noexcept
    : QMenuBar{parent}
    , fileMenu{new FileMenu{this}}
{
    addMenu(fileMenu);
}
