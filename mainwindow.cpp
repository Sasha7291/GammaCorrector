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

    // убрать линейную аппроксимацию, передать степень полинома как параметр функции, а не шаблона

    connect(ui->approximatePushButton, &QPushButton::clicked, this, [this]() -> void {
        if (ui->lineModeCheckBox->checkState() == Qt::Checked)
        {
            const auto [coeffs, values] = lsa::Approximator().linear(
                utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
            );

            ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
        }
        else if (ui->polynomialModeCheckBox->checkState() == Qt::Checked)
        {
            switch (ui->polynomialOrderComboBox->currentData().toInt())
            {
            case 2:
            {
                const auto [coeffs, values] = lsa::Approximator().polynomial<3>(
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
                );

                ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
                break;
            }

            case 3:
            {
                const auto [coeffs, values] = lsa::Approximator().polynomial<4>(
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
                );

                ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
                break;
            }

            case 4:
            {
                const auto [coeffs, values] = lsa::Approximator().polynomial<5>(
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
                );

                ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
                break;
            }

            case 5:
            {
                const auto [coeffs, values] = lsa::Approximator().polynomial<6>(
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                    utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
                );

                ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
                break;
            }
            }
        }
        else if (ui->exponentionalModeCheckBox->checkState() == Qt::Checked)
        {
            const auto [coeffs, values] = lsa::Approximator().exponential(
                utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(0)),
                utils::qVectorToStdVector<std::vector<double>>(ui->tableWidget->column<double>(1))
            );

            ui->tableWidget->setColumn(2, "I', A", utils::stdVectorToQVector<QVector<double>>(values));
        }
    });
}

MainWindow::~MainWindow() {}
