#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_affine_simulator.h"
#include "dialog_visual.h"
#include "dock_debug.h"
#include "frame_system.h"
#include "frame_visual.h"
#include "var_record.h"

class myAffineGui: public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT
    
public:
    myAffineGui(QWidget *parent = 0);
    QString path;

/*     void setupScene(); */


public slots:
    void about();
    void loadModel();
    void saveModel();
    void unloadModel();

    void setModified();
    void newVisual();
    void clearVisuals();

 private:
    divine::affine_explicit_system_t *pSys;
    divine::error_vector_t gerr;
    
    myDockDebug *dockDebug;
    size_t visualNum;
    QString loadedFile;
};
 
