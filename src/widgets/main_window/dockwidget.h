#pragma once

#include "tablewidget.h"

#include <QDockWidget>
#include <QPointer>


class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidget(QWidget *parent = nullptr);
    ~DockWidget() = default;

    void setQ(const QList<double> &Q);

private:
    QPointer<TableWidget> tableWidget_;

};
