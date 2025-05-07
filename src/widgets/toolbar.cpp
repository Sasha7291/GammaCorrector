#include "toolbar.h"


ToolBar::ToolBar(QWidget *parent)
    : QToolBar{parent}
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    setFloatable(false);
    addAction(QIcon{":/icons/Q.png"}, "Calculate Q");
}
