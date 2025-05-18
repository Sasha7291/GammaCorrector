#pragma once

#include <QMenu>


class QMenuBar;

class AboutMenu : public QMenu
{
    Q_OBJECT

public:
    enum Actions
    {
        About,
        AboutQt
    };

    explicit AboutMenu(QMenuBar *parent = nullptr);
    ~AboutMenu() = default;

};
