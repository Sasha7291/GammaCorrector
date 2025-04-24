#pragma once

#include "abstracttabwidget.h"


class GammaCorrectionTabWidget_Ui;

class GammaCorrectionTabWidget : public AbstractTabWidget
{
    Q_OBJECT

public:
    explicit GammaCorrectionTabWidget(QTabWidget *parent = nullptr) noexcept;
    ~GammaCorrectionTabWidget() noexcept override;

    void loadData() override;
    void saveData() override;

private:
    std::unique_ptr<GammaCorrectionTabWidget_Ui> ui;

};
