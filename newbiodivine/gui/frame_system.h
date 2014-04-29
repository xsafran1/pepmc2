#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_frame_system.h"
#include "var_record.h"

class myFrameSystem : public QFrame, private Ui::Frame_System
{
  Q_OBJECT
    
public:
  myFrameSystem(QWidget *parent = 0);
    
public slots:
  void loadVars(divine::affine_explicit_system_t *);
  void updateSystem();

private:
  QVBoxLayout *varsLayout;
  divine::affine_explicit_system_t *pSys;
  bool loaded;
};
 
