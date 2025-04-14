#include "statisticstextedit.h"


StatisticsTextEdit::StatisticsTextEdit(QWidget *parent) noexcept
    : QTextEdit{parent}
{
    setFixedWidth(90);
    setMinimumHeight(90);
}

void StatisticsTextEdit::setStatistics(const QVector<double> &statistics)
{
    setHtml(_PATTERN_.arg(
        QString::number(statistics[0]),
        QString::number(statistics[1]),
        QString::number(statistics[2]),
        QString::number(statistics[3])
    ));
}
