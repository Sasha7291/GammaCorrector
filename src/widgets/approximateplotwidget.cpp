#include "approximateplotwidget.h"
#include "approximateplotwidget_ui.h"

#include <QContextMenuEvent>
#include <QMdiSubWindow>

#include "lsa_approximator.h"
#include "psr_gaussfilter.h"
#include "psr_medianfilter.h"
#include "psr_polynomial.h"
#include "psr_powerfunction.h"
#include "psr_rationing.h"


ApproximatePlotWidget::ApproximatePlotWidget(QWidget *parent)
    : SubWindowWidget{parent}
    , ui{std::make_unique<ApproximatePlotWidget_Ui>(this)}
    , coeffs_{}
{
    if (parent != nullptr)
        parent->installEventFilter(this);
}

ApproximatePlotWidget::~ApproximatePlotWidget() {}

QList<double> ApproximatePlotWidget::coeffs() const
{
    return coeffs_;
}

void ApproximatePlotWidget::setData(const QList<QList<double>> &data)
{
    ui->originalData->setColumns(data, {"U, V", "I, A"});
    ui->originalData->setColumnCheckable(0, false);
    ui->originalData->setColumnCheckable(1, false);

    ui->plot->setAxisTitles({ "U, dsc", "I, dsc" });

    normalizeData({ 0, 1023 }, { 0, 1023 });
    approximateData(ui->settingsWindow->polynomialOrder(), ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    gammaData(ui->settingsWindow->gammaCorrectionOrder());

    ui->plot->showMarker();
    ui->plot->setManualMoveMarker(false);

    connect(ui->settingsWindow, &SettingsWindow::gammaCorrectionDegreeChanged, this, &ApproximatePlotWidget::gammaData);
    connect(ui->settingsWindow, &SettingsWindow::polynomialOrderChanged, this, [this](std::size_t order) -> void {
        approximateData(order, ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    });
    connect(ui->settingsWindow, &SettingsWindow::offsetChanged, this, [this](int offset, const QPointF &pos) -> void {
        approximateData(ui->settingsWindow->polynomialOrder(), offset, pos);
    });
}

void ApproximatePlotWidget::calculateQ()
{
    QList<double> result(10);
    result[0] = ui->settingsWindow->temperature();
    result[1] = ui->settingsWindow->offsetPosition().x();

    const auto gammaDataY = ui->plot->data(Gamma, 256)[1];
    const auto approximatedData = ui->plot->data(Approximated, 1024);
    QList<double> qX(gammaDataY.size());
    QList<double> qY(gammaDataY.size());

    for (int i = 0; i < gammaDataY.size(); ++i)
    {
        qX[i] = 4 * i;
        double currentGammaValue = gammaDataY[i];
        double minimumDifferece = std::abs(approximatedData[1][0] - currentGammaValue);
        int index = 0;

        for (int j = 0; j < approximatedData[1].size(); ++j)
        {
            double currentDifference = std::abs(approximatedData[1][j] - currentGammaValue);

            if (minimumDifferece > currentDifference)
            {
                minimumDifferece = currentDifference;
                index = j;
            }
        }

        double resultValue = std::round(approximatedData[0][index]);
        if (resultValue >= result[1])
            qY[i] = resultValue;
        else
            qY[i] = 0.0;
    }

    for (int i = 1; i < 9; ++i)
    {
        double resultValue = std::round(qY[std::pow(2, i) - 1]);
        if (resultValue >= result[1])
            result[i + 1] = resultValue;
        else
            result[i + 1] = std::numeric_limits<double>::quiet_NaN();
    }

    qX.insert(1, 3);
    qX.insert(1, 2.5);
    qX.insert(1, 2);
    qX.insert(1, 1.5);
    qX.insert(1, 1);
    qX.insert(1, 0.5);
    qY.insert(1, qY[1] * 1.0 / 6 * 5);
    qY.insert(1, qY[1] * 1.0 / 6 * 4);
    qY.insert(1, qY[1] * 1.0 / 6 * 3);
    qY.insert(1, qY[1] * 1.0 / 6 * 2);
    qY.insert(1, qY[1] * 1.0 / 6);
    qY[255] = result[9] = 1023.0;

    ui->plot->setData(CoefficientsQ, qX, qY, "Q", true);

    emit qCalculated(result);
}

void ApproximatePlotWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse)
        ui->showContextMenu(event->pos());
}

void ApproximatePlotWidget::approximateData(std::size_t order, int offset, const QPointF &pos)
{
    const auto data = ui->plot->data(Normalized, 1024);
    const auto offsetIt = std::find_if(data[0].cbegin(), data[0].cend(), [pos](double value) -> bool {
        return value > pos.x();
    });
    const auto offsetIndex = data[0].indexOf(*offsetIt);
    const auto slicedX = QList<double>{ offsetIt, data[0].cend() };
    const auto slicedY = data[1].last(data[1].size() - offsetIndex);

    coeffs_ = lsa::Approximator().polynomial(slicedX, slicedY, order);
    auto [keys, values] = psr::Polynomial<double>{data[0].front(), data[0].back()}(1024, coeffs_);
    std::fill(values.begin(), values.begin() + offsetIndex, 0.0);

    ui->originalData->hideRowTo(offset);
    ui->plot->setData(Approximated, keys, values, "I_app", true);
    ui->plot->setMarkerPosition(pos);
    emit coeffsChanged(coeffs_);
}

void ApproximatePlotWidget::gammaData(double degree)
{
    const auto data = ui->plot->data(Normalized, 1024);
    const auto [gammaX, gammaY] = psr::PowerFunction<double>{data[0].front(), data[0].back()}(1024, data[1].back() / std::pow(data[0].back(), degree), degree);

    ui->plot->setData(Gamma, gammaX, gammaY, "I_gamma");
}

void ApproximatePlotWidget::normalizeData(const QPair<double, double> &xRange, const QPair<double, double> &yRange)
{
    auto data = ui->originalData->columns({ 0, ui->originalData->columnCount() - 1 }, { 0, ui->originalData->rowCount() - 1 });
    const auto [minX, maxX] = std::ranges::minmax(data[0]);
    const auto [minY, maxY] = std::ranges::minmax(data[1]);

    data[0] = psr::Rationing<double>{{minX, maxX}, xRange}(data[0]);
    data[1] = psr::Rationing<double>{{minY, maxY}, yRange}(data[1]);

    ui->settingsWindow->setOffsetPlotData(data[0], data[1]);
    ui->plot->setData(Normalized, data[0], data[1], "I", true);
}
