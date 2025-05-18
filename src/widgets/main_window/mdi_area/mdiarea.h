#pragma once

#include "mdisubwindow.h"

#include <QMdiArea>


class MdiArea : public QMdiArea
{
    Q_OBJECT

public:
    static MdiArea *create(QWidget *parent = nullptr);
    static MdiArea *instance();
    static QMdiSubWindow *openSubWindow(QWidget *widget = new QWidget, const QString &name = QString{}, bool autoDelete = true);

public slots:
    void activateNextSubWindowWidget();
    void activatePreviousSubWindowWidget();

private:
    explicit MdiArea(QWidget *parent = nullptr);
    ~MdiArea() = default;

    static inline MdiArea *instance_ = nullptr;

};
