#pragma once

#include "grid.h"
#include "legend.h"
#include "movedmarker.h"

#include <QwtPlot>


class Curve;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    Plot(const Plot&) = delete;
    Plot(Plot&&) = delete;
    ~Plot() = default;

    Plot &operator=(const Plot&) = delete;
    Plot &operator=(Plot&&) = delete;

    [[nodiscard]] std::pair<int, QPointF> currentMarkerPosition() const noexcept;
    [[nodiscard]] bool isMovedMarkerShown() const noexcept;
    void setData(
        const QVector<QVector<double>> &keys,
        const QVector<QVector<double>> &values,
        const QStringList &names
    );
    void setData(
        unsigned index,
        const QVector<double> &keys,
        const QVector<double> &values,
        const QString &name
    );

public slots:
    void hideCurve(int index);
    void hideMarker();
    void showCurve(int index);
    void showMarker();

signals:
    void markerMoved(int index, const QPointF &pos);

private:
    using CurvesVector = QVector<Curve *>;
    using ColorsVector = QVector<QColor>;

    std::unique_ptr<Grid> grid_;
    std::unique_ptr<Legend> legend_;
    std::unique_ptr<MovedMarker> movedMarker_;
    CurvesVector curves_;
    ColorsVector colors_;
    QVector<double> xValues_;
    QVector<double> yValues_;

};
