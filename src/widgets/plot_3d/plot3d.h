#pragma once

#include <QObject>
#include <QSize>


class Q3DSurface;
class QGradient;
class QSurfaceDataProxy;
class QSurface3DSeries;


class Plot3D : public QObject
{
    Q_OBJECT

public:
    Plot3D(QObject *parent = nullptr);
    Plot3D(const Plot3D &) = delete;
    Plot3D(Plot3D &&) = delete;
    ~Plot3D();

    Plot3D &operator=(const Plot3D&) = delete;
    Plot3D &operator=(Plot3D&&) = delete;

    QWidget *container() const;
    void setData(
        const QList<double> &keys,
        const QList<double> &values,
        const QList<QList<double>> &data,
        const QStringList &names
    );

private:
    Q3DSurface *surface_;
    QSurfaceDataProxy *proxy_;
    QSurface3DSeries *series_;

};
