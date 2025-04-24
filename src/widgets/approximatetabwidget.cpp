#include "approximatetabwidget.h"
#include "approximatetabwidget_ui.h"

#include "utils.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.h"
#include "psr_curvesproximity.h"
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
    connect(ui->tableWidget, &TableWidget::columnChecked, this, [this](int index, bool checked) -> void {
        (checked)
            ? ui->plot->showCurve(index - 1)
            : ui->plot->hideCurve(index - 1);
    });
}

ApproximateTabWidget::~ApproximateTabWidget() noexcept {}

void ApproximateTabWidget::approximate()
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
            index_ = ui->plot->currentMarkerPosition().first;
            const auto slicedX = x.last(x.size() - index_);
            const auto slicedY = y.last(y.size() - index_);
            const auto coeffs = lsa::Approximator().polynomial(slicedX, slicedY, ui->polynomialOrderComboBox->currentPolynomialOrder());
            const auto [keys, values] = psr::Polynomial<double>{slicedX.front(), slicedX.back()}(1024, coeffs);

            ui->tableWidget->hideRowTo(index_);
            ui->tableWidget->setColumnValues(2, values, "I', A", index_);
            ui->tableWidget->setColumnCheckable(2, true);
            ui->tableWidget->setColumnChecked(2, true);
            ui->statisticsTextEdit->setStatistics({
                psr::PearsonCoefficient<double>{}(slicedX, slicedY),
                psr::SpearmanCoefficient<double>{}(slicedX, slicedY),
                psr::CurvesProximity<double>{}(slicedX, slicedY, values.last(x.size() - index_)),
                psr::CurvesProximity<double>{}(slicedY, values.last(x.size() - index_))
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
        data[1] = psr::Rationing<double>{{minY, maxY}, {0, 255}}(data[1]);
        data = utils::transposeVector(data);

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

void ApproximateTabWidget::saveData()
{
    try
    {
        csv::Writer{}(utils::getSaveFileName().toStdString(), ui->tableWidget->values<double>(index_));
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}
