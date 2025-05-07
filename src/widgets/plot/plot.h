#pragma once

#include <QwtPlot>


class Curve;
class Grid;
class Legend;
class MovedMarker;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = nullptr);
    Plot(const Plot &) = delete;
    Plot(Plot &&) = delete;
    virtual ~Plot() override;

    Plot &operator=(const Plot &) = delete;
    Plot &operator=(Plot &&) = delete;

    [[nodiscard]] QPair<int, QPointF> currentMarkerPosition() const noexcept;
    [[nodiscard]] QList<QList<double>> data(int index, std::size_t size) const noexcept;
    [[nodiscard]] bool isMovedMarkerShown() const noexcept;
    void setAxisOrigin(QwtAxisId axis, double origin);
    void setAxisTitles(const QStringList &titles);
    virtual void setData(
        const QList<QList<double>> &keys,
        const QList<QList<double>> &values,
        const QStringList &names
    );
    virtual void setData(
        unsigned index,
        const QList<double> &keys,
        const QList<double> &values,
        const QString &name,
        bool autoScale = false
    );
    void setManualMoveMarker(bool moved);
    void setMarkerPosition(const QPointF &pos);

public slots:
    void hideCurve(int index);
    void hideMarker();
    void showCurve(int index);
    void showMarker();

signals:
    void markerMoved(int index, const QPointF &pos);

private slots:
    void legendChecked(const QVariant &itemInfo, bool on, int index);

private:
    using CurvesVector = QList<Curve *>;
    using ColorsVector = QList<QColor>;

    Grid *grid_;
    Legend *legend_;
    MovedMarker *movedMarker_;
    CurvesVector curves_;
    ColorsVector colors_;

};
