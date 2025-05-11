#pragma once

#include "plot.h"
#include "approximateplotsettingswidget.h"
#include "tablewidget.h"

#include <QPointer>


class ApproximatePlotWidget;

class ApproximatePlotWidget_Ui
{

public:
    explicit ApproximatePlotWidget_Ui(ApproximatePlotWidget *parent);
    ~ApproximatePlotWidget_Ui() = default;

    void showContextMenu(const QPoint &pos) const;

    QPointer<Plot> plot;
    QPointer<TableWidget> originalData;
    QPointer<ApproximatePlotSettingsWidget> settingsWindow;

private:
    void showSettingsWindow() const;

    ApproximatePlotWidget *parent_;

};
