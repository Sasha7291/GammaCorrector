#pragma once

#include <QFrame>


class Splitter : public QFrame
{
    Q_OBJECT

public:
    enum Orientation
    {
        Horizontal = HLine,
        Vertical = VLine
    };

    explicit Splitter(Orientation orientation, QWidget *parent = nullptr);
    ~Splitter() = default;

};
