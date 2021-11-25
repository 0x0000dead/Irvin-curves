#include "Curve.h"
#include <QwtPlotCurve>
#include <QwtPlotLegendItem>
#include <QwtLegend>
#include <QwtPlotCanvas>
#include <QwtPlotGrid>
#include <QwtPlotLayout>
#include <QwtMath>
#include "Legend.h"
#include <QPen>

#include "Phys_plot.h"


Curve::Curve(int index, int isElectron,  const Settings& settings) : m_index(index), _isElectron(isElectron), _settings(settings)
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    std::vector<std::pair<double, double>> result;
    // Main settings
	phfm::Material_base materialType = phfm::Materials.Si;
    double temperature;
    double donorEnergy;
    double concentration;

	if (index == -1)
    {
        temperature = _settings.runner.temperature;
        concentration = _settings.runner.concentration * 1e10;
        donorEnergy = _settings.runner.donorEnergy;
    } else
    {
        temperature = _settings.currentCurvesParam[index].temperature;
        donorEnergy = _settings.currentCurvesParam[index].donorEnergy;
        concentration = _settings.currentCurvesParam[index].concentration * 1e10;
    }
    
    // Advanced settings
    double beginConcentration = _settings.narrowWidget.advancedBeginN * 1e10; // 1 * 1e10
    double endConcentration = _settings.narrowWidget.advancedEndN * 1e10; // 1e8 * 1e10
    double stepConcentration = _settings.narrowWidget.advancedStepN * 1e10; // 1e10 * 1e10

    double beginTemperature = _settings.narrowWidget.advancedBeginT;
    double endTemperature = _settings.narrowWidget.advancedEndT;
    double stepTemperature = _settings.narrowWidget.advancedStepT;

    auto fome = new phfm::Phys_plot();

    if (_settings.generalWidget.materialType == 1)
    {
        materialType = phfm::Materials.Ge;
    }
    else if(_settings.generalWidget.materialType == 2)
    {
        materialType = phfm::Materials.GaAs;
    }
    // Irving curve sigma(Nd)
    if (_settings.generalWidget.plotType == 0)
    {
        result = fome->sigma_ndo(materialType, temperature, donorEnergy,
            beginConcentration, endConcentration, stepConcentration);
    }
    // Irving curve rho(Nd)
    else if (_settings.generalWidget.plotType == 1)
    {
        result = fome->rho_ndo(materialType, temperature, donorEnergy,
            beginConcentration, endConcentration, stepConcentration);
    }
    // Sigma_T
    else if (_settings.generalWidget.plotType == 2)
    {
        result = fome->sigma_T(materialType, donorEnergy, beginTemperature, endTemperature, stepTemperature, concentration);
    }
    // Mobility_T
    else if (_settings.generalWidget.plotType == 3)
    {
        if(isElectron)
        {
            result = fome->mu_e_T(materialType, donorEnergy,
                beginTemperature, endTemperature, stepTemperature, 
                concentration);
        } else
        {
            result = fome->mu_p_T(materialType, donorEnergy, 
                beginTemperature, endTemperature, stepTemperature,
                concentration);
        }
    }
    // Concentration_T
    else if (_settings.generalWidget.plotType == 4)
    {
        if (isElectron)
        {
            result = fome->p_T(materialType, donorEnergy,
                beginTemperature, endTemperature, stepTemperature, 
                concentration );
        }
        else
        {
            result = fome->n_T(materialType, donorEnergy,
                beginTemperature, endTemperature, stepTemperature,
                concentration);
        }
    }
    delete fome;

    QVector< QPointF > points;
	for (auto& t : result)
    {
        if (_settings.additionalParamWidget.inverseAxis) {
            std::swap(t.first, t.second);
        }
		points += QPointF(t.first, t.second);
    }
    if(_settings.additionalParamWidget.logScale)
    {
        setBaseline(1);
    }
    setSamples(points);
}


void Curve::setCurveTitle(const QString& title)
{
    QString txt("%1 %2");
    double temperature;
    double donorEnergy;
    double concentration;
    QString type;
    int typeMat;

    if (m_index == -1)
    {
        temperature = _settings.runner.temperature;
        concentration = _settings.runner.concentration * 1e10;
        donorEnergy = _settings.runner.donorEnergy;
        type = _settings.runner.type == 0 ? "Electron" : "Holes";
        typeMat = _settings.runner.materialType;
    }
    else {
        temperature = _settings.currentCurvesParam[m_index].temperature;
        concentration = _settings.currentCurvesParam[m_index].concentration * 1e10;
        donorEnergy = _settings.currentCurvesParam[m_index].donorEnergy;
        type = _settings.currentCurvesParam[m_index].type == 0 ? "Electron" : "Holes";
        typeMat = _settings.currentCurvesParam[m_index].materialType;
    }

    QString material = "";
    if (typeMat == 0)
    {
        material = "Si";
    }
    else if(typeMat == 1)
    {
        material = "Ge";

    } else
    {
        material = "AsGa";
    }
    setTitle(QString("Number=%1;T=%2;C=%3;E=%4;" + type + ";Mat=" + material).arg(m_index).arg(temperature).arg(concentration).arg(donorEnergy));
};
