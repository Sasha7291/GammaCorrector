#pragma once

#include <QToolBar>


class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    enum Actions
    {
        CalculateQ
    };

    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar() = default;

};
