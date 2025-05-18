#pragma once

#include "aboutmenu.h"
#include "filemenu.h"
#include "viewmenu.h"

#include <QMenuBar>
#include <QPointer>


class MenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr) noexcept;
    ~MenuBar() noexcept = default;

    QPointer<AboutMenu> aboutMenu;
    QPointer<FileMenu> fileMenu;
    QPointer<ViewMenu> viewMenu;

};
