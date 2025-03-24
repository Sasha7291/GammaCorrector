#include "mainwindow_ui.h"

#include "mainwindow.h"

#include <QButtonGroup>
#include <QGridLayout>


MainWindow_Ui::MainWindow_Ui(MainWindow *parent) noexcept
    : tableWidget(new TableWidget(QStringList() << "U, V" << "I, A", parent))
    , loadPushButton(new QPushButton("Load", parent))
    , savePushButton(new QPushButton("Save", parent))
    , approximatePushButton(new QPushButton("Approximate", parent))
    , polynomialOrderComboBox(new QComboBox(parent))
    , lineModeCheckBox(new QCheckBox("Line", parent))
    , polynomialModeCheckBox(new QCheckBox("Polynom", parent))
    , exponentionalModeCheckBox(new QCheckBox("Exponent", parent))
{
    auto *widget = new QWidget(parent);
    auto *layout = new QHBoxLayout(widget);

    auto layout_1 = new QHBoxLayout;
    layout_1->addWidget(loadPushButton);
    layout_1->addWidget(savePushButton);

    auto layout_2 = new QVBoxLayout;
    layout_2->addWidget(tableWidget);
    layout_2->addLayout(layout_1);
    layout->addLayout(layout_2);

    auto layout_3 = new QHBoxLayout;
    layout_3->addWidget(new QLabel("Order: "));
    layout_3->addWidget(polynomialOrderComboBox);

    auto layout_4 = new QVBoxLayout;
    layout_4->addWidget(lineModeCheckBox);
    layout_4->addWidget(polynomialModeCheckBox);
    layout_4->addWidget(exponentionalModeCheckBox);
    layout_4->addLayout(layout_3);
    layout_4->addWidget(approximatePushButton);
    layout_4->addStretch();
    layout->addLayout(layout_4);

    widget->setLayout(layout);
    parent->setCentralWidget(widget);

    parent->connect(
        polynomialModeCheckBox, &QCheckBox::checkStateChanged,
        parent, [this](Qt::CheckState state) -> void {
            polynomialOrderComboBox->setEnabled(state == Qt::Checked);
        }
    );

    polynomialOrderComboBox->addItem("2", QVariant::fromValue(2));
    polynomialOrderComboBox->addItem("3", QVariant::fromValue(3));
    polynomialOrderComboBox->addItem("4", QVariant::fromValue(4));
    polynomialOrderComboBox->addItem("5", QVariant::fromValue(5));

    auto buttonGroup = new QButtonGroup(parent);
    buttonGroup->addButton(lineModeCheckBox);
    buttonGroup->addButton(polynomialModeCheckBox);
    buttonGroup->addButton(exponentionalModeCheckBox);
    buttonGroup->setExclusive(true);

    polynomialModeCheckBox->setChecked(true);

    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
