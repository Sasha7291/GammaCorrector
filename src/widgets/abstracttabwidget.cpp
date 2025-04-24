#include "abstracttabwidget.h"

#include <QTabWidget>


AbstractTabWidget::AbstractTabWidget(const QString &name, QTabWidget *parent) noexcept
    : QWidget{parent}
{
    parent->addTab(this, name);
}
