#pragma once

#include "approximatetabwidget.h"
#include "gammacorrectiontabwidget.h"

#include <QPointer>
#include <QTabWidget>


class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr) noexcept;
    ~TabWidget() noexcept = default;

    QPointer<ApproximateTabWidget> approximateTabWidget;
    QPointer<GammaCorrectionTabWidget> gammaCorrectionTabWidget;

};
