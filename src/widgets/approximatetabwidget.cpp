#include "approximatetabwidget.h"
#include "approximatetabwidget_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.h"
#include "psr_gaussfilter.h"
#include "psr_medianfilter.h"
#include "psr_pearsoncoefficient.h"
#include "psr_polynomial.h"
#include "psr_rationing.h"
#include "psr_spearmancoefficient.h"


ApproximateTabWidget::ApproximateTabWidget(QTabWidget *parent) noexcept
    : AbstractTabWidget{"Approximate", parent}
    , ui{std::make_unique<ApproximateTabWidget_Ui>(this)}
    , index_{0}
{
    connect(ui->approximatePushButton, &QPushButton::clicked, this, &ApproximateTabWidget::approximate);
    connect(ui->tableWidget, &TableWidget::dataUpdated, this, &ApproximateTabWidget::approximate);
}

ApproximateTabWidget::~ApproximateTabWidget() noexcept {}

void ApproximateTabWidget::approximate()
{
    const auto x = ui->tableWidget->column(0, {0, ui->tableWidget->rowCount() - 1});
    auto y = ui->tableWidget->column(1, {0, ui->tableWidget->rowCount() - 1});

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
            index_ = ui->plot->currentMarkerPosition().first;
            const auto slicedX = x.last(x.size() - index_);
            const auto slicedY = y.last(y.size() - index_);
            const auto coeffs = lsa::Approximator().polynomial(slicedX, slicedY, ui->polynomialOrderComboBox->currentPolynomialOrder());
            const auto [keys, values] = psr::Polynomial<double>{slicedX.front(), slicedX.back()}(1024, coeffs);

            ui->tableWidget->hideRowTo(index_);
            ui->statisticsTextEdit->setStatistics({
                psr::PearsonCoefficient<double>{}(slicedX, slicedY),
                psr::SpearmanCoefficient<double>{}(slicedX, slicedY)
            });
            ui->equationTextEdit->setEquation("V", "I", coeffs);
            ui->plot->setData({ x, keys }, { y, values }, { "I, A", "I', A" });
        }
        catch (const lsa::Exception &exception)
        {
            utils::showWarningMessage(exception.what());
        }
    }
}

void ApproximateTabWidget::loadData()
{
    try
    {
        index_ = 0;
        auto data = utils::transposeVector(csv::Reader<double>{}(utils::getOpenFileName().toStdString()));
        auto [minX, maxX] = std::ranges::minmax(data[0]);
        data[0] = psr::Rationing<double>{{minX, maxX}, {0, 1023}}(data[0]);
        auto [minY, maxY] = std::ranges::minmax(data[1]);
        data[1] = psr::Rationing<double>{{minY, maxY}, {0, 1023}}(data[1]);

        ui->tableWidget->setColumns(data, {"U, V", "I, A"});
        ui->tableWidget->setColumnCheckable(0, false);
        ui->tableWidget->setColumnCheckable(1, false);
        ui->plot->setData(
            { ui->tableWidget->column(0, {0, ui->tableWidget->rowCount() - 1}) },
            { ui->tableWidget->column(1, {0, ui->tableWidget->rowCount() - 1}) },
            { "I, A" }
        );
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void ApproximateTabWidget::saveData()
{
    try
    {
        csv::Writer{}(utils::getSaveFileName().toStdString(), ui->tableWidget->columns({0, ui->tableWidget->columnCount() - 1}, {index_, ui->tableWidget->rowCount() - 1}));
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}
