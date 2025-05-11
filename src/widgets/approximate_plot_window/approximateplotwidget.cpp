#include "approximateplotwidget.h"
#include "approximateplotwidget_ui.h"

#include "approximateplotprocessor.h"

#include <QContextMenuEvent>
#include <QMdiSubWindow>

#include "psr_gaussfilter.h"
#include "psr_medianfilter.h"
#include "psr_powerfunction.h"


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

    normalizeData(ui->settingsWindow->voltageRange(), ui->settingsWindow->currentRange());
    approximateData(ui->settingsWindow->polynomialOrder(), ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    gammaData(ui->settingsWindow->gammaCorrectionOrder());

    ui->plot->showMarker();

    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::gammaCorrectionDegreeChanged, this, &ApproximatePlotWidget::gammaData);
    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::polynomialOrderChanged, this, [this](std::size_t order) -> void {
        approximateData(order, ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    });
    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::offsetChanged, this, [this](int offset, const QPointF &pos) -> void {
        approximateData(ui->settingsWindow->polynomialOrder(), offset, pos);
    });
    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::offsetChanged, this, [this]([[maybe_unused]] int index, const QPointF &pos) -> void {
        if (ui->plot->currentMarkerPosition().second != pos)
            ui->plot->setMarkerPosition(pos);
    });
    connect(ui->plot, &Plot::markerMoved, this, [this]([[maybe_unused]] int index, const QPointF &pos) -> void {
        if (ui->settingsWindow->offsetPosition() != pos)
            ui->settingsWindow->setOffsetPosition(pos);
    });
}

void ApproximatePlotWidget::calculateQ()
{
    QList<double> result(3);
    result[0] = ui->settingsWindow->gammaCorrectionOrder();
    result[1] = ui->settingsWindow->temperature();
    result[2] = ui->settingsWindow->offsetPosition().x();

    const auto gammaDataY = ui->plot->data(Gamma, 256)[1];
    const auto approximatedData = ui->plot->data(Approximated, 1024);
    auto [qX, qY] = ApproximatePlotProcessor{}.qData(gammaDataY, approximatedData[0], approximatedData[1], ui->settingsWindow->offsetPosition().x());

    result << qY;

    for (auto it = qY.begin(); it != qY.end(); ++it)
        if (std::isnan(*it))
        {
            qX.remove(std::distance(qY.begin(), it));
            qY.erase(it);
        }
    qX.squeeze();
    auto [additionalValuesX, additionalValuesY] = psr::PowerFunction<double>{0.0, qX[0]}(50, qY[0] / std::pow(qX[0], 3.0), 3.0);
    additionalValuesX << qX;
    additionalValuesY << qY;
    ui->plot->setData(CoefficientsQ, additionalValuesX, additionalValuesY, "Q", true);

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
    const auto approximatedData = ApproximatePlotProcessor{}.approximatedData(data[0], data[1], order, pos.x());

    coeffs_ = approximatedData[0];
    ui->originalData->hideRowTo(offset);
    ui->plot->setData(Approximated, approximatedData[1], approximatedData[2], "I_app", true);
    emit coeffsChanged(coeffs_);
}

void ApproximatePlotWidget::gammaData(double degree)
{
    const auto [gammaX, gammaY] = ApproximatePlotProcessor{}.gammaData({ 0.0, 1023.0 }, degree);
    ui->plot->setData(Gamma, gammaX, gammaY, "I_gamma");
}

void ApproximatePlotWidget::normalizeData(const QPair<double, double> &voltageRange, const QPair<double, double> &currentRange)
{
    const auto [normalizedDataX, normalizedDataY] = ApproximatePlotProcessor{}.normalizedData(
        ui->originalData->column(0, { 0, ui->originalData->rowCount() - 1 }),
        ui->originalData->column(1, { 0, ui->originalData->rowCount() - 1 }),
        voltageRange,
        currentRange
    );

    ui->settingsWindow->setOffsetPlotData(normalizedDataX, normalizedDataY);
    ui->plot->setData(Normalized, normalizedDataX, normalizedDataY, "I", true);
}
