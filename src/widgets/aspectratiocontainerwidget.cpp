#include "aspectratiocontainerwidget.h"

#include <QHBoxLayout>
#include <QResizeEvent>


AspectRatioContainerWidget::AspectRatioContainerWidget(QWidget *widget, const float aspectRatio, int minimumWidth, QWidget *parent)
    : QWidget{parent}
    , layout_{new QBoxLayout{QBoxLayout::LeftToRight, this}}
    , widget_{widget}
    , aspectRatio_{aspectRatio}
{
    layout_->setContentsMargins(5, 5, 5, 5);
    layout_->addItem(new QSpacerItem{0, 0});
    layout_->addWidget(widget);
    layout_->addItem(new QSpacerItem{0, 0});

    widget->setMinimumSize(minimumWidth, minimumWidth / aspectRatio);
    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void AspectRatioContainerWidget::resizeEvent(QResizeEvent *event)
{
    int widgetStretch = 0;
    int outerStretch = 0;

    if (static_cast<float>(event->size().width()) / event->size().height() > aspectRatio_)
    {
        layout_->setDirection(QBoxLayout::LeftToRight);
        widgetStretch = static_cast<int>(event->size().height() * aspectRatio_);
        outerStretch = static_cast<int>((event->size().width() - widgetStretch) / 2 + 0.5);
    }
    else
    {
        layout_->setDirection(QBoxLayout::TopToBottom);
        widgetStretch = static_cast<int>(event->size().width() / aspectRatio_);
        outerStretch = static_cast<int>((event->size().height() - widgetStretch) / 2 + 0.5);
    }

    layout_->setStretch(0, outerStretch);
    layout_->setStretch(1, widgetStretch);
    layout_->setStretch(2, outerStretch);
}
