/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/


#include "MainWindow.h"
#include <QApplication>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    app.setStyle( "Windows" );
    QIcon icon("icon.ico");
    app.setWindowIcon(icon);
    MainWindow window;
    window.resize( 1200, 800 );
    window.show();

    return app.exec();
}
