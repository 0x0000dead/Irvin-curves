/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "Plot.h"
#include "Settings.h"

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

Plot::Plot( QWidget* parent )
    : QwtPlot( parent )
    , m_externalLegend( NULL )
    , m_legendItem( NULL )
    , m_isDirty( false )
{
    QwtPlotCanvas* canvas = new QwtPlotCanvas();
    canvas->setFocusIndicator( QwtPlotCanvas::CanvasFocusIndicator );
    canvas->setFocusPolicy( Qt::StrongFocus );
    canvas->setPalette( Qt::black );
    setCanvas( canvas );

    setAutoReplot( false );

    setTitle( "Irwin curves, sigma(Nd)" );

    // Grid
    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
    grid->setMinorPen( Qt::darkGray, 0, Qt::DotLine );
    grid->attach( this );

    // Axis
    setAxisScale(QwtAxis::YLeft, 0.0, 1000.0 );
    setAxisTitle(QwtAxis::YLeft, "Sigma, 1 / Om * sm");

    setAxisScale( QwtAxis::XBottom, pow(10,10), pow(10,20) );
    setAxisTitle(QwtAxis::XBottom, "Nd, donor count");

}

void Plot::insertCurve( const Settings& settings)
{
    int counter = settings.currentCurvesParam.size() - 1;
    const char* colors[] =
    {
        "LightSalmon",
        "SteelBlue",
        "Yellow",
        "Fuchsia",
        "PaleGreen",
        "PaleTurquoise",
        "Cornsilk",
        "HotPink",
        "Peru",
        "Maroon",
        "Green",
        "Blue",
        "Orange",
        "Red",
        "White"
    };

    const int numColors = sizeof( colors ) / sizeof( colors[0] );

    QwtPlotCurve* curve = new Curve(counter,settings.narrowWidget.type == 0,settings );

    curve->setPen( QColor( colors[counter % numColors ] ), 2 );
    curve->attach( this );
}

void Plot::drawAxis(const Settings & settings)
{
    // Irving curve sigma(Nd)
    if (settings.generalWidget.plotType == 0) {
        setTitle("Irwin curves, sigma(Nd)");

        setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisTitle(QwtAxis::YLeft, "Sigma, 1 / Om * sm");

        setAxisScale(QwtAxis::XBottom, pow(10, 10), pow(10, 20));
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisTitle(QwtAxis::XBottom, "Nd, cm^-3");
    }
    // Irving curve rho(Nd)
    else if (settings.generalWidget.plotType == 1) {
        setTitle("Irwin curves, rho(Nd)");

        setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisTitle(QwtAxis::YLeft, "rho, Om * sm");

        setAxisScale(QwtAxis::XBottom, pow(10, 10), pow(10, 20));
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisTitle(QwtAxis::XBottom, "Nd, cm^-3");
    }
    // Sigma_T
    else if (settings.generalWidget.plotType == 2)
    {
        setTitle("Conduction, sigma(T)");

        setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisTitle(QwtAxis::YLeft, "sigma, 1 / Om * sm");

        setAxisScale(QwtAxis::XBottom, 0, 1500);
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisTitle(QwtAxis::XBottom, "T, K");

    }
    // Mobility_T
    else if (settings.generalWidget.plotType == 3)
    {
        setTitle("Mobility, mu(T)");

        setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        setAxisAutoScale(QwtAxis::YLeft);
        //TODO
        setAxisTitle(QwtAxis::YLeft, "Mobility, TODO");

        setAxisScale(QwtAxis::XBottom, 0, 1500);
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisTitle(QwtAxis::XBottom, "T, K");
    }
    // Concentration_T
    else if (settings.generalWidget.plotType == 4)
    {
        setTitle("Concentration, n(T)");

        setAxisScale(QwtAxis::YLeft, pow(10, 10), pow(10, 20));
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisTitle(QwtAxis::YLeft, "Concentration, cm^-3");

        setAxisScale(QwtAxis::XBottom, 0, 1500);
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisTitle(QwtAxis::XBottom, "T, K");
    }
}

void Plot::overlayPlot(const Settings& settings)
{
    drawAxis(settings);

    QwtPlotItemList curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    int curveCount = settings.currentCurvesParam.size();
    if (lastPlotType != settings.generalWidget.plotType)
    {
        while (curveList.size() > 0)
        {
            QwtPlotItem* curve = curveList.takeFirst();
            delete curve;
        }
    }
    lastPlotType = settings.generalWidget.plotType;

    if (curveList.size() != curveCount)
    {
        while (curveList.size() > curveCount)
        {
            QwtPlotItem* curve = curveList.takeLast();
            delete curve;
        }

        for (int i = curveList.size(); i < curveCount; i++)
        {
            insertCurve(settings);
        }

    }

    curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    for (int i = 0; i < curveList.count(); i++)
    {
        Curve* curve = static_cast<Curve*>(curveList[i]);
        curve->setCurveTitle(settings.additionalParamWidget.title);

        int sz = 0.5 * settings.narrowWidget.size;
        curve->setLegendIconSize(QSize(sz, sz));
    }
  
}

void Plot::applySettings( const Settings& settings )
{
    m_isDirty = false;
    setAutoReplot( true );
    if (settings.generalWidget.show) {
        insertLegend(new QwtLegend(),
            QwtPlot::LegendPosition(QwtPlot::BottomLegend));

    }
    else
    {
        insertLegend(NULL);

    }
    overlayPlot(settings);


    setAutoReplot( false );
    if ( m_isDirty )
    {
        m_isDirty = false;
        replot();
    }
}

void Plot::replot()
{
    if ( autoReplot() )
    {
        m_isDirty = true;
        return;
    }

    QwtPlot::replot();
}

Plot::~Plot()
{
    delete m_externalLegend;
}

#include "moc_Plot.cpp"
