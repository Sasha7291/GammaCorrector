#pragma once

#include "filemenu.h"

#include <QMenuBar>
#include <QPointer>


class MenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr) noexcept;
    ~MenuBar() noexcept = default;

    QPointer<FileMenu> fileMenu;

};
