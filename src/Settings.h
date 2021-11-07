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

        narrowWidget.temperature = 0;
        narrowWidget.concentration = 0;

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
        int temperature;
        int concentration;

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
        int temperature;
        int concentration;
        int materialType;
    };

    std::vector<Settings::paramEquation> currentCurvesParam;
};
