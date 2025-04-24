#include "approximatetabwidget_ui.h"

#include "approximatetabwidget.h"

#include <QFormLayout>
#include <QGridLayout>


ApproximateTabWidget_Ui::ApproximateTabWidget_Ui(ApproximateTabWidget *parent) noexcept
    : tableWidget{new TableWidget{QStringList() << "U, V" << "I, A", parent}}
    , savePushButton{new QPushButton{"Save", parent}}
    , approximatePushButton{new QPushButton{"Approximate", parent}}
    , polynomialOrderComboBox{new PolynomialOrderComboBox{parent}}
    , equationTextEdit{new EquationTextEdit{parent}}
    , statisticsTextEdit{new StatisticsTextEdit{parent}}
    , plot{new Plot{parent}}
    , filterCheckBox{new QCheckBox{"Filtering", parent}}
    , filterWidthComboBox{new FilterWidthComboBox{parent}}
{
    auto mainLayout = new QHBoxLayout{parent};

    auto layout_1 = new QHBoxLayout;
    layout_1->addWidget(savePushButton);
    layout_1->addStretch();

    auto layout_2 = new QFormLayout;
    layout_2->addRow("Order: ", polynomialOrderComboBox);

    auto layout_3 = new QFormLayout;
    layout_3->addRow("Width: ", filterWidthComboBox);

    auto layout_4 = new QVBoxLayout;
    layout_4->addLayout(layout_2);
    layout_4->addLayout(layout_3);
    layout_4->addWidget(filterCheckBox);
    layout_4->addWidget(statisticsTextEdit);
    layout_4->addWidget(approximatePushButton);

    auto layout_5 = new QVBoxLayout;
    layout_5->addWidget(tableWidget);
    layout_5->addWidget(equationTextEdit);
    layout_5->addLayout(layout_1);

    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(plot, 1);
    mainLayout->addLayout(layout_5);
    mainLayout->addLayout(layout_4);

    parent->setLayout(mainLayout);

    tableWidget->setFixedWidth(equationTextEdit->width());
}
