#include "gammacorrectiontabwidget.h"

#include "gammacorrectiontabwidget_ui.h"

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "lsa_approximator.h"
#include "psr_rationing.h"
#include "psr_powerfunction.h"
#include "psr_selection.h"
#include "utils.h"


GammaCorrectionTabWidget::GammaCorrectionTabWidget(QTabWidget *parent) noexcept
    : AbstractTabWidget{"Gamma correction", parent}
    , ui(std::make_unique<GammaCorrectionTabWidget_Ui>(this))
{}

GammaCorrectionTabWidget::~GammaCorrectionTabWidget() noexcept {}

void GammaCorrectionTabWidget::loadData()
{
    try
    {
        auto data = utils::transposeVector(csv::Reader<double>{}(utils::getOpenFileName().toStdString()));
        auto [minX, maxX] = std::ranges::minmax(data[0]);
        data[0] = psr::Rationing<double>{{minX, maxX}, {0, 1023}}(data[0]);
        auto [minY, maxY] = std::ranges::minmax(data[1]);
        data[1] = psr::Rationing<double>{{minY, maxY}, {0, 255}}(data[1]);

        const auto coeffs = lsa::Approximator().polynomial(data[0], data[1], 7);
        const auto [keys, values] = psr::Polynomial<double>{data[0].front(), data[0].back()}(1024, coeffs);
        const double degree = ui->gammaCorrectionDoubleSpinBox->value();
        const auto [gammaX, gammaY] = psr::PowerFunction<double>{data[0].front(), data[0].back()}(1024, data[1].back() / std::pow(data[0].back(), degree), degree);

        ui->plot->setData({keys, gammaX}, {values, gammaY}, {"I, A", "I_g, A"});
    }
    catch (const csv::Exception &exception)
    {
        utils::showWarningMessage(exception.what());
    }
}

void GammaCorrectionTabWidget::saveData()
{

}


