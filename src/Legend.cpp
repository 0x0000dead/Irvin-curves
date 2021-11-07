#include "Legend.h"
// Legend label color + alpha + antialiasing
Legend::Legend()
{
    setRenderHint(QwtPlotItem::RenderAntialiased);

    const QColor c1(Qt::white);

    setTextPen(c1);
    setBorderPen(c1);

    QColor c2(Qt::gray);
    c2.setAlpha(200);

    setBackgroundBrush(c2);
}