#include "approximateplotwidget.h"
#include "approximateplotwidget_ui.h"

#include "approximateplotprocessor.h"

#include <QContextMenuEvent>
#include <QMdiSubWindow>

#include "psr_powerfunction.h"


ApproximatePlotWidget::ApproximatePlotWidget(QWidget *parent)
    : SubWindowWidget{parent}
    , processor{std::make_unique<ApproximatePlotProcessor>()}
    , ui{std::make_unique<ApproximatePlotWidget_Ui>(this)}
    , coeffs_{}
    , currentPeakIndex_{0}
    , dataSubstracted_{false}
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

    normalizeData();
    approximateData(ui->settingsWindow->polynomialOrder(), ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    gammaData(ui->settingsWindow->gammaCorrectionOrder());

    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::gammaCorrectionDegreeChanged, this, &ApproximatePlotWidget::gammaData);
    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::polynomialOrderChanged, this, [this](std::size_t order) -> void {
        approximateData(order, ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());
    });
    connect(ui->settingsWindow, &ApproximatePlotSettingsWidget::offsetChanged, this, [this](std::size_t index, const QPointF &pos) -> void {
        if (ui->plot->currentMarkerPosition().first != index)
            ui->plot->setMarkerPosition(pos);
    });

    connect(ui->plot, &Plot::markerMoved, this, [this](std::size_t offset, const QPointF &pos) -> void {
        approximateData(ui->settingsWindow->polynomialOrder(), offset, pos);
    });
    connect(ui->plot, &Plot::markerMoved, this, [this](std::size_t index, const QPointF &pos) -> void {
        if (ui->settingsWindow->offsetIndex() != index)
            ui->settingsWindow->setOffsetPosition(pos);
    });
}

void ApproximatePlotWidget::calculateQ()
{
    const auto gammaDataY = ui->plot->data(Gamma, 256)[1];
    const auto approximatedData = ui->plot->data(Approximated, processor->dataSize());
    auto [qX, qY] = processor->qData(gammaDataY, approximatedData[0], approximatedData[1], ui->settingsWindow->offsetPosition().x());
    auto originalX = ui->originalData->column(0, { 0 , ui->originalData->rowCount() - 1 });

    QList<double> result(4);
    result[0] = ui->settingsWindow->gammaCorrectionOrder();
    result[1] = ui->settingsWindow->temperature();
    result[3] = std::ranges::max(originalX);
    result[2] = originalX.at(ui->settingsWindow->offsetIndex() / static_cast<double>(processor->dataSize()) * ui->originalData->rowCount());
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
    ui->plot->setAxisOrigin(QwtPlot::xBottom, 1.0);

    emit qCalculated(result);
}

void ApproximatePlotWidget::findOffset()
{
    const auto data = ui->plot->data(Normalized, processor->dataSize());
    const auto peaks = processor->peakData(data[1]);

    ui->plot->setMarkerPosition(QPointF{data[0][peaks[currentPeakIndex_]], data[1][peaks[currentPeakIndex_]]});
    currentPeakIndex_ == peaks.size() - 1 ? currentPeakIndex_ = 0 : ++currentPeakIndex_;
}

void ApproximatePlotWidget::substractLine()
{
    disconnect(ui->plot, &Plot::markerMoved, this, nullptr);
    disconnect(ui->plot, &Plot::markerMoved, this, nullptr);

    if (!dataSubstracted_)
    {
        const auto data = ui->plot->data(Normalized, processor->dataSize());
        auto [substractedX, substractedY] = processor->substractLineData(data[0], data[1]);
        substractedX.removeAt(0);
        substractedY.removeAt(0);

        ui->plot->setData(Normalized, substractedX, substractedY, "I", true);
        ui->plot->showMarker();
        ui->plot->setAxisOrigin(QwtPlot::xBottom, 1.0);

        ui->settingsWindow->setOffsetPlotData(substractedX, substractedY);
        approximateData(ui->settingsWindow->polynomialOrder(), ui->settingsWindow->offsetIndex(), ui->settingsWindow->offsetPosition());

        dataSubstracted_ = true;
    }

    connect(ui->plot, &Plot::markerMoved, this, [this](std::size_t offset, const QPointF &pos) -> void {
        approximateData(ui->settingsWindow->polynomialOrder(), offset, pos);
    });
    connect(ui->plot, &Plot::markerMoved, this, [this](std::size_t index, const QPointF &pos) -> void {
        if (ui->settingsWindow->offsetIndex() != index)
            ui->settingsWindow->setOffsetPosition(pos);
    });
}

void ApproximatePlotWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse)
        ui->showContextMenu(event->pos());
}

void ApproximatePlotWidget::approximateData(std::size_t order, std::size_t offset, const QPointF &pos)
{
    try
    {
        const auto data = ui->plot->data(Normalized, processor->dataSize());
        if (offset >= data[0].size())
            offset = 0ull;
        const auto approximatedData = processor->approximatedData(data[0], data[1], order, offset);

        coeffs_ = approximatedData[0] + processor->statisticsData(
            data[0].last(data[0].size() - offset),
            data[1].last(data[1].size() - offset),
            approximatedData[2].last(approximatedData[2].size() - offset)
        );
        ui->originalData->hideRowTo(offset / static_cast<double>(processor->dataSize()) * ui->originalData->rowCount());
        ui->plot->setData(Approximated, approximatedData[1], approximatedData[2], "I_app", true);
        ui->plot->setAxisOrigin(QwtPlot::xBottom, 1.0);

        emit coeffsChanged(coeffs_);
    }
    catch (const std::exception &exception)
    {
        qWarning() << exception.what();
    }
}

void ApproximatePlotWidget::gammaData(double degree)
{
    const auto [gammaX, gammaY] = processor->gammaData(degree);
    ui->plot->setData(Gamma, gammaX, gammaY, "I_gamma");
    ui->plot->setAxisOrigin(QwtPlot::xBottom, 1.0);
}

void ApproximatePlotWidget::normalizeData()
{
    auto [normalizedDataX, normalizedDataY] = processor->normalizedData(
        ui->originalData->column(0, { 0, ui->originalData->rowCount() - 1 }),
        ui->originalData->column(1, { 0, ui->originalData->rowCount() - 1 })
    );
    normalizedDataX.removeAt(0);
    normalizedDataY.removeAt(0);

    ui->plot->setData(Normalized, normalizedDataX, normalizedDataY, "I", true);

    const auto data = ui->plot->data(Normalized, processor->dataSize());
    ui->plot->setData(Normalized, data[0], data[1], "I", true);
    ui->plot->showMarker();
    ui->plot->setAxisOrigin(QwtPlot::xBottom, 1.0);
    ui->settingsWindow->setOffsetPlotData(data[0], data[1]);
}
