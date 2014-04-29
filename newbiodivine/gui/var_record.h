#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_var_record.h"

class myVarRecord: public QWidget, private Ui::Form
{
  Q_OBJECT
    
public:
    myVarRecord(QWidget *parent = 0);
    void setVar(divine::affine_explicit_system_t *,size_t);
};
 
