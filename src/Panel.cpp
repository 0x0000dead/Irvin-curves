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
    narrowParamBoxLayout->addWidget(narrowWidgetItem.showAdvancedParam, row, 0);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[0], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.temperature, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[1], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.concentration, row, 1);
    
    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[2], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.donorEnergy, row, 1);

	row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[3], row, 0);

	row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[4], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedBeginT, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[5], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedEndT, row, 1);

	row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[6], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedStepT, row, 1);

    row++;
	narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[7], row, 0);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[8], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedBeginN, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[9], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedEndN, row, 1);

    row++;
    narrowParamBoxLayout->addWidget(narrowWidgetItem.labels[10], row, 0);
    narrowParamBoxLayout->addWidget(narrowWidgetItem.advancedStepN, row, 1);

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

    row++;
    additionalParamBoxLayout->addWidget(overlayWidgeItem.logScale, row, 0);
    additionalParamBoxLayout->addWidget(overlayWidgeItem.inverseAxis, row, 1);
    
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
    generalWidgetItem.boxPlotType->addItem("Irving curve sigma(Nd)", QwtPlot::LeftLegend);
    generalWidgetItem.boxPlotType->addItem("Irving curve pho(Nd)", QwtPlot::RightLegend);
    generalWidgetItem.boxPlotType->addItem("Sigma(T)", QwtPlot::BottomLegend);
    generalWidgetItem.boxPlotType->addItem("Mobility(T)", QwtPlot::BottomLegend);
    generalWidgetItem.boxPlotType->addItem("Concentration(T)", QwtPlot::BottomLegend);

    // Narrow parameters widget;
    // Contains:
    // 1. Temperature value; Range [0, 1500] K;  QDoubleSpinBox
    // 2. Concentration value; Range [10^10 - 10^20];  QDoubleSpinBox
    // 3. Energy value;
    // 4. Button to show advanced settings: steps, max value, e.t.c

    narrowWidgetItem.showAdvancedParam = new QCheckBox("Show advanced settings");

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
    // Advanced settings
    // Temperature:
    narrowWidgetItem.advancedBeginT = new QDoubleSpinBox();
    narrowWidgetItem.advancedBeginT->setRange(0, 1500);
    narrowWidgetItem.advancedBeginT->setDecimals(1);
    narrowWidgetItem.advancedBeginT->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.advancedEndT = new QDoubleSpinBox();
    narrowWidgetItem.advancedEndT->setRange(0, 1500);
    narrowWidgetItem.advancedEndT->setDecimals(1);
    narrowWidgetItem.advancedEndT->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.advancedStepT = new QDoubleSpinBox();
    narrowWidgetItem.advancedStepT->setRange(1, 500);
    narrowWidgetItem.advancedStepT->setDecimals(1);
    narrowWidgetItem.advancedStepT->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    narrowWidgetItem.labels = {
    	new QLabel("Temperature, K"),
    	new QLabel("Donor count, cm^-3"),
    	new QLabel("Donor energy, eV") ,
        new QLabel("Temperature settings:"),
    	new QLabel("Begin, K"),
		new QLabel("End, K"),
    	new QLabel("Step, K"),
    	new QLabel("Concentration settings:"),
        new QLabel("Begin, cm^-3"),
    	new QLabel("End, cm^-3"),
    	new QLabel("Step, cm^-3")
    };
    // Concentration
    narrowWidgetItem.advancedBeginN = new QDoubleSpinBox();
    narrowWidgetItem.advancedBeginN->setRange(1, 1e10);
    narrowWidgetItem.advancedBeginN->setDecimals(0);
    narrowWidgetItem.advancedBeginN->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.advancedEndN = new QDoubleSpinBox();
    narrowWidgetItem.advancedEndN->setRange(1, 1e10);
    narrowWidgetItem.advancedEndN->setDecimals(0);
    narrowWidgetItem.advancedEndN->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    narrowWidgetItem.advancedStepN = new QDoubleSpinBox();
    narrowWidgetItem.advancedStepN->setRange(1, 1e10);
    narrowWidgetItem.advancedStepN->setDecimals(0);
    narrowWidgetItem.advancedStepN->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    // Overlay widget
	// Contains:
	// 1. Overlay one more line; Button;
	// 2. Remove last overlaid line; Button;
	// 3. Clear all line; Button;
    overlayWidgeItem.addCurve = new QPushButton("&Add curve");
    overlayWidgeItem.removeCurve = new QPushButton("&Remove last added curve");
    overlayWidgeItem.resetAll = new QPushButton("&Remove all curve");
    overlayWidgeItem.showHide = new QPushButton("&Show/Hide labels");

    overlayWidgeItem.logScale = new QCheckBox("Log scale");
    overlayWidgeItem.inverseAxis = new QCheckBox("Inverse axis");

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


    connect(narrowWidgetItem.showAdvancedParam,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
    connect(narrowWidgetItem.temperature,
        SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.concentration,
        SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.donorEnergy,
    SIGNAL(valueChanged(double)), SIGNAL(edited()));

    connect(narrowWidgetItem.advancedBeginT,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.advancedEndT,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));
    connect(narrowWidgetItem.advancedStepT,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));

    connect(narrowWidgetItem.advancedBeginN,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));
	connect(narrowWidgetItem.advancedEndN,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));
	connect(narrowWidgetItem.advancedStepN,
	SIGNAL(valueChanged(double)), SIGNAL(edited()));


    connect(overlayWidgeItem.addCurve,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
    connect(overlayWidgeItem.removeCurve,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
	connect(overlayWidgeItem.resetAll,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
	connect(overlayWidgeItem.showHide,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
	connect(overlayWidgeItem.logScale,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
    connect(overlayWidgeItem.inverseAxis,
        SIGNAL(clicked(bool)), SIGNAL(edited()));
}

Panel::Panel( QWidget* parent )
    : QWidget( parent )
{
    createWidgets();
    overlayWidgets();
    connectWidgets();
}

void Panel::hideAdvanced(Settings & s,bool isHide)
{
    if (isHide) {
        narrowWidgetItem.advancedBeginN->hide();
        narrowWidgetItem.advancedEndN->hide();
        narrowWidgetItem.advancedStepN->hide();

        narrowWidgetItem.advancedBeginT->hide();
        narrowWidgetItem.advancedEndT->hide();
        narrowWidgetItem.advancedStepT->hide();

        for (int i = 3; i < narrowWidgetItem.labels.size(); ++i)
        {
            narrowWidgetItem.labels[i]->hide();
        }
    } else
    {
        // Irving curve
        if( s.generalWidget.plotType == 0 ||
            s.generalWidget.plotType == 1)
        {
            narrowWidgetItem.advancedBeginT->hide();
            narrowWidgetItem.advancedEndT->hide();
            narrowWidgetItem.advancedStepT->hide();
            for (int i = 3; i < narrowWidgetItem.labels.size() - 4; ++i)
            {
                narrowWidgetItem.labels[i]->hide();
            }

            narrowWidgetItem.advancedBeginN->show();
            narrowWidgetItem.advancedEndN->show();
            narrowWidgetItem.advancedStepN->show();
            for (int i = narrowWidgetItem.labels.size() - 4; i < narrowWidgetItem.labels.size(); ++i)
            {
                narrowWidgetItem.labels[i]->show();
            }
        }
        // Sigma_T or Mobility_T
        if( s.generalWidget.plotType == 2 ||
            s.generalWidget.plotType == 3 || 
			s.generalWidget.plotType == 4)
        {
            narrowWidgetItem.advancedBeginN->hide();
            narrowWidgetItem.advancedEndN->hide();
            narrowWidgetItem.advancedStepN->hide();

            narrowWidgetItem.advancedBeginT->show();
            narrowWidgetItem.advancedEndT->show();
            narrowWidgetItem.advancedStepT->show();
            for (int i = 3; i < narrowWidgetItem.labels.size() - 4; ++i)
            {
                narrowWidgetItem.labels[i]->show();
            }
            for (int i = narrowWidgetItem.labels.size() - 4; i < narrowWidgetItem.labels.size();++i)
            {
                narrowWidgetItem.labels[i]->hide();
            }
        }
    }
}
void Panel::setSettings(Settings& settings)
{
    blockSignals( true );

    generalWidgetItem.checkBoxElectrons->setChecked(true);
    generalWidgetItem.checkBoxHoles->setChecked(false);
    generalWidgetItem.boxPlotType->setCurrentIndex(settings.generalWidget.plotType);
    generalWidgetItem.boxMaterialType->setCurrentIndex(settings.generalWidget.materialType);

	narrowWidgetItem.temperature->setValue(settings.narrowWidget.temperature);
    narrowWidgetItem.concentration->setValue(settings.narrowWidget.concentration);
    narrowWidgetItem.donorEnergy->setValue(settings.narrowWidget.donorEnergy);
	narrowWidgetItem.showAdvancedParam->setChecked(false);

	narrowWidgetItem.advancedBeginN->setValue(settings.narrowWidget.advancedBeginN);
	narrowWidgetItem.advancedEndN->setValue(settings.narrowWidget.advancedEndN);
	narrowWidgetItem.advancedStepN->setValue(settings.narrowWidget.advancedStepN);
    
	narrowWidgetItem.advancedBeginT->setValue(settings.narrowWidget.advancedBeginT);
	narrowWidgetItem.advancedEndT->setValue(settings.narrowWidget.advancedEndT);
	narrowWidgetItem.advancedStepT->setValue(settings.narrowWidget.advancedStepT);

    hideAdvanced(settings,true);

	overlayWidgeItem.inverseAxis->setChecked(false);
    overlayWidgeItem.inverseAxis->setChecked(false);

    settings.currentCurvesParam = params;

	blockSignals( false );
}

Settings Panel::settings() 
{
    Settings s;
    s.additionalParamWidget.inverseAxis = overlayWidgeItem.inverseAxis->isChecked();
    s.additionalParamWidget.logScale = overlayWidgeItem.logScale->isChecked();

    s.generalWidget.materialType = generalWidgetItem.boxMaterialType->currentIndex();
    s.generalWidget.plotType = generalWidgetItem.boxPlotType->currentIndex();

    s.narrowWidget.type = generalWidgetItem.checkBoxElectrons->isChecked() ? 0 : 1;
    s.narrowWidget.temperature = narrowWidgetItem.temperature->value();
    s.narrowWidget.concentration = narrowWidgetItem.concentration->value();
    s.narrowWidget.donorEnergy = narrowWidgetItem.donorEnergy->value();

    s.narrowWidget.advancedBeginN = narrowWidgetItem.advancedBeginN->value();
    s.narrowWidget.advancedEndN = narrowWidgetItem.advancedEndN->value();
	s.narrowWidget.advancedStepN = narrowWidgetItem.advancedStepN->value();
    s.narrowWidget.advancedBeginT = narrowWidgetItem.advancedBeginT->value();
    s.narrowWidget.advancedEndT = narrowWidgetItem.advancedEndT->value();
    s.narrowWidget.advancedStepT = narrowWidgetItem.advancedStepT->value();
    //Irving curve
    if(s.generalWidget.plotType == 0 || s.generalWidget.plotType == 1)
    {
        narrowWidgetItem.labels[0]->show();
        narrowWidgetItem.temperature->show();

        narrowWidgetItem.labels[1]->hide();
        narrowWidgetItem.concentration->hide();

        narrowWidgetItem.labels[2]->show();
        narrowWidgetItem.donorEnergy->show();

    }
    // Sigma_T or Mobility_T or Concentration_T
	else if(s.generalWidget.plotType == 2 ||
        s.generalWidget.plotType == 3 ||
        s.generalWidget.plotType == 4)
    {
        narrowWidgetItem.labels[0]->hide();
        narrowWidgetItem.temperature->hide();

        narrowWidgetItem.labels[1]->show();
        narrowWidgetItem.concentration->show();

        narrowWidgetItem.labels[2]->show();
        narrowWidgetItem.donorEnergy->show();
    }
    hideAdvanced(s,!narrowWidgetItem.showAdvancedParam->isChecked());
    // reset all data if changed type
    if (lastPlotType != s.generalWidget.plotType ||
        lastCheckType != s.narrowWidget.type ||
		lastInverseType != s.additionalParamWidget.inverseAxis)
    {
        params.clear();

    }
    lastPlotType = s.generalWidget.plotType;
    lastCheckType = s.narrowWidget.type;
    lastInverseType = s.additionalParamWidget.inverseAxis;
    // show/hide labels of curve
    if (overlayWidgeItem.showHide->isChecked())
    {
        stateShowHide = !stateShowHide;
        s.generalWidget.show = stateShowHide;
    	overlayWidgeItem.showHide->setChecked(false);
    }
    // add/remove/reset curve
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
    s.narrowWidget.alignment |= Qt::AlignBottom;
    s.narrowWidget.size = 12;

	s.currentCurvesParam = params;

    s.runner.concentration = s.narrowWidget.concentration;
    s.runner.temperature = s.narrowWidget.temperature;
    s.runner.donorEnergy = s.narrowWidget.donorEnergy;
    s.runner.materialType = s.generalWidget.materialType;
    s.runner.type = s.narrowWidget.type;

	return s;
}

#include "moc_Panel.cpp"
