#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.hpp"
#include "lsa_statistics.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{std::make_unique<MainWindow_Ui>(this)}
{
    connect(ui->loadPushButton, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(ui->savePushButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(ui->approximatePushButton, &QPushButton::clicked, this, &MainWindow::approximate);
    connect(ui->plot, &Plot::markerMoved, this, &MainWindow::reapproximate);
    connect(ui->tableWidget, &TableWidget::columnChecked, this, [this](int index, bool checked) -> void {
        (checked)
            ? ui->plot->showCurve(index - 1)
            : ui->plot->hideCurve(index - 1);
    });
}

MainWindow::~MainWindow() {}

void MainWindow::approximate()
{
    const auto x = ui->tableWidget->column<double>(TableWidget::U);
    const auto y = ui->tableWidget->column<double>(TableWidget::I);

    if (!x.empty() && !y.empty())
        try
        {
            const auto [coeffs, values] = lsa::Approximator().polynomial(x, y, ui->polynomialOrderComboBox->currentPolynomialOrder());

            ui->tableWidget->hideRowTo(0);
            ui->tableWidget->setColumn(TableWidget::I_app, values, "I', A", 0, true, true);
            ui->statisticsTextEdit->setStatistics(lsa::Statistics()(x, y, values));
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData({ x, x }, { y, values }, { "I, A", "I', A" });
            ui->plot->showMarker();
        }
        catch (const lsa::Exception &exception)
        {
            utils::showWarningMessage(exception.what());
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
        ui->plot->setData(
            { ui->tableWidget->column<double>(TableWidget::U) },
            { ui->tableWidget->column<double>(TableWidget::I) },
            { "I, A" }
        );
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void MainWindow::reapproximate(int index, const QPointF &pos)
{
    const auto x = ui->tableWidget->column<double>(TableWidget::U);
    const auto y = ui->tableWidget->column<double>(TableWidget::I);
    const auto slicedX = x.last(x.size() - index);
    const auto slicedY = y.last(y.size() - index);

    if (!slicedX.empty() && !slicedY.empty())
        try
        {
            const auto [coeffs, values] = lsa::Approximator().polynomial(slicedX, slicedY, ui->polynomialOrderComboBox->currentPolynomialOrder());

            ui->tableWidget->setColumn(
                TableWidget::I_app,
                values,
                QString{},
                index,
                ui->tableWidget->isColumnCheckable(TableWidget::I_app),
                ui->tableWidget->isColumnChecked(TableWidget::I_app)
            );
            ui->tableWidget->hideRowTo(index);
            ui->statisticsTextEdit->setStatistics(lsa::Statistics()(slicedX, slicedY, values));
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData(1, slicedX, values, "I', A");
        }
        catch (const lsa::Exception &exception)
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
