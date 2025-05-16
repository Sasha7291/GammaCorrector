#pragma once

#include "subwindowwidget.h"


class ApproximatePlotWidget_Ui;

class ApproximatePlotWidget : public SubWindowWidget
{
    Q_OBJECT

public:
    explicit ApproximatePlotWidget(QWidget *parent = nullptr);
    ~ApproximatePlotWidget() override;

    [[nodiscard]] QList<double> coeffs() const;
    void setData(const QList<QList<double>> &data);

public slots:
    void calculateQ();
    void findOffset();
    void substractLine();

signals:
    void coeffsChanged(const QList<double> &coeffs);
    void qCalculated(const QList<double> &Q);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    enum CurveName
    {
        Normalized,
        Approximated,
        Gamma,
        CoefficientsQ
    };

    void approximateData(std::size_t order, int offset, const QPointF &pos);
    void gammaData(double degree);
    void normalizeData();

    std::unique_ptr<ApproximatePlotWidget_Ui> ui;
    QList<double> coeffs_;
    std::size_t currentPeakIndex_;
    bool dataSubstracted_;

};
