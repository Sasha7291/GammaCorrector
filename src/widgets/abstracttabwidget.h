#pragma once

#include <QWidget>


class QTabWidget;

class AbstractTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractTabWidget(const QString &name, QTabWidget *parent = nullptr) noexcept;
    virtual ~AbstractTabWidget() noexcept = default;

    virtual void loadData() = 0;
    virtual void saveData() = 0;

};
