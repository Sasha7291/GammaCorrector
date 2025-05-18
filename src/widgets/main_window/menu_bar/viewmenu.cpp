#include "viewmenu.h"

#include <QMenuBar>


ViewMenu::ViewMenu(QMenuBar *parent)
    : QMenu{"View", parent}
{
    addAction(QIcon{":/icons/cascade.png"}, "Cascade arrange", QKeySequence{Qt::CTRL | Qt::Key_W});
    addAction(QIcon{":/icons/tile.png"}, "Tile arrange", QKeySequence{Qt::CTRL | Qt::Key_S});
    addSeparator();
    addAction(QIcon{":/icons/next_sub_window.png"}, "Next window", QKeySequence{Qt::CTRL | Qt::Key_D});
    addAction(QIcon{":/icons/previous_sub_window.png"}, "Previous window", QKeySequence{Qt::CTRL | Qt::Key_A});
    addSeparator();
    addAction(QIcon{":/icons/close_all_windows.png"}, "Close all windows", QKeySequence{Qt::CTRL | Qt::Key_Q});
}
