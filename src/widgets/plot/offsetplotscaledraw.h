#pragma once

#include <QwtScaleDraw>
#include <QwtText>
#include <QFont>


class OffsetPlotScaleDraw : public QwtScaleDraw
{

public:
    OffsetPlotScaleDraw(const QFont& font) : font_(font) {}

    QwtText label(double value) const override
    {
        QwtText lbl = QwtScaleDraw::label(value);
        lbl.setFont(font_);
        return lbl;
    }

private:
    QFont font_;

};
