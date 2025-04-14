#include "mainwindow_ui.h"

#include "mainwindow.h"

#include <QGridLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : tableWidget(new TableWidget{QStringList() << "U, V" << "I, A", parent})
    , loadPushButton(new QPushButton{"Load", parent})
    , savePushButton(new QPushButton{"Save", parent})
    , approximatePushButton(new QPushButton{"Approximate", parent})
    , polynomialOrderComboBox(new PolynomialOrderComboBox{parent})
    , equationTextEdit(new EquationTextEdit{parent})
    , statisticsTextEdit(new StatisticsTextEdit{parent})
    , plot(new Plot{parent})
{
    auto widget = new QWidget{parent};
    auto layout = new QGridLayout{widget};

    auto layout_1 = new QHBoxLayout;
    layout_1->addWidget(loadPushButton);
    layout_1->addWidget(savePushButton);
    layout_1->addStretch();

    auto layout_2 = new QHBoxLayout;
    layout_2->addWidget(new QLabel("Order: "));
    layout_2->addWidget(polynomialOrderComboBox);

    auto layout_3 = new QVBoxLayout;
    layout_3->addLayout(layout_2);
    layout_3->addWidget(approximatePushButton);
    layout_3->addWidget(statisticsTextEdit);

    layout->addWidget(tableWidget, 0, 0);
    layout->addWidget(equationTextEdit, 1, 0);
    layout->addLayout(layout_3, 0, 1, 2, 1);
    layout->addLayout(layout_1, 2, 0, 1, 2);
    layout->addWidget(plot, 0, 2, 3, 1);

    widget->setLayout(layout);
    parent->setCentralWidget(widget);

    tableWidget->setFixedWidth(equationTextEdit->width());
}
