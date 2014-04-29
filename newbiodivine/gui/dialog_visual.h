#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_dialog_visual.h"

class myDialogNewVisual: public QDialog, public Ui::DialogNewVisual
{
  Q_OBJECT
    
public:
    myDialogNewVisual(QWidget *parent = 0);

private:
};
 
