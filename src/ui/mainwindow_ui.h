#pragma once

#include "equationtextedit.h"
#include "filterwidthcombobox.h"
#include "plot.h"
#include "polynomialordercombobox.h"
#include "statisticstextedit.h"
#include "tablewidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPointer>
#include <QPushButton>


class MainWindow;

class MainWindow_Ui
{

public:
    MainWindow_Ui(MainWindow *parent) noexcept;
    ~MainWindow_Ui() noexcept = default;

    MainWindow_Ui(const MainWindow_Ui &) = delete;
    MainWindow_Ui(MainWindow_Ui &&) = delete;
    MainWindow_Ui &operator=(const MainWindow_Ui &) = delete;
    MainWindow_Ui &operator=(MainWindow_Ui &&) = delete;

    QPointer<TableWidget> tableWidget;
    QPointer<QPushButton> savePushButton;
    QPointer<QPushButton> loadPushButton;
    QPointer<QPushButton> approximatePushButton;
    QPointer<PolynomialOrderComboBox> polynomialOrderComboBox;
    QPointer<EquationTextEdit> equationTextEdit;
    QPointer<StatisticsTextEdit> statisticsTextEdit;
    QPointer<Plot> plot;
    QPointer<QCheckBox> filterCheckBox;
    QPointer<FilterWidthComboBox> filterWidthComboBox;

};
