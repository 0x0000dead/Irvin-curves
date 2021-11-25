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

        narrowWidget.temperature = 300;
        narrowWidget.concentration = 1e8;
        narrowWidget.donorEnergy = 0.045;
        narrowWidget.type = 0; // 0 - electron only, 1 - holes only
        narrowWidget.size = 2;
        narrowWidget.showAdvancedParam = false;

        narrowWidget.advancedBeginN = 1; // * 1e10
        narrowWidget.advancedEndN = 1e10; // * 1e10
        narrowWidget.advancedStepN = 1e8; // * 1e10

        narrowWidget.advancedBeginT = 100.0;
        narrowWidget.advancedEndT = 400.0;
        narrowWidget.advancedStepT = 10.0;

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
        double concentration;
        double donorEnergy;
        int type;

        int backgroundMode;
        int numColumns;
        int alignment;
        int size;


        double advancedBeginT;
        double advancedEndT;
        double advancedStepT;

        double advancedBeginN;
        double advancedEndN;
        double advancedStepN;

        bool showAdvancedParam;
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
    Settings::paramEquation runner;
    bool isShow = true;
};
