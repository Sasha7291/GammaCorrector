#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) noexcept
    : QTabWidget{parent}
    , approximateTabWidget{new ApproximateTabWidget{this}}
    , gammaCorrectionTabWidget{new GammaCorrectionTabWidget{this}}
{}
