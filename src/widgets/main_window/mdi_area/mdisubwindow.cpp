#include "mdisubwindow.h"

#include <QCloseEvent>
#include <QMdiArea>


MdiSubWindow::MdiSubWindow(QMdiArea *parent, QWidget *widget, const QString &name, bool autoDelete)
    : QMdiSubWindow{parent}
    , autoDelete_{autoDelete}
    , previousParent_{widget->parentWidget()}
{   
    widget->setWindowTitle(name);
    setWindowTitle(name);

    setWidget(widget);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setOption(QMdiSubWindow::RubberBandMove);
    setOption(QMdiSubWindow::RubberBandResize);
    setWindowIcon(QIcon{":/icons/main_icon.png"});
    setWindowFlags(widget->windowFlags());

    widget->show();
    show();
    parent->setActiveSubWindow(this);
}

void MdiSubWindow::closeEvent(QCloseEvent *)
{
    emit mdiWindowDeleted(this, widget());

    if (!autoDelete_)
    {
        widget()->hide();
        widget()->setParent(previousParent_);
        setWidget(nullptr);
    }
}
