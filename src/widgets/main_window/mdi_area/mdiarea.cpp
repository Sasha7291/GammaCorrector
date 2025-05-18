#include "mdiarea.h"

#include "subwindowwidget.h"


MdiArea *MdiArea::create(QWidget *parent)
{
    if (instance_ == nullptr)
        instance_ = new MdiArea{parent};
    else
        instance_->setParent(parent);

    return instance_;
}

MdiArea *MdiArea::instance()
{
    return instance_;
}

QMdiSubWindow *MdiArea::openSubWindow(QWidget *widget, const QString &name, bool autoDelete)
{
    return new MdiSubWindow{instance(), widget, name, autoDelete};
}

void MdiArea::activateNextSubWindowWidget()
{
    activateNextSubWindow();
    while (qobject_cast<SubWindowWidget *>(activeSubWindow()->widget()) == nullptr)
        activateNextSubWindow();
}

void MdiArea::activatePreviousSubWindowWidget()
{
    activatePreviousSubWindow();
    while (qobject_cast<SubWindowWidget *>(activeSubWindow()->widget()) == nullptr)
        activatePreviousSubWindow();
}

MdiArea::MdiArea(QWidget *parent)
    : QMdiArea{parent}
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}
