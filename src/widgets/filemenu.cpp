#include "filemenu.h"

#include <QMenuBar>


FileMenu::FileMenu(QMenuBar *parent) noexcept
    : QMenu{"File", parent}
{
    addAction(QIcon{":/icons/open.png"}, "Open", QKeySequence::Open);
    addAction(QIcon{":/icons/save.png"}, "Save as...", QKeySequence::Save);
    addSeparator();
    addAction(QIcon{":/icons/exit.png"}, "Exit", QKeySequence::Close);
}
