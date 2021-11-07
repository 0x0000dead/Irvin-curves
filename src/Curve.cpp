#include "Curve.h"
#include <QwtPlotCurve>
#include <QwtPlotLegendItem>
#include <QwtLegend>
#include <QwtPlotCanvas>
#include <QwtPlotGrid>
#include <QwtPlotLayout>
#include <QwtMath>
#include "Curve.h"
#include "Legend.h"
#include <QPen>
Curve::Curve(int index, int isElectron,  const Settings& settings) : m_index(index), _isElectron(isElectron), _settings(settings)
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    // Conductivity
    if (_settings.generalWidget.plotType == 0)
    {
        plotConductivityCurves(_settings.currentCurvesParam[index]);
    }
    else if (_settings.generalWidget.plotType == 1)
    // Mobility
    {
        plotMobilityCurves(_settings.currentCurvesParam[index]);
    }
    else if (_settings.generalWidget.plotType == 2)
    // Concentration
    {
        plotConcentrationCurves(_settings.currentCurvesParam[index]);
    }

}


void Curve::setCurveTitle(const QString& title)
{
    QString txt("%1 %2");
    setTitle(QString("%1  %2").arg(title).arg(m_index));
}

void Curve::plotConductivityCurves(Settings::paramEquation & param)
{
    QVector< QPointF > points;

    double y;

    for (double x = 0.0; x <= 1000.0; x += 100.0)
    {
        y = -x + 1000;

        points += QPointF(x, y);
    }

    setSamples(points);


}

void Curve::plotMobilityCurves(Settings::paramEquation & param)
{
    QVector< QPointF > points;

    double y;

    for (double x = 0.0; x <= 1000.0; x += 100.0)
    {
        y = -x + 1000;

        points += QPointF(x, y);
    }

    setSamples(points);
}

void Curve::plotConcentrationCurves(Settings::paramEquation & param)
{
    QVector< QPointF > points;

    double y;

    for (double x = 0.0; x <= 1000.0; x += 100.0)
    {
        y = -x*param.temperature + 1000;

        points += QPointF(x, y);
    }

    setSamples(points);
}
