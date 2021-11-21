/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#pragma once

#include "Settings.h"
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <qspinbox.h>

class QCheckBox;
class QComboBox;
class QSpinBox;
class QLineEdit;

class Panel : public QWidget
{
    Q_OBJECT

  public:
    Panel( QWidget* parent = NULL );

    void setSettings(  Settings&);
    Settings settings() ;

  Q_SIGNALS:
    void edited();

  private:
    struct
    {
        QRadioButton* checkBoxElectrons;
        QRadioButton* checkBoxHoles;

        QComboBox* boxMaterialType;
        QComboBox* boxPlotType;

    } generalWidgetItem;

    struct
    {
        QDoubleSpinBox* temperature;
        QDoubleSpinBox* concentration;
        QDoubleSpinBox* donorEnergy;

    } narrowWidgetItem;

    struct
    {
        QPushButton* addCurve;
        QPushButton* removeCurve;
        QPushButton* resetAll;
        QPushButton* showHide;
        QCheckBox* inverseAxis;
        QCheckBox* logScale;

    } overlayWidgeItem;

    void createWidgets();
    void overlayWidgets();
    void connectWidgets();

    std::vector<Settings::paramEquation> params;

    int currentCurveCount;
    int lastPlotType = 0;
    bool lastInverseType = 0;
    int lastCheckType = 0;
    bool state = true;
};
