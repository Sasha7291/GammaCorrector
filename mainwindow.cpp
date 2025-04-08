#include "mainwindow.h"
#include "mainwindow_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<MainWindow_Ui>(this))
{
    connect(ui->loadPushButton, &QPushButton::clicked, this, [this]() -> void {
        try
        {
            ui->tableWidget->setValues(
                utils::stdVectorToQVector<QVector<QVector<double>>>(
                    csv::Reader<double>()(utils::getOpenFileName().toStdString())
                )
            );
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
        const auto [coeffs, values] = lsa::Approximator().polynomial(
            utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
            utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1)),
            ui->polynomialOrderComboBox->itemData(ui->polynomialOrderComboBox->currentIndex()).toULongLong()
        );

        ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
    });
}

MainWindow::~MainWindow() {}
