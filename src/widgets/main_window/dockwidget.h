#pragma once

#include <QDockWidget>
#include <QPointer>


class SubWindowWidget;
class TableWidget;
class QTabWidget;

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidget(QWidget *parent = nullptr);
    ~DockWidget() = default;

    [[nodiscard]] QList<QList<double>> data() const;

public slots:
    void createTableWidget(SubWindowWidget *subWindowWidget);
    void removeTableWidget(SubWindowWidget *subWindowWidget);
    void setQ(SubWindowWidget *subWindowWidget, const QList<double> &Q);

private:
    void createMainTableWidget();

    QHash<SubWindowWidget *, QPointer<TableWidget>> tableWidgets_;
    QPointer<TableWidget> mainTableWidget_;
    QPointer<QTabWidget> tabWidget_;

};
