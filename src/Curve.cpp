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
            result = fome->sigma_ndo(materialType, temperature, concentration, donorEnergy);
        } else
        {
            result = { {1.0,1.0} ,{555.0,555.0} };
        }
    }
    // Irving curve rho(Nd)
    else if (_settings.generalWidget.plotType == 1)
    {
        if (isWorkMode) {
            result = fome->rho_ndo(materialType, temperature, concentration, donorEnergy);
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
    setTitle(QString("%1  %2").arg(title).arg(m_index));
}
