#pragma once

#include <QwtCounter>
#include <QwtPickerMachine>
#include <QwtPlotZoomer>
#include <QwtPlotPanner>
#include <QwtPlotRenderer>
#include <QwtText>

#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QLayout>
#include <QStatusBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QPen>
class Zoomer : public QwtPlotZoomer
{
public:
    Zoomer(int xAxis, int yAxis, QWidget* canvas);
};
