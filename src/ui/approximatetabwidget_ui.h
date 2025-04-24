#pragma once

#include "equationtextedit.h"
#include "filterwidthcombobox.h"
#include "plot.h"
#include "polynomialordercombobox.h"
#include "statisticstextedit.h"
// #include "tablewidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPointer>
#include <QPushButton>


class ApproximateTabWidget;

class ApproximateTabWidget_Ui
{

public:
    explicit ApproximateTabWidget_Ui(ApproximateTabWidget *parent) noexcept;
    ~ApproximateTabWidget_Ui() noexcept = default;

    ApproximateTabWidget_Ui(const ApproximateTabWidget_Ui &) = delete;
    ApproximateTabWidget_Ui(ApproximateTabWidget_Ui &&) = delete;
    ApproximateTabWidget_Ui &operator=(const ApproximateTabWidget_Ui &) = delete;
    ApproximateTabWidget_Ui &operator=(ApproximateTabWidget_Ui &&) = delete;

    // QPointer<TableWidget> tableWidget;
    QPointer<QPushButton> savePushButton;
    QPointer<QPushButton> approximatePushButton;
    QPointer<PolynomialOrderComboBox> polynomialOrderComboBox;
    QPointer<EquationTextEdit> equationTextEdit;
    QPointer<StatisticsTextEdit> statisticsTextEdit;
    QPointer<Plot> plot;
    QPointer<QCheckBox> filterCheckBox;
    QPointer<FilterWidthComboBox> filterWidthComboBox;

};
