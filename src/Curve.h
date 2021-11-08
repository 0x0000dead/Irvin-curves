#pragma once
#include <QwtPlotCurve>
#include <QwtLegend>
#include <QwtPlotGrid>
#include <QwtPlotLayout>
#include <QwtMath>
#include "Settings.h"

class Curve : public QwtPlotCurve
{
public:
    Curve(int index, int isElectron, const Settings& settings);

    void setCurveTitle(const QString& title);

    void initData();
private:
    const int m_index;
    Settings _settings;
    const int _isElectron;

};
