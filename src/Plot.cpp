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

    setTitle( "Irwin curves" );
    setFooter( "Temperature, K" );

    // Grid
    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
    grid->setMinorPen( Qt::darkGray, 0, Qt::DotLine );
    grid->attach( this );

    // Axis
    setAxisScale(QwtAxis::YLeft, 0.0, 1000.0 );
    setAxisTitle(QwtAxis::YLeft, "Something, P");

    setAxisScale( QwtAxis::XBottom, 0.0, 1000.0 );

}

void Plot::insertCurve(ChargeType type, const Settings& settings)
{
    static int counter = 0;

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
    if (settings.generalWidget.plotType == 0) {

        setAxisScale(QwtAxis::YLeft, 0.0, 2000.0);
        setAxisTitle(QwtAxis::YLeft, "Something, P");

        setAxisScale(QwtAxis::XBottom, 0.0, 2000.0);
    }    if (settings.generalWidget.plotType == 1) {

        setAxisScale(QwtAxis::YLeft, 0.0, 1000.0);
        setAxisTitle(QwtAxis::YLeft, "Something, P");

        setAxisScale(QwtAxis::XBottom, 0.0, 1000.0);
    }
    QwtPlotCurve* curve = new Curve( counter++,type==Electrons,settings );
    curve->setPen( QColor( colors[ counter % numColors ] ), 2 );
    curve->attach( this );
}


void Plot::overlayPlot(ChargeType type, const Settings& settings)
{
    QwtPlotItemList curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    if (curveList.size() != settings.currentCurvesParam.size())
    {
        while (curveList.size() > settings.currentCurvesParam.size())
        {
            QwtPlotItem* curve = curveList.takeFirst();
            delete curve;
        }

        for (int i = curveList.size(); i < settings.currentCurvesParam.size(); i++)
            insertCurve(type, settings);
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

    if ( settings.generalWidget.isElectronsEnabled )
    {
        overlayPlot(Electrons, settings);
    }
    if (settings.generalWidget.isHolesEnabled)
    {
        overlayPlot(Holes, settings);
    }

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
