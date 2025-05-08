#pragma once

#include <QMdiSubWindow>


class MdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit MdiSubWindow(QMdiArea *parent, QWidget *widget = new QWidget, const QString &name = QString{}, bool autoDelete = true);
    ~MdiSubWindow() = default;

    MdiSubWindow(const MdiSubWindow &) = delete;
    MdiSubWindow(MdiSubWindow &&) = delete;
    MdiSubWindow &operator=(const MdiSubWindow &) = delete;
    MdiSubWindow &operator=(MdiSubWindow &&) = delete;

signals:
    void mdiWindowDeleted(MdiSubWindow *mdiSubWindow, QWidget *widget);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    QWidget *previousParent_;
    bool autoDelete_;

};
