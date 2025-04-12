#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.hpp"
#include "lsa_statistics.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<MainWindow_Ui>(this))
{
    connect(ui->loadPushButton, &QPushButton::clicked, this, [this]() -> void {
        try
        {
            auto data = utils::stdVectorToQVector<QVector<QVector<double>>>(
                csv::Reader<double>()(utils::getOpenFileName().toStdString())
            );

            ui->tableWidget->setValues(data);
            ui->plot->setData({ ui->tableWidget->column<double>(0) }, { ui->tableWidget->column<double>(1) }, QStringList() << "I, A");
        }
        catch (const csv::Exception &exception)
        {
            utils::showWarningMessage(exception.what());
        }
    });
    connect(ui->savePushButton, &QPushButton::clicked, this, [this]() -> void {
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
    });

    connect(ui->approximatePushButton, &QPushButton::clicked, this, [this]() -> void {
        auto x = ui->tableWidget->column<double>(0);
        auto y = ui->tableWidget->column<double>(1);

        if (!x.empty() && !y.empty())
        {
            const auto [coeffs, values] = lsa::Approximator().polynomial(x, y, ui->polynomialOrderComboBox->currentPolynomialOrder());

            ui->tableWidget->setColumn(2, "I', A", values, true, true);
            ui->statisticsTextEdit->setStatistics(lsa::Statistics()(x, y));
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData({ x, x }, { y, values }, QStringList{ "I, A", "I', A" });
            ui->plot->showMarker();
        }
    });

    connect(ui->plot, &Plot::markerMoved, this, [this](int index, [[maybe_unused]] const QPointF &pos) -> void {
        auto x = ui->tableWidget->column<double>(0);
        auto y = ui->tableWidget->column<double>(1);
        auto slicedX = x.last(x.size() - index);
        auto slicedY = y.last(y.size() - index);

        if (!slicedX.empty() && !slicedY.empty())
        {
            const auto [coeffs, values] = lsa::Approximator().polynomial(slicedX, slicedY, ui->polynomialOrderComboBox->currentPolynomialOrder());

            ui->statisticsTextEdit->setStatistics(lsa::Statistics()(slicedX, slicedY));
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData(1, slicedX, values, "I', A");
        }
    });

    connect(ui->tableWidget, &TableWidget::columnChecked, this, [this](int index, bool checked) -> void {
        (checked)
            ? ui->plot->showCurve(index - 1)
            : ui->plot->hideCurve(index - 1);
    });
}

MainWindow::~MainWindow() {}
