/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#pragma once

#include <QString>
#include <vector>

class Settings
{
  public:

    Settings()
    {
        generalWidget.isElectronsEnabled = true;
        generalWidget.isHolesEnabled = false;
        generalWidget.materialType = 0;
        generalWidget.plotType = 0;

        narrowWidget.temperature = 1;
        narrowWidget.concentration = 0;
        narrowWidget.donorEnergy = 0.045;

        additionalParamWidget.numCurves = 1;
        additionalParamWidget.title = "Curve";
    }
    
    struct
    {
        bool isElectronsEnabled;
        bool isHolesEnabled;
        int materialType;
        int plotType;
    } generalWidget;

    struct
    {
        double temperature;
        double concentration; // aka donorCount
        double donorEnergy;

        int backgroundMode;
        int numColumns;
        int alignment;
        int size;
    } narrowWidget;

    struct
    {
        int numCurves;
        QString title;
    } additionalParamWidget;

    struct paramEquation
    {
        double temperature;
        double concentration;
        double donorEnergy;
        int materialType;
    };

    std::vector<Settings::paramEquation> currentCurvesParam;
    std::vector<Settings::paramEquation> currentCurvesParamExtended;
};
