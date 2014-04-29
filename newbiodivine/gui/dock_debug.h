#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_dock_debug.h"

class myDockDebug: public QDockWidget, private Ui::DockWidget_debug
{
  Q_OBJECT
    
public:
    myDockDebug(QWidget *parent = 0);

private:
};
 
