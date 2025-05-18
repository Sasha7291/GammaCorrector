#include "aboutmenu.h"

#include <QMenuBar>


AboutMenu::AboutMenu(QMenuBar *parent)
    : QMenu{"Help", parent}
{
    addAction(QIcon{":/icons/about.png"}, "About", QKeySequence::HelpContents);
    addAction(QIcon{":/icons/Qt.png"}, "About Qt", QKeySequence::WhatsThis);
}
