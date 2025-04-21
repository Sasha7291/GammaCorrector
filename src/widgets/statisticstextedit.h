#pragma once

#include <QTextEdit>


class StatisticsTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit StatisticsTextEdit(QWidget *parent = nullptr) noexcept;
    ~StatisticsTextEdit() noexcept = default;

    void setStatistics(const QVector<double> &statistics);

private:
    const QString _PATTERN_ =
        R"(
        <h3>Statistics:</h3>
        r = %1<br>
        &rho; = %2<br>
        &delta; = %3<br>
        &Delta; = %4
        )";

};
