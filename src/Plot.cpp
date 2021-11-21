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

    //setAxisScale(QwtAxis::YLeft, 0.0, 1000.0 );
    setAxisTitle(QwtAxis::YLeft, "Sigma, 1 / Om * sm");
    setAxisAutoScale(QwtAxis::YLeft);
    setAxisAutoScale(QwtAxis::XBottom);

    //setAxisScale( QwtAxis::XBottom, pow(10,10), pow(10,20) );
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

        //setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        if (settings.additionalParamWidget.inverseAxis) {
            setAxisTitle(QwtAxis::YLeft, "Nd, cm^-3");
            setAxisTitle(QwtAxis::XBottom, "Sigma, 1 / Om * sm");
        } else
        {
            setAxisTitle(QwtAxis::YLeft, "Sigma, 1 / Om * sm");
            setAxisTitle(QwtAxis::XBottom, "Nd, cm^-3");
        }
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisAutoScale(QwtAxis::XBottom);


    }
    // Irving curve rho(Nd)
    else if (settings.generalWidget.plotType == 1) {
        setTitle("Irwin curves, rho(Nd)");

        //setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        if (settings.additionalParamWidget.inverseAxis) {
            setAxisTitle(QwtAxis::YLeft, "Nd, cm^-3");
            setAxisTitle(QwtAxis::XBottom, "rho, Om * sm");
        }
        else {
            setAxisTitle(QwtAxis::YLeft, "rho, Om * sm");
            setAxisTitle(QwtAxis::XBottom, "Nd, cm^-3");
        }
        setAxisAutoScale(QwtAxis::XBottom);
        setAxisAutoScale(QwtAxis::YLeft);


    }
    // Sigma_T
    else if (settings.generalWidget.plotType == 2)
    {
        setTitle("Conduction, sigma(T)");

        //setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        if (settings.additionalParamWidget.inverseAxis) {
            setAxisTitle(QwtAxis::YLeft, "T, K");
            setAxisTitle(QwtAxis::XBottom, "sigma, 1 / Om * sm");
        }
        else {
            setAxisTitle(QwtAxis::YLeft, "sigma, 1 / Om * sm");
            setAxisTitle(QwtAxis::XBottom, "T, K");
        }
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisAutoScale(QwtAxis::XBottom);

    }
    // Mobility_T
    else if (settings.generalWidget.plotType == 3)
    {
        setTitle("Mobility, mu(T)");

        //TODO
        if (settings.additionalParamWidget.inverseAxis) {
            setAxisTitle(QwtAxis::YLeft, "T, K");
            setAxisTitle(QwtAxis::XBottom, "Mobility, TODO");
        }
        else {
            //setAxisScale(QwtAxis::YLeft, 0.0, 1000000.0);

            setAxisTitle(QwtAxis::YLeft, "Mobility, TODO");
            setAxisTitle(QwtAxis::XBottom, "T, K");
        }

        setAxisAutoScale(QwtAxis::XBottom);
        setAxisAutoScale(QwtAxis::YLeft);

    }
    // Concentration_T
    else if (settings.generalWidget.plotType == 4)
    {
        setTitle("Concentration, n(T)");

        if (settings.additionalParamWidget.inverseAxis) {
            setAxisTitle(QwtAxis::YLeft, "T, K");
            setAxisTitle(QwtAxis::XBottom, "Concentration, cm^-3");
        }
        else {
            setAxisTitle(QwtAxis::YLeft, "Concentration, cm^-3");
            setAxisTitle(QwtAxis::XBottom, "T, K");
        }
        setAxisAutoScale(QwtAxis::YLeft);
        setAxisAutoScale(QwtAxis::XBottom);
    }
}

void Plot::overlayPlot(const Settings& settings)
{
    drawAxis(settings);

    QwtPlotItemList curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    int curveCount = settings.currentCurvesParam.size();
    if (lastPlotType != settings.generalWidget.plotType ||
        lastInverseType != settings.additionalParamWidget.inverseAxis)
    {
        while (curveList.size() > 0)
        {
            QwtPlotItem* curve = curveList.takeFirst();
            delete curve;
        }
    }
    lastPlotType = settings.generalWidget.plotType;
    lastInverseType = settings.additionalParamWidget.inverseAxis;

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
