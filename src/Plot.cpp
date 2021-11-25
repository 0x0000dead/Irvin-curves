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
#include <QwtScaleEngine>

Plot::Plot( QWidget* parent )
    : QwtPlot( parent )
    , m_externalLegend( NULL )
    , m_legendItem( NULL )
    , m_isDirty( false )
{
    QwtPlotCanvas* canvas = new QwtPlotCanvas();
    canvas->setFocusIndicator(QwtPlotCanvas::CanvasFocusIndicator);
    canvas->setFocusPolicy(Qt::StrongFocus);
    canvas->setPalette(Qt::black);
    setCanvas(canvas);

    setAutoReplot(false);

    setTitle("Irwin curves, sigma(Nd)");

    // Grid
    QwtPlotGrid* grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->setMajorPen(Qt::gray,0,Qt::DotLine);
    grid->setMinorPen(Qt::darkGray,0, Qt::DotLine);
    grid->attach(this);

    setAxisTitle(QwtAxis::YLeft, "Sigma, 1 / Om * sm");
    setAxisAutoScale(QwtAxis::YLeft);
    setAxisAutoScale(QwtAxis::XBottom);

    setAxisTitle(QwtAxis::XBottom, "Nd, donor count");

}

void Plot::insertCurve(const Settings& settings,bool isRunner)
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

    QwtPlotCurve* curve = new Curve(counter,settings.narrowWidget.type == 0, settings );
	curve->setPen(QColor(colors[7]), 3);
	curve->setPen(QColor(colors[counter % numColors]), 2);
	curve->attach( this );
}

void Plot::drawAxis(const Settings & settings)
{
    QString scaleType = "";
    if (settings.additionalParamWidget.logScale) {
        setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine());
        setAxisScaleEngine(QwtPlot::xBottom, new QwtLogScaleEngine());
        scaleType = "Log scale: ";
    }
    else
    {
        setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine());
        setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine());
        scaleType = "Linear scale: ";
    }
    // Irving curve sigma(Nd)
    if (settings.generalWidget.plotType == 0) {
        setTitle(scaleType + "Irwin curves, sigma(Nd)");

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
        setTitle(scaleType + "Irwin curves, rho(Nd)");

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
        setTitle(scaleType + "Conduction, sigma(T)");

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
        setTitle(scaleType + "Mobility, mu(T)");

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
        setTitle(scaleType + "Concentration, n(T)");
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
            nameForTxt.clear();
            dataForTxt.clear();
        }
    }
    lastPlotType = settings.generalWidget.plotType;
    lastInverseType = settings.additionalParamWidget.inverseAxis;
    if (curveList.empty())
    {
        // always append to the end, we know it's in the end
        QwtPlotCurve* curve = new Curve(-1, settings.narrowWidget.type == 0, settings);
        curve->setPen(QColor("Orange"), 3);
        curve->attach(this);
    }
    else
    {
        delete itemList(QwtPlotItem::Rtti_PlotCurve).takeLast();
        QwtPlotCurve* curve = new Curve(-1, settings.narrowWidget.type == 0, settings);
        curve->setPen(QColor("Orange"), 3);
        curve->attach(this);
    }
    curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
    if (curveList.size() != curveCount + 1)
    {
        while (curveList.size() > curveCount)
        {
            delete itemList(QwtPlotItem::Rtti_PlotCurve).takeLast();
            curveList = itemList(QwtPlotItem::Rtti_PlotCurve);

            QwtPlotItem* curve = curveList.takeLast();
            delete curve;
            nameForTxt.pop_back();
            dataForTxt.pop_back();

            QwtPlotCurve* curve1 = new Curve(-1, settings.narrowWidget.type == 0, settings);
            curve1->setPen(QColor("Orange"), 3);
            curve1->attach(this);
        }
        curveList = itemList(QwtPlotItem::Rtti_PlotCurve);

        for (int i = curveList.size(); i < curveCount + 1; i++)
        {
            delete itemList(QwtPlotItem::Rtti_PlotCurve).takeLast();
            curveList = itemList(QwtPlotItem::Rtti_PlotCurve);
            insertCurve(settings, false);
            nameForTxt.push_back(static_cast<Curve*>(itemList(QwtPlotItem::Rtti_PlotCurve).takeLast())->getNames());
            dataForTxt.push_back(static_cast<Curve*>(itemList(QwtPlotItem::Rtti_PlotCurve).takeLast())->getData());
            QwtPlotCurve* curve = new Curve(-1, settings.narrowWidget.type == 0, settings);

            curve->setPen(QColor("Orange"), 3);
            curve->attach(this);
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

std::vector<std::vector<std::pair<double, double>>> Plot::getTxtData()
{
    return dataForTxt;
}
std::vector<QString> Plot::getTxtName(){
    return nameForTxt;
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
