#include "gammacorrectiontabwidget_ui.h"

#include "gammacorrectiontabwidget.h"

#include <QFormLayout>
#include <QGridLayout>


GammaCorrectionTabWidget_Ui::GammaCorrectionTabWidget_Ui(GammaCorrectionTabWidget *parent) noexcept
    : plot{new Plot{parent}}
    , tableWidget{new TableWidget{QStringList() << "Q", parent}}
    , gammaCorrectionDoubleSpinBox{new GammaCorrectionOrderDoubleSpinBox{parent}}
{
    auto mainLayout = new QHBoxLayout{parent};

    auto layout_1 = new QFormLayout;
    layout_1->addRow("Order: ", gammaCorrectionDoubleSpinBox);

    auto layout_2 = new QVBoxLayout;
    layout_2->addLayout(layout_1);
    layout_2->addWidget(tableWidget);

    mainLayout->addWidget(plot, 1);
    mainLayout->addLayout(layout_2);

    parent->setLayout(mainLayout);
}
