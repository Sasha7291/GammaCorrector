#include "splitter.h"


Splitter::Splitter(Orientation orientation, QWidget *parent)
    : QFrame{parent}
{
    setFrameShape(static_cast<Shape>(orientation));
    setFrameShadow(QFrame::Sunken);
}
