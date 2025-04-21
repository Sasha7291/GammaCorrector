#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.hpp"
#include "psr_curvesproximity.h"
#include "psr_gaussfilter.h"
#include "psr_medianfilter.h"
#include "psr_pearsoncoefficient.h"
#include "psr_spearmancoefficient.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{std::make_unique<MainWindow_Ui>(this)}
{
    connect(ui->loadPushButton, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(ui->savePushButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->approximatePushButton, &QPushButton::clicked, this, &MainWindow::approximate);
    connect(ui->tableWidget, &TableWidget::columnChecked, this, [this](int index, bool checked) -> void {
        (checked)
            ? ui->plot->showCurve(index - 1)
            : ui->plot->hideCurve(index - 1);
    });
}

MainWindow::~MainWindow() {}

void MainWindow::approximate()
{
    const auto x = ui->tableWidget->column<double>(0);
    auto y = ui->tableWidget->column<double>(1);

    if (!x.empty() && !y.empty())
    {
        if (ui->filterCheckBox->isChecked())
        {
            auto width = ui->filterWidthComboBox->currentWidth();
            y = psr::GaussFilter<double>{}(psr::MedianFilter<double>{}(y, width), width);
        }

        try
        {
            if (!ui->plot->isMovedMarkerShown())
                ui->plot->showMarker();
            const auto [index, _] = ui->plot->currentMarkerPosition();
            const auto slicedX = x.last(x.size() - index);
            const auto slicedY = y.last(y.size() - index);
            const auto [coeffs, values] = lsa::Approximator().polynomial(slicedX, slicedY, ui->polynomialOrderComboBox->currentPolynomialOrder());

            ui->tableWidget->hideRowTo(index);
            ui->tableWidget->setColumnValues(2, values, QString{}, index);
            ui->statisticsTextEdit->setStatistics({
                psr::PearsonCoefficient<double>{}(slicedX, slicedY),
                psr::SpearmanCoefficient<double>{}(slicedX, slicedY),
                psr::CurvesProximity<double>{}(slicedX, slicedY, values),
                psr::CurvesProximity<double>{}(slicedY, values)
            });
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData({ x, slicedX }, { y, values }, { "I, A", "I', A" });
        }
        catch (const lsa::Exception &exception)
        {
            utils::showWarningMessage(exception.what());
        }
    }
}

void MainWindow::loadData()
{
    try
    {
        auto data = utils::stdVectorToQVector<QVector<QVector<double>>>(
            csv::Reader<double>()(utils::getOpenFileName().toStdString())
        );

        ui->tableWidget->setValues(data);
        ui->tableWidget->setColumnCheckable(0, false);
        ui->tableWidget->setColumnCheckable(1, true);
        ui->tableWidget->setColumnChecked(1, true);
        ui->plot->setData(
            { ui->tableWidget->column<double>(0) },
            { ui->tableWidget->column<double>(1) },
            { "I, A" }
        );
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void MainWindow::saveData()
{
    try
    {
        csv::Writer()(
            utils::getSaveFileName().toStdString(),
            utils::qVectorToStdVector<std::vector<std::vector<double>>>(ui->tableWidget->values<double>())
        );
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}
