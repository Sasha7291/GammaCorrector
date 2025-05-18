#pragma once

#include <QMenu>


class QMenuBar;

class FileMenu : public QMenu
{
    Q_OBJECT

public:
    enum Actions : int
    {
        Open,
        Save,
        Separator_1,
        Exit
    };

    explicit FileMenu(QMenuBar *parent = nullptr) noexcept;
    ~FileMenu() noexcept = default;

};
