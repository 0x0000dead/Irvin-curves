/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#pragma once

#include <QMainWindow>

class Plot;
class Panel;
class QwtPlotPicker;
class QwtPlotZoomer;
class QwtPlotPanner;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow( QWidget* parent = 0 );

  private Q_SLOTS:
    void updatePlot();
    void exportPlot();
    void moved(const QPoint&);
    void selected(const QPolygon&);
    void enableZoomMode(bool);

  private:
    Plot* m_plot;
    Panel* m_panel;
    QwtPlotPicker* m_picker;
    QwtPlotZoomer* m_zoomer[2];
    QwtPlotPanner* m_panner;

    void showInfo(QString text = QString());

};
