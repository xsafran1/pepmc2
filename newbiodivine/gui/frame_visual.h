#pragma once

#include <QtGui>
#include "sevine.h"
#include "ui_frame_visual.h"

const qreal surroundingFrameWidth = 30;
const qreal viewWidth = 1024;
const qreal viewHeight = 768;
const qreal axisSeparator=10;
const qreal tickSize=6;


class myFrameVisual: public QFrame, private Ui::Frame_Visual
{
  Q_OBJECT
    
public:
    myFrameVisual(QWidget *parent = 0);
    void setSystem(divine::affine_explicit_system_t *_pSys);
    void compute(size_t _mode, size_t _p1=0);

public slots:    
    void setupScene();
    void showAll();
    void zoomIn();
    void zoomOut();
    void setUniformedTresholds(bool);


private:
    qreal getXScale(size_t x);
    qreal getYScale(size_t y);
    qreal zoomFactor;
    

    divine::affine_explicit_system_t *pSys;
    QGraphicsScene* myScene;

    void showState(divine::state_t, QColor, size_t timePos=0);
    
    struct { divine::state_t s; bool l; } p_t;

    std::vector< std::vector< std::pair< bool, divine::state_t > > > levels;
    divine::explicit_storage_t visited;
    size_t bfs_depth;

    divine::succ_container_t initialStates;
    size_t mode;

    bool uniform_tresholds;
        
};
 
