#include "subwindowwidget.h"

#include <QMdiSubWindow>


SubWindowWidget::SubWindowWidget(QWidget *parent)
    : QWidget{parent}
    , manualResize_{false}
{}

void SubWindowWidget::setSize(const QSize &size)
{
    setSize(size.width(), size.height());
}

void SubWindowWidget::setSize(int w, int h)
{
    manualResize_ = true;
    resize(w, h);
    manualResize_ = false;
}

void SubWindowWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    auto subWindow = qobject_cast<QMdiSubWindow *>(parent());
    if ((manualResize_) && (subWindow != nullptr) && !(subWindow->windowState() & Qt::WindowMaximized))
        subWindow->adjustSize();
}

QSize SubWindowWidget::sizeHint() const
{
    return size();
}
