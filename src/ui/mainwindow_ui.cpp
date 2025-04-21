#include "mainwindow_ui.h"

#include "mainwindow.h"

#include <QFormLayout>
#include <QGridLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : tableWidget{new TableWidget{QStringList() << "U, V" << "I, A", parent}}
    , loadPushButton{new QPushButton{"Load", parent}}
    , savePushButton{new QPushButton{"Save", parent}}
    , approximatePushButton{new QPushButton{"Approximate", parent}}
    , polynomialOrderComboBox{new PolynomialOrderComboBox{parent}}
    , equationTextEdit{new EquationTextEdit{parent}}
    , statisticsTextEdit{new StatisticsTextEdit{parent}}
    , plot{new Plot{parent}}
    , medianFilterCheckBox{new QCheckBox{"Median filter", parent}}
    , gaussFilterCheckBox{new QCheckBox{"Gauss filter", parent}}
{
    auto widget = new QWidget{parent};
    auto mainLayout = new QGridLayout{widget};

    auto layout_1 = new QHBoxLayout;
    layout_1->addWidget(loadPushButton);
    layout_1->addWidget(savePushButton);
    layout_1->addStretch();

    auto layout_2 = new QFormLayout;
    layout_2->addRow("Order: ", polynomialOrderComboBox);

    auto layout_3 = new QVBoxLayout;
    layout_3->addLayout(layout_2);
    layout_3->addWidget(approximatePushButton);
    layout_3->addWidget(medianFilterCheckBox);
    layout_3->addWidget(gaussFilterCheckBox);
    layout_3->addWidget(statisticsTextEdit);

    mainLayout->addWidget(tableWidget, 0, 0);
    mainLayout->addWidget(equationTextEdit, 1, 0);
    mainLayout->addLayout(layout_3, 0, 1, 2, 1);
    mainLayout->addLayout(layout_1, 2, 0, 1, 2);
    mainLayout->addWidget(plot, 0, 2, 3, 1);

    widget->setLayout(mainLayout);
    parent->setCentralWidget(widget);

    tableWidget->setFixedWidth(equationTextEdit->width());
}
