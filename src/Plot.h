/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#pragma once

#include <QwtPlot>

class QwtPlotLegendItem;
class QwtLegend;
class Settings;
class Plot : public QwtPlot
{
    Q_OBJECT

  public:
    Plot( QWidget* parent = NULL );
    std::vector<std::vector<std::pair<double, double>>> getTxtData();
    std::vector<QString> getTxtName();
	virtual ~Plot();

  public Q_SLOTS:
    void applySettings( const Settings& );

  public:
    virtual void replot() QWT_OVERRIDE;

  private:

    void insertCurve(const Settings& settings, bool isRunner);
	void overlayPlot(const Settings& settings);
    void drawAxis(const Settings& settings);
    
    int lastPlotType = 0;
    bool lastInverseType = false;
    bool m_isDirty;

    std::vector<std::vector<std::pair<double, double>>> dataForTxt;
    std::vector<QString> nameForTxt;

	QwtLegend* m_externalLegend;
    QwtPlotLegendItem* m_legendItem;
    

};
