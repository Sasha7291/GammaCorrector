#include "plot3d.h"

#include <Q3DSurface>
#include <QSurface3DSeries>
#include <QSurfaceDataProxy>
#include <QSurfaceFormat>
#include <QWidget>


Plot3D::Plot3D(QObject *parent)
    : QObject{parent}
    , surface_{new Q3DSurface}
    , proxy_{new QSurfaceDataProxy}
    , series_{new QSurface3DSeries{proxy_}}
{
    series_->setDrawMode(QSurface3DSeries::DrawSurface);
    series_->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    series_->setFlatShadingEnabled(true);

    surface_->axisX()->setLabelFormat("%.2f");
    surface_->axisZ()->setLabelFormat("%.2f");
    surface_->axisX()->setLabelAutoRotation(30.f);
    surface_->axisY()->setLabelAutoRotation(90.f);
    surface_->axisZ()->setLabelAutoRotation(30.f);
    surface_->axisY()->setAutoAdjustRange(true);
}

Plot3D::~Plot3D()
{
    delete surface_;
}

QWidget *Plot3D::container() const
{
    QWidget *container = QWidget::createWindowContainer(surface_);
    container->setMinimumSize(200, 200);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    return container;
}

void Plot3D::setData(
    const QList<double> &keys,
    const QList<double> &values,
    const QList<QList<double>> &data,
    const QStringList &names
)
{
    auto dataArray = new QSurfaceDataArray;
    dataArray->reserve(data.size());

    for (int i = 0; i < data.size(); ++i)
    {
        auto row = new QSurfaceDataRow;
        row->reserve(data[i].size());

        for (int j = 0; j < data[i].size(); ++j)
            *row << QSurfaceDataItem{QVector3D{
                static_cast<float>(keys[j]),
                static_cast<float>(data[i][j]),
                static_cast<float>(values[i])
            }};

        *dataArray << row;
    }

    surface_->axisX()->setRange(std::ranges::min(keys), std::ranges::max(keys));
    surface_->axisZ()->setRange(std::ranges::min(values), std::ranges::max(values));
    surface_->axisX()->setTitle(names[0]);
    surface_->axisY()->setTitle(names[1]);
    surface_->axisZ()->setTitle(names[2]);

    proxy_->resetArray(dataArray);
    surface_->addSeries(series_);
}
