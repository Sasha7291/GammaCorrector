#pragma once

#include "plot.h"
#include "temperatureplotsettingswidget.h"

#include <QPointer>


class TemperaturePlotWidget;

class TemperaturePlotWidget_Ui
{

public:
    TemperaturePlotWidget_Ui(TemperaturePlotWidget *parent);
    ~TemperaturePlotWidget_Ui() = default;

    void showContextMenu(const QPoint &pos) const;

    QPointer<Plot> plot;
    QPointer<TemperaturePlotSettingsWidget> settingsWindow;

private:
    void showSettingsWindow() const;

    TemperaturePlotWidget *parent_;

};
