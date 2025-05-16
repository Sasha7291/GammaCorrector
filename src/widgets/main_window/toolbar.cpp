#include "toolbar.h"


ToolBar::ToolBar(QWidget *parent)
    : QToolBar{parent}
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    setFloatable(false);
    addAction(QIcon{":/icons/Q.png"}, "Calculate Q", QKeySequence{Qt::CTRL | Qt::Key_Q});
    addAction(QIcon{":/icons/find_offset.png"}, "Find offset", QKeySequence{Qt::CTRL | Qt::Key_E});
    addAction(QIcon{":/icons/substract_line.png"}, "Substract line", QKeySequence{Qt::CTRL | Qt::Key_L});

    for (auto &action : actions())
        action->setEnabled(false);
}
