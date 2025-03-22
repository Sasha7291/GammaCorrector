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
    auto *layout = new QGridLayout(widget);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(tableWidget, 0, 0, 5, 2, Qt::AlignCenter);
    layout->addWidget(lineModeCheckBox, 0, 2, 1, 2, Qt::AlignLeft);
    layout->addWidget(polynomialModeCheckBox, 1, 2, 1, 2, Qt::AlignLeft);
    layout->addWidget(exponentionalModeCheckBox, 2, 2, 1, 2, Qt::AlignLeft);
    layout->addWidget(new QLabel("Order: "), 3, 2, Qt::AlignLeft);
    layout->addWidget(polynomialOrderComboBox, 3, 3, Qt::AlignLeft);
    layout->addWidget(approximatePushButton, 4, 2, 1, 2, Qt::AlignHCenter);
    layout->addWidget(loadPushButton, 5, 0, Qt::AlignCenter);
    layout->addWidget(savePushButton, 5, 1, Qt::AlignCenter);

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
}
