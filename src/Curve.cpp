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
    bool isWorkMode = true;

    setRenderHint(QwtPlotItem::RenderAntialiased);
    std::vector<std::pair<double, double>> result;
    phfm::Material_base materialType = phfm::Materials.Si;
    double temperature = _settings.currentCurvesParam[index].temperature;
    double concentration = _settings.currentCurvesParam[index].concentration * pow(10, 10);
    double donorEnergy = _settings.currentCurvesParam[index].donorEnergy;
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
        if (isWorkMode) {
            result = fome->sigma_ndo(materialType, temperature, 10000000.0, donorEnergy);
        } else
        {
            result = { {1.0,1.0} ,{555.0,555.0} };
        }
    }
    // Irving curve rho(Nd)
    else if (_settings.generalWidget.plotType == 1)
    {
        if (isWorkMode) {
            result = fome->rho_ndo(materialType, temperature, 1000.0, donorEnergy);
        }
        else
        {
            result = { {1.0,1.0} ,{555.0,555.0} };
        }
    }
    // Sigma_T
    else if (_settings.generalWidget.plotType == 2)
    {
        if (isWorkMode) {
            result = fome->sigma_T(materialType, concentration,0.0,temperature,1.0, donorEnergy);
        }
        else
        {
            result = { {1.0,1.0} ,{555.0,555.0} };
        }
    }
    // Mobility_T
    else if (_settings.generalWidget.plotType == 3)
    {
        if (isWorkMode) {
            if(isElectron)
            {
                result = fome->mu_e_T(materialType, concentration, donorEnergy, 0.0, temperature, 0.0);
            } else
            {
                result = fome->mu_p_T(materialType, concentration, donorEnergy, 0.0, temperature, 0.0);
            }
        }
        else
        {
            result = { {1.0,1.0} ,{555.0,555.0} };
        }
    }
    // Concentration_T// TODO is p_T electron?
    else if (_settings.generalWidget.plotType == 4)
    {
        if (isWorkMode) {
            if (isElectron)
            {
                result = fome->p_T(materialType, concentration, 0.0, temperature, 1.0, donorEnergy);
            }
            else
            {
                result = fome->n_T(materialType, concentration, 0.0, temperature, 1.0, donorEnergy);
            }
        }
        else
        {
            result = { {1.0, 1.0} ,{555.0,555.0} };
        }
    }
    delete fome;

    QVector< QPointF > points;
    double y = qwtRand() % 10000;
    if (isWorkMode)
    {
        y = 0;
    }
    for (const auto t : result)
    {
        points += QPointF(t.first+2*y, t.second + y);
    }

    setSamples(points);
}


void Curve::setCurveTitle(const QString& title)
{
    QString txt("%1 %2");
    double temperature = _settings.currentCurvesParam[m_index].temperature;
    double concentration = _settings.currentCurvesParam[m_index].concentration * pow(10, 10);
    double donorEnergy = _settings.currentCurvesParam[m_index].donorEnergy;
    QString type = _settings.currentCurvesParam[m_index].type == 0 ? "Electron" : "Holes";
    int typeMat = _settings.currentCurvesParam[m_index].materialType;
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
