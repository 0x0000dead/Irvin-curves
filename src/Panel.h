/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#pragma once

#include "Settings.h"
#include <QWidget>
#include <QPushButton>

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
        QCheckBox* checkBoxElectrons;
        QCheckBox* checkBoxHoles;

        QComboBox* boxMaterialType;
        QComboBox* boxPlotType;

    } generalWidgetItem;

    struct
    {
        QSpinBox* temperature;
        QSpinBox* concentration;

    } narrowWidgetItem;

    struct
    {
        QPushButton* addCurve;
        QPushButton* removeCurve;
        QPushButton* resetAll;

    } overlayWidgeItem;

    void createWidgets();
    void overlayWidgets();
    void connectWidgets();

    std::vector<Settings::paramEquation> params;

    int currentCurveCount;
};
