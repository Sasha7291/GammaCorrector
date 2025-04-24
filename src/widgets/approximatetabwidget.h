#pragma once

#include "abstracttabwidget.h"


class ApproximateTabWidget_Ui;

class ApproximateTabWidget : public AbstractTabWidget
{
    Q_OBJECT

public:
    explicit ApproximateTabWidget(QTabWidget *parent = nullptr) noexcept;
    ~ApproximateTabWidget() noexcept override;

    void loadData() override;
    void saveData() override;

private slots:
    void approximate();

private:
    std::unique_ptr<ApproximateTabWidget_Ui> ui;

    int index_;

};
