/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "Panel.h"

#include <iostream>

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

void Panel::overlayWidgets()
{
    // General Widget
    QGroupBox* generalParamBox = new QGroupBox("General parameters");
    QGridLayout* generalParamBoxLayout = new QGridLayout(generalParamBox);

    int row = 0;
    generalParamBoxLayout->addWidget(generalWidgetItem.checkBoxElectrons, row, 0, 1, -1);
    generalParamBoxLayout->addWidget(generalWidgetItem.checkBoxHoles, row, 1, 1, -1);

    row++;
    generalParamBoxLayout->addWidget(new QLabel("Material type"), row, 0);
    generalParamBoxLayout->addWidget(generalWidgetItem.boxMaterialType, row, 1);

    row++;
    generalParamBoxLayout->addWidget(new QLabel("Plot type (of temperature)"), row, 0);
    generalParamBoxLayout->addWidget(generalWidgetItem.boxPlotType, row, 1);

    // Narrow widget
    QGroupBox* narrowParamBox = new QGroupBox("Narrow parameters");
    QGridLayout* narrowParamBoxLayout = new QGridLayout(narrowParamBox);

    row++;
    narrowParamBoxLayout->addWidget(new QLabel("Temperature"), row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.temperature, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(new QLabel("Concentration"), row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.concentration, row, 1);

    // Additional widget
    QGroupBox* additionalParamBox = new QGroupBox("Additional parameters");
    QGridLayout* additionalParamBoxLayout = new QGridLayout(additionalParamBox);

    row = 0;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.addCurve, row, 0);

    row++;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.removeCurve, row, 0);

    row = 0;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.resetAll, row, 1);

    // Plot widget
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(generalParamBox);
    layout->addWidget(narrowParamBox);
    layout->addWidget(additionalParamBox);
    layout->addStretch(5);

}
void Panel::createWidgets()
{
	// General parameters widget;
	// Contains:
	// 1. Charge type [Elecntros , Holes] - check box;
	// 2. Material type [Si, Ge, AsGa]; - position box;
	// 3. Plot type relative to Temperature [Conductivity(T), Mobility(T), Concentration(T)] - position box;

    generalWidgetItem.checkBoxElectrons = new QCheckBox("Electrons");
    generalWidgetItem.checkBoxHoles = new QCheckBox("Holes");

    generalWidgetItem.boxMaterialType = new QComboBox();
    generalWidgetItem.boxMaterialType->addItem("Si", QwtPlot::LeftLegend);
    generalWidgetItem.boxMaterialType->addItem("Ge", QwtPlot::RightLegend);
    generalWidgetItem.boxMaterialType->addItem("AsGa", QwtPlot::BottomLegend);

    generalWidgetItem.boxPlotType = new QComboBox();
    generalWidgetItem.boxPlotType->addItem("Conductivity", QwtPlot::LeftLegend);
    generalWidgetItem.boxPlotType->addItem("Mobility", QwtPlot::RightLegend);
    generalWidgetItem.boxPlotType->addItem("Concentration", QwtPlot::BottomLegend);

    // Narrow parameters widget;
    // Contains:
    // 1. Temperature value; Range [0, 1500] K; QSpinBox or QDoubleSpinBox
    // 2. Concentration value; Range []; QSpinBox or QDoubleSpinBox
    // TODO + config file for range?

    narrowWidgetItem.temperature = new QSpinBox();
    narrowWidgetItem.temperature->setRange(0, 1500);

    narrowWidgetItem.concentration = new QSpinBox();
    narrowWidgetItem.concentration->setRange(2, 22);

    // Overlay widget
	// Contains:
	// 1. Overlay one more line; Button;
	// 2. Remove last overlaid line; Button;
	// 3. Clear all line; Button;
    overlayWidgeItem.addCurve = new QPushButton("&Add curve");
    overlayWidgeItem.removeCurve = new QPushButton("&Remove last added curve");
    overlayWidgeItem.resetAll = new QPushButton("&Remove all curve");

}
void Panel::connectWidgets()
{
    connect(generalWidgetItem.checkBoxElectrons,
        SIGNAL(stateChanged(int)), SIGNAL(edited()));
    connect(generalWidgetItem.checkBoxHoles,
        SIGNAL(stateChanged(int)), SIGNAL(edited()));
    connect(generalWidgetItem.boxMaterialType,
        SIGNAL(currentIndexChanged(int)), SIGNAL(edited()));
    connect(generalWidgetItem.boxPlotType,
    SIGNAL(currentIndexChanged(int)), SIGNAL(edited()));


    connect(narrowWidgetItem.temperature,
        SIGNAL(valueChanged(int)), SIGNAL(edited()));
    connect(narrowWidgetItem.concentration,
        SIGNAL(valueChanged(int)), SIGNAL(edited()));


    connect(overlayWidgeItem.addCurve,
        SIGNAL(stateChanged(int)), SIGNAL(edited()));
    connect(overlayWidgeItem.removeCurve,
        SIGNAL(stateChanged(int)), SIGNAL(edited()));
	connect(overlayWidgeItem.resetAll,
        SIGNAL(stateChanged(int)), SIGNAL(edited()));
}
Panel::Panel( QWidget* parent )
    : QWidget( parent )
{
    createWidgets();
    overlayWidgets();
    connectWidgets();
}

void Panel::setSettings( const Settings& settings)
{
    blockSignals( true );

    generalWidgetItem.checkBoxElectrons->setCheckState(
        settings.generalWidget.isElectronsEnabled ? Qt::Checked : Qt::Unchecked );
	generalWidgetItem.checkBoxHoles->setCheckState(
        settings.generalWidget.isHolesEnabled ? Qt::Checked : Qt::Unchecked );
    generalWidgetItem.boxMaterialType->setCurrentIndex( settings.generalWidget.materialType );
    generalWidgetItem.boxMaterialType->setCurrentIndex( settings.generalWidget.plotType);

    narrowWidgetItem.temperature->setValue( settings.narrowWidget.temperature);
    narrowWidgetItem.temperature->setValue( settings.narrowWidget.concentration);

    blockSignals( false );
}

Settings Panel::settings() const
{
    Settings s;

    s.generalWidget.isElectronsEnabled =
        generalWidgetItem.checkBoxElectrons->checkState() == Qt::Checked;
    s.generalWidget.isHolesEnabled =
        generalWidgetItem.checkBoxHoles->checkState() == Qt::Checked;
    s.generalWidget.materialType = generalWidgetItem.boxMaterialType->currentIndex();
    s.generalWidget.plotType = generalWidgetItem.boxMaterialType->currentIndex();


    s.narrowWidget.temperature = narrowWidgetItem.temperature->value();
    s.narrowWidget.concentration = narrowWidgetItem.concentration->value();
	s.narrowWidget.alignment = 1;
    s.narrowWidget.size = 12;
    s.additionalParamWidget.numCurves = 1;


    return s;
}

#include "moc_Panel.cpp"
