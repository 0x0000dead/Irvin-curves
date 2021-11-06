/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "Panel.h"
#include "Settings.h"

#include <QwtPlot>
#include <QwtPlotLegendItem>

#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>

Panel::Panel( QWidget* parent )
    : QWidget( parent )
{
    // Widget creation

    // General parameters widget;
    // Contains:
    // 1. Charge type [Elecntros , Holes] - check box;
    // 2. Material type [Si, Ge, AsGa]; - position box;
    // 3. Plot type relative to Temperature [Conductivity(T), Mobility(T), Concentration(T)] - position box;

    generalWidgetItem.checkBoxElectrons = new QCheckBox( "Electrons");
    generalWidgetItem.checkBoxHoles = new QCheckBox( "Holes");
    
    generalWidgetItem.positionBoxMaterialType = new QComboBox();
    generalWidgetItem.positionBoxMaterialType->addItem( "Si", QwtPlot::LeftLegend );
    generalWidgetItem.positionBoxMaterialType->addItem( "Ge", QwtPlot::RightLegend );
    generalWidgetItem.positionBoxMaterialType->addItem( "AsGa", QwtPlot::BottomLegend );

    generalWidgetItem.positionBoxPlotType = new QComboBox();
    generalWidgetItem.positionBoxPlotType->addItem("Conductivity", QwtPlot::LeftLegend);
    generalWidgetItem.positionBoxPlotType->addItem("Mobility", QwtPlot::RightLegend);
    generalWidgetItem.positionBoxPlotType->addItem("Concentration", QwtPlot::BottomLegend);

    // Narrow parameters widget;
    // Contains:
    // 1. Temperature value; Range [0, 1500] K; QSpinBox or QDoubleSpinBox
    // 2. Concentration value; Range []; QSpinBox or QDoubleSpinBox
    // TODO + config file for range?

    narrowWidgetItem.temperature = new QSpinBox();
    narrowWidgetItem.temperature->setRange( 0, 1500 );

    narrowWidgetItem.concentration = new QSpinBox();
    narrowWidgetItem.concentration->setRange( 2, 22 );

    // Overlay widget
    // Contains:
    // 1. Overlay one more line; Button;
    // 2. Remove last overlaid line; Button;
    // 3. Clear all line; Button;
    overlayWidgeItem.numCurves = new QSpinBox();
    overlayWidgeItem.numCurves->setRange( 0, 99 );

    overlayWidgeItem.title = new QLineEdit();

    // layout

    QGroupBox* legendBox = new QGroupBox( "General parameters" );
    QGridLayout* legendBoxLayout = new QGridLayout( legendBox );

    int row = 0;
    legendBoxLayout->addWidget( generalWidgetItem.checkBoxElectrons, row, 0, 1, -1 );
    legendBoxLayout->addWidget( generalWidgetItem.checkBoxHoles, row, 1, 1, -1 );

    row++;
    legendBoxLayout->addWidget(new QLabel("Material type"), row, 0);
    legendBoxLayout->addWidget(generalWidgetItem.positionBoxMaterialType, row, 1);

    row++;
    legendBoxLayout->addWidget( new QLabel( "Plot type" ), row, 0 );
    legendBoxLayout->addWidget( generalWidgetItem.positionBoxPlotType, row, 1 );


    QGroupBox* legendItemBox = new QGroupBox( "Narrow parameters" );
    QGridLayout* legendItemBoxLayout = new QGridLayout( legendItemBox );


    row++;
    legendItemBoxLayout->addWidget( new QLabel( "Temperature" ), row, 0 );
    legendItemBoxLayout->addWidget( narrowWidgetItem.temperature, row, 1 );


    row++;
    legendItemBoxLayout->addWidget( new QLabel( "Concentration" ), row, 0 );
    legendItemBoxLayout->addWidget( narrowWidgetItem.concentration, row, 1 );

    QGroupBox* curveBox = new QGroupBox( "Additional parameters" );
    QGridLayout* curveBoxLayout = new QGridLayout( curveBox );

    row = 0;
    curveBoxLayout->addWidget( new QLabel( "Number" ), row, 0 );
    curveBoxLayout->addWidget( overlayWidgeItem.numCurves, row, 1 );

    row++;
    curveBoxLayout->addWidget( new QLabel( "Title" ), row, 0 );
    curveBoxLayout->addWidget( overlayWidgeItem.title, row, 1 );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->addWidget( legendBox );
    layout->addWidget( legendItemBox );
    layout->addWidget( curveBox );
    layout->addStretch( 10 );

    connect( generalWidgetItem.checkBoxElectrons,
        SIGNAL(stateChanged(int)), SIGNAL(edited()) );
    connect( generalWidgetItem.checkBoxHoles,
        SIGNAL(stateChanged(int)), SIGNAL(edited()) );
    connect( generalWidgetItem.positionBoxMaterialType,
        SIGNAL(currentIndexChanged(int)), SIGNAL(edited()) );

    connect( narrowWidgetItem.temperature,
        SIGNAL(valueChanged(int)), SIGNAL(edited()) );


    connect( overlayWidgeItem.numCurves,
        SIGNAL(valueChanged(int)), SIGNAL(edited()) );
    connect( narrowWidgetItem.concentration,
        SIGNAL(valueChanged(int)), SIGNAL(edited()) );
    connect( overlayWidgeItem.title,
        SIGNAL(textEdited(const QString&)), SIGNAL(edited()) );
}

void Panel::setSettings( const Settings& settings)
{
    blockSignals( true );

    generalWidgetItem.checkBoxElectrons->setCheckState(
        settings.legend.isEnabled ? Qt::Checked : Qt::Unchecked );
    generalWidgetItem.positionBoxMaterialType->setCurrentIndex( settings.legend.position );

    narrowWidgetItem.temperature->setValue( settings.legendItem.numColumns );



    narrowWidgetItem.concentration->setValue( settings.legendItem.size );

    overlayWidgeItem.numCurves->setValue( settings.curve.numCurves );
    overlayWidgeItem.title->setText( settings.curve.title );

    blockSignals( false );
}

Settings Panel::settings() const
{
    Settings s;

    s.legend.isEnabled =
        generalWidgetItem.checkBoxElectrons->checkState() == Qt::Checked;
    s.legend.position = generalWidgetItem.positionBoxMaterialType->currentIndex();


    s.legendItem.numColumns = narrowWidgetItem.temperature->value();

    int align = 0;


    s.legendItem.alignment = align;

    s.legendItem.size = narrowWidgetItem.concentration->value();

    s.curve.numCurves = overlayWidgeItem.numCurves->value();
    s.curve.title = overlayWidgeItem.title->text();

    return s;
}

#include "moc_Panel.cpp"
