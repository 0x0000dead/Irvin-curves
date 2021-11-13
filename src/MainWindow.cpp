/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "Plot.h"
#include "Panel.h"
#include "MainWindow.h"
#include "Zoomer.h"
#include "Pixmaps.h"

#include <iostream>

#include <QwtPickerMachine>
#include <QwtPlotZoomer>
#include <QwtPlotRenderer>

#include <QToolBar>
#include <QToolButton>
#include <QLayout>
#include <QStatusBar>
#include <QPrinter>
#include <QPen>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
{
    m_plot = new Plot();

    Settings settings;
    settings.generalWidget.isElectronsEnabled = true;

    settings.narrowWidget.numColumns = 1;
    settings.narrowWidget.alignment = Qt::AlignRight | Qt::AlignVCenter;
    settings.narrowWidget.backgroundMode = 0;
    settings.narrowWidget.size = m_plot->canvas()->font().pointSize();

    settings.additionalParamWidget.numCurves = 4;
    settings.additionalParamWidget.title = "Curve";

    m_panel = new Panel();
    m_panel->setSettings( settings );

    QWidget* box = new QWidget( this );
    QHBoxLayout* layout = new QHBoxLayout( box );
    layout->addWidget( m_plot, 10 );
    layout->addWidget( m_panel );

    setCentralWidget( box );

    QToolBar* toolBar = new QToolBar( this );

    QToolButton* btnExport = new QToolButton( toolBar );

    btnExport->setText( "Export" );
    btnExport->setIcon(QPixmap(print_xpm));
    btnExport->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolBar->addWidget( btnExport );

    addToolBar( toolBar );

    updatePlot();
    //

    m_panner = new QwtPlotPanner(m_plot->canvas());
    m_panner->setMouseButton(Qt::MiddleButton);

    //
    m_picker = new QwtPlotPicker(QwtAxis::XBottom, QwtAxis::YLeft,
        QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
        m_plot->canvas());
    m_picker->setStateMachine(new QwtPickerDragPointMachine());
    m_picker->setRubberBandPen(QColor(Qt::green));
    m_picker->setRubberBand(QwtPicker::CrossRubberBand);
    m_picker->setTrackerPen(QColor(Qt::white));
    //

	m_zoomer[0] = new Zoomer(QwtAxis::XBottom, QwtAxis::YLeft,
        m_plot->canvas());
    m_zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
    m_zoomer[0]->setRubberBandPen(QColor(Qt::green));
    m_zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
    m_zoomer[0]->setTrackerPen(QColor(Qt::white));

    m_zoomer[1] = new Zoomer(
        QwtAxis::XTop, QwtAxis::YRight, m_plot->canvas());



    //
   QToolButton* btnZoom = new QToolButton(toolBar);
    btnZoom->setText("Zoom");
    btnZoom->setIcon(QPixmap(zoom_xpm));
    btnZoom->setCheckable(true);
    btnZoom->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addWidget(btnZoom);

	enableZoomMode(false);
   showInfo();
        connect(btnZoom, SIGNAL(toggled(bool)), SLOT(enableZoomMode(bool)));

    connect( m_panel, SIGNAL(edited()), SLOT(updatePlot()) );
    connect( btnExport, SIGNAL(clicked()), SLOT(exportPlot()) );

	connect(m_picker, SIGNAL(moved(const QPoint&)),
        SLOT(moved(const QPoint&)));
    connect(m_picker, SIGNAL(selected(const QPolygon&)),
        SLOT(selected(const QPolygon&)));
}

void MainWindow::enableZoomMode(bool on)
{
    m_panner->setEnabled(on);

    m_zoomer[0]->setEnabled(on);
    m_zoomer[0]->zoom(0);

    m_zoomer[1]->setEnabled(on);
    m_zoomer[1]->zoom(0);

    m_picker->setEnabled(!on);
    updatePlot();
    showInfo();
}

void MainWindow::updatePlot()
{
    m_plot->applySettings( m_panel->settings() );
}
void MainWindow::selected(const QPolygon&)
{
    showInfo();
}

void MainWindow::showInfo(QString text)
{
    if (text.isEmpty())
    {
        if (m_picker->rubberBand())
            text = "Cursor Pos: Press left mouse button in plot region";
        else
            text = "Zoom: Press mouse button and drag";
    }

#ifndef QT_NO_STATUSBAR
    statusBar()->showMessage(text);
#endif
}
void MainWindow::moved(const QPoint& pos)
{
    using namespace QwtAxis;

    QString info("X=%1, Y=%2, Phase=%3");
    info = info.arg(m_plot->invTransform(XBottom, pos.x()));
    info = info.arg(m_plot->invTransform(YLeft, pos.y()));

    showInfo(info);
}

void MainWindow::exportPlot()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( m_plot, "irwinCurve.pdf" );
}

#include "moc_MainWindow.cpp"
