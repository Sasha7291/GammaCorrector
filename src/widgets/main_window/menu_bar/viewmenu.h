#pragma once

#include <QMenu>


class QMenuBar;

class ViewMenu : public QMenu
{
    Q_OBJECT

public:
    enum Actions
    {
        CascadeArrange,
        TileArrange,
        Separator_1,
        NextSubWindow,
        PreviousSubWindow,
        Separator_2,
        CloseAllSubWindows
    };

    explicit ViewMenu(QMenuBar *parent = nullptr);
    ~ViewMenu() = default;

};
