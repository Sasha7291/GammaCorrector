#pragma once

#include "gammacorrectionorderdoublespinbox.h"
#include "plot.h"
#include "tablewidget.h"

#include <QPointer>


class GammaCorrectionTabWidget;

class GammaCorrectionTabWidget_Ui
{

public:
    explicit GammaCorrectionTabWidget_Ui(GammaCorrectionTabWidget *parent) noexcept;
    ~GammaCorrectionTabWidget_Ui() noexcept = default;

    GammaCorrectionTabWidget_Ui(const GammaCorrectionTabWidget_Ui &) = delete;
    GammaCorrectionTabWidget_Ui(GammaCorrectionTabWidget_Ui &&) = delete;
    GammaCorrectionTabWidget_Ui &operator=(const GammaCorrectionTabWidget_Ui &) = delete;
    GammaCorrectionTabWidget_Ui &operator=(GammaCorrectionTabWidget_Ui &&) = delete;

    QPointer<Plot> plot;
    QPointer<TableWidget> tableWidget;
    QPointer<GammaCorrectionOrderDoubleSpinBox> gammaCorrectionDoubleSpinBox;

};
