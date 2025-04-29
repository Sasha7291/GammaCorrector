#include "statisticstextedit.h"


StatisticsTextEdit::StatisticsTextEdit(QWidget *parent) noexcept
    : QTextEdit{parent}
{
    setFixedWidth(100);
    setMinimumHeight(90);
    setReadOnly(true);
}

void StatisticsTextEdit::setStatistics(const QVector<double> &statistics)
{
    setHtml(_PATTERN_.arg(
        QString::number(statistics[0]),
        QString::number(statistics[1])
    ));
}
