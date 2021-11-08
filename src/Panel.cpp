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
    generalParamBoxLayout->addWidget(new QLabel("Material type:"), row, 0);
    generalParamBoxLayout->addWidget(generalWidgetItem.boxMaterialType, row, 1);

    row++;
    generalParamBoxLayout->addWidget(new QLabel("Plot type:"), row, 0);
    generalParamBoxLayout->addWidget(generalWidgetItem.boxPlotType, row, 1);

    // Narrow widget
    QGroupBox* narrowParamBox = new QGroupBox("Narrow parameters");
    QGridLayout* narrowParamBoxLayout = new QGridLayout(narrowParamBox);

    row++;
    narrowParamBoxLayout->addWidget(new QLabel("Temperature, K"), row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.temperature, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(new QLabel("Donor Number"), row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.concentration, row, 1);
    
    row++;
    narrowParamBoxLayout->addWidget(new QLabel("Donor energy, eV"), row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.donorEnergy, row, 1);

    // Additional widget
    QGroupBox* additionalParamBox = new QGroupBox("Additional parameters");
    QGridLayout* additionalParamBoxLayout = new QGridLayout(additionalParamBox);

    row = 0;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.addCurve, row, 0);
    overlayWidgeItem.addCurve->setCheckable(true);

    row++;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.removeCurve, row, 0);
    overlayWidgeItem.removeCurve->setCheckable(true);

    row = 0;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.resetAll, row, 1);
    overlayWidgeItem.resetAll->setCheckable(true);
    
    row++;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.showHide, row, 1);
    overlayWidgeItem.showHide->setCheckable(true);

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
	// 1. Charge type [Electrons , Holes] - check box;
	// 2. Material type [Si, Ge, AsGa]; - position box;
	// 3. Plot type relative to Temperature [Irving curve sigma(Nd), Irving curve pho(Nd), Sigma(T), Mobility(T), Concentration(T)] - position box;

    generalWidgetItem.checkBoxElectrons = new QRadioButton("Electrons");
    generalWidgetItem.checkBoxHoles = new QRadioButton("Holes");

    generalWidgetItem.boxMaterialType = new QComboBox();
    generalWidgetItem.boxMaterialType->addItem("Si", QwtPlot::LeftLegend);
    generalWidgetItem.boxMaterialType->addItem("Ge", QwtPlot::RightLegend);
    generalWidgetItem.boxMaterialType->addItem("AsGa", QwtPlot::BottomLegend);

    generalWidgetItem.boxPlotType = new QComboBox();
    // https://stackoverflow.com/questions/40272566/how-to-print-greek-letter-delta-in-c not working TODO
    generalWidgetItem.boxPlotType->addItem("Irving curve sigma(Nd)", QwtPlot::LeftLegend);
    generalWidgetItem.boxPlotType->addItem("Irving curve pho(Nd)", QwtPlot::RightLegend);
    generalWidgetItem.boxPlotType->addItem("Sigma(T)", QwtPlot::BottomLegend);
    generalWidgetItem.boxPlotType->addItem("Mobility(T)", QwtPlot::BottomLegend);
    generalWidgetItem.boxPlotType->addItem("Concentration(T)", QwtPlot::BottomLegend);

    // Narrow parameters widget;
    // Contains:
    // 1. Temperature value; Range [0, 1500] K;  QDoubleSpinBox
    // 2. Concentration value; Range [10^10 - 10^20];  QDoubleSpinBox
    // 3. Energy value; Range [] TODO

    narrowWidgetItem.temperature = new QDoubleSpinBox();
    narrowWidgetItem.temperature->setRange(0, 1500);
    narrowWidgetItem.temperature->setDecimals(2);
    narrowWidgetItem.temperature->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.concentration = new QDoubleSpinBox();
    narrowWidgetItem.concentration->setRange(pow(10,1), pow(10,10)); //have to multiply to 10^10
    narrowWidgetItem.concentration->setDecimals(0);
    narrowWidgetItem.concentration->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.donorEnergy = new QDoubleSpinBox();
    narrowWidgetItem.donorEnergy->setRange(0, 1);
    narrowWidgetItem.donorEnergy->setDecimals(4);
    narrowWidgetItem.donorEnergy->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    
    // Overlay widget
	// Contains:
	// 1. Overlay one more line; Button;
	// 2. Remove last overlaid line; Button;
	// 3. Clear all line; Button;
    overlayWidgeItem.addCurve = new QPushButton("&Add curve");
    overlayWidgeItem.removeCurve = new QPushButton("&Remove last added curve");
    overlayWidgeItem.resetAll = new QPushButton("&Remove all curve");
    overlayWidgeItem.showHide = new QPushButton("&Show/Hide labels");

}
void Panel::connectWidgets()
{
    connect(generalWidgetItem.checkBoxElectrons,
        SIGNAL(clicked()), SIGNAL(edited()));
    connect(generalWidgetItem.checkBoxHoles,
        SIGNAL(clicked()), SIGNAL(edited()));
    connect(generalWidgetItem.boxMaterialType,
        SIGNAL(currentIndexChanged(int)), SIGNAL(edited()));
    connect(generalWidgetItem.boxPlotType,
    SIGNAL(currentIndexChanged(int)), SIGNAL(edited()));


    connect(narrowWidgetItem.temperature,
        SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.concentration,
        SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.donorEnergy,
    SIGNAL(valueChanged(double)), SIGNAL(edited()));


    connect(overlayWidgeItem.addCurve,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
    connect(overlayWidgeItem.removeCurve,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
	connect(overlayWidgeItem.resetAll,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
	connect(overlayWidgeItem.showHide,
        SIGNAL(clicked(bool)), SIGNAL(edited()));

}
Panel::Panel( QWidget* parent )
    : QWidget( parent )
{
    createWidgets();
    overlayWidgets();
    connectWidgets();
}

void Panel::setSettings(  Settings& settings)
{
    blockSignals( true );

    generalWidgetItem.checkBoxElectrons->setChecked(true);
    generalWidgetItem.checkBoxHoles->setChecked(false);

    generalWidgetItem.boxPlotType->setCurrentIndex( settings.generalWidget.plotType);
    generalWidgetItem.boxMaterialType->setCurrentIndex(settings.generalWidget.materialType);
    narrowWidgetItem.temperature->setValue( settings.narrowWidget.temperature);
    narrowWidgetItem.concentration->setValue( settings.narrowWidget.concentration);
    narrowWidgetItem.donorEnergy->setValue( settings.narrowWidget.donorEnergy);
    
    settings.currentCurvesParam = params;

	blockSignals( false );
}

Settings Panel::settings() 
{
    Settings s;

    auto isCheckedElectrons = generalWidgetItem.checkBoxElectrons->isChecked();
    auto isCheckedHoles = generalWidgetItem.checkBoxHoles->isChecked();

    s.generalWidget.materialType = generalWidgetItem.boxMaterialType->currentIndex();
    s.generalWidget.plotType = generalWidgetItem.boxPlotType->currentIndex();

    s.narrowWidget.type = isCheckedElectrons ? 0 : 1;
    if (lastPlotType != s.generalWidget.plotType || lastCheckType!= s.narrowWidget.type)
    {
        params.clear();
    }
    lastPlotType = s.generalWidget.plotType;
    lastCheckType = s.narrowWidget.type;

    s.narrowWidget.temperature = narrowWidgetItem.temperature->value();
    s.narrowWidget.concentration = narrowWidgetItem.concentration->value();
    s.narrowWidget.donorEnergy = narrowWidgetItem.donorEnergy->value();


	s.narrowWidget.alignment |= Qt::AlignBottom;
    s.narrowWidget.size = 12;
    s.additionalParamWidget.numCurves = 1;
    if (overlayWidgeItem.showHide->isChecked())
    {
        state = !state;
        s.generalWidget.show = state;
    	overlayWidgeItem.showHide->setChecked(false);
    }
    if (overlayWidgeItem.addCurve->isChecked())
    {
        Settings::paramEquation tmp;
        tmp.concentration = narrowWidgetItem.concentration->value();
        tmp.temperature = narrowWidgetItem.temperature->value();
        tmp.donorEnergy = narrowWidgetItem.donorEnergy->value();
        tmp.materialType = generalWidgetItem.boxMaterialType->currentIndex();
        tmp.type = s.narrowWidget.type;
        params.push_back(tmp);
        overlayWidgeItem.addCurve->setChecked(false);

    } else if(overlayWidgeItem.removeCurve->isChecked())
    {
        if (!params.empty()) {
            params.pop_back();
        }

        overlayWidgeItem.removeCurve->setChecked(false);

    } else if(overlayWidgeItem.resetAll->isChecked())
    {
        params.clear();
    	overlayWidgeItem.resetAll->setChecked(false);
    }

	s.currentCurvesParam = params;
    
    return s;
}

#include "moc_Panel.cpp"
