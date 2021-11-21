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
        narrowWidget.type = 0; // 0 - electron only, 1 - holes only
        narrowWidget.size = 2;

        additionalParamWidget.inverseAxis = false;
        additionalParamWidget.logScale = false;
        additionalParamWidget.title = "";

        generalWidget.show = true;
    }
    
    struct
    {
        bool isElectronsEnabled;
        bool isHolesEnabled;
        int materialType;
        int plotType;
        bool show;
    } generalWidget;

    struct
    {
        double temperature;
        double concentration; // aka donorCount
        double donorEnergy;
        int type;

        int backgroundMode;
        int numColumns;
        int alignment;
        int size;
    } narrowWidget;

    struct
    {
        int numCurves;
        QString title;
        bool logScale;
        bool inverseAxis;
    } additionalParamWidget;

    struct paramEquation
    {
        double temperature;
        double concentration;
        double donorEnergy;
        int materialType;
        int type;
    };

    std::vector<Settings::paramEquation> currentCurvesParam;
    bool isShow = true;;
};
