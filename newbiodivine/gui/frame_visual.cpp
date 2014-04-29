#include "frame_visual.h"

void myFrameVisual::setUniformedTresholds(bool _ut)
{
  uniform_tresholds = _ut;
}

qreal myFrameVisual::getXScale(size_t _x)
{
  if (_x<pSys->get_dim())
    {
      qreal xMax;
      qreal xMin;
      if (uniform_tresholds)
	{
	  xMax = pSys->get_treshs(_x);
	  xMin = 0;   
	}
      else
	{
	  xMax = pSys->get_tresh(_x,pSys->get_treshs(_x)-1);
	  xMin = pSys->get_tresh(_x,0);   
	}
     return  (xMax-xMin) / (viewWidth-(2*surroundingFrameWidth));
    }
  else
    return (1+bfs_depth) / (viewWidth-(2*surroundingFrameWidth));
} 

qreal myFrameVisual::getYScale(size_t _y)
{
  qreal yMax;
  qreal yMin;
  if (uniform_tresholds)
    {
      yMax = pSys->get_treshs(_y);
      yMin = 0;   
    }
  else
    {
      yMax = pSys->get_tresh(_y,pSys->get_treshs(_y)-1);
      yMin = pSys->get_tresh(_y,0);
    }
  return  (yMax-yMin) / (viewHeight-(2*surroundingFrameWidth));
} 


myFrameVisual::myFrameVisual(QWidget *)
{
  mode = 0;
  bfs_depth = 0;
  zoomFactor=1;
  pSys = 0;
  setupUi(this); // this sets up GUI

  uniform_tresholds = true;

  myScene = new QGraphicsScene(graphicsView);
  graphicsView->setScene(myScene);
  graphicsView->setSceneRect(0,0,viewWidth,viewHeight);
  graphicsView->show();



}

void myFrameVisual::showAll()
{
  zoomFactor=1;  
  graphicsView->fitInView(0,0,viewWidth,viewHeight,Qt::KeepAspectRatio);
}

void myFrameVisual::zoomIn()
{
  zoomFactor*=1.2;
  graphicsView->scale(1.2,1.2);
  myScene->update();
  graphicsView->update();
}

void myFrameVisual::zoomOut()
{
  if (zoomFactor<0.5)
    {
      return;	    
    }
  zoomFactor=zoomFactor/1.2;
  graphicsView->scale(1/1.2,1/1.2);
  myScene->update();
  graphicsView->update();
}


void myFrameVisual::setSystem(divine::affine_explicit_system_t *_pSys)
{
  pSys = _pSys;
  mode = 0;
 
  for (size_t _i=0; _i<pSys->get_dim(); _i++)
    {
      comboBox->addItem(QString::fromStdString(pSys->get_varname(_i)));
      comboBox_2->addItem(QString::fromStdString(pSys->get_varname(_i)));
    }
  comboBox->addItem("TIME STEPS");  
  
  connect (comboBox, SIGNAL (currentIndexChanged(int)), this, SLOT (setupScene()));
  connect (comboBox_2, SIGNAL (currentIndexChanged(int)), this, SLOT (setupScene()));
  setupScene();
  connect (toolButtonShowAll, SIGNAL (clicked()), this, SLOT (showAll()));
  connect (toolButtonZoomOut, SIGNAL (clicked()), this, SLOT (zoomOut()));
  connect (toolButtonZoomIn, SIGNAL (clicked()), this, SLOT (zoomIn()));
}

void myFrameVisual::compute(size_t _mode, size_t _p1)
{
  if (mode!=0 || pSys == 0) return;
  visited.set_appendix(sizeof(size_t));
  visited.init();
  size_t lev=0;
  mode = _mode;
  bfs_depth = 1;
  switch (_mode) {
  case 1: //Initial states
    {
      divine::state_t s=pSys->get_initial_state();
      pSys->get_succs(s,initialStates);
      delete_state(s);
      comboBox->removeItem(comboBox->count()-1);        
      setupScene();
    }
    break;
  case 2: //Limited BFS
  case 3: //All runs simulation
    if (_p1==0)
      { 
	mode=0;
	break;
      }
    bfs_depth = _p1;
    levels.resize(bfs_depth+1);
    while (lev<_p1)
      {
	lev++;
	if (lev==1)
	  {
	    divine::state_t s=pSys->get_initial_state();
	    pSys->get_succs(s,initialStates);
	    delete_state(s);
	    for (divine::succ_container_t::iterator c=initialStates.begin();
		 c!=initialStates.end();
		 c++)
	      {
		std::pair< bool, divine::state_t > pp;
		divine::state_t t=*c;
		divine::state_ref_t ref;
		pp.first = false;
		pp.second = t;
		levels[0].push_back( pp );
		visited.insert(t,ref);
		visited.set_app_by_ref(ref,lev);
	      }
	  }
	for (std::vector<std::pair< bool, divine::state_t > >::iterator c=levels[lev-1].begin();
	     c!=levels[lev-1].end();
	     c++)
	  {
	    divine::succ_container_t succs;
	    divine::state_t s = (*c).second;
	    divine::state_ref_t ref;
	    pSys->get_succs(s,succs);
	    for (divine::succ_container_t::iterator d=succs.begin();
		 d!=succs.end();
		 d++)
	      {
		std::pair< bool, divine::state_t > pp;
		divine::state_t t = (*d);
		pp.second = t;
		pp.first=false;
		if (t == s) // should update s !!
		  {
		    (*c).first = true;
		  }
		if (!visited.is_stored(t,ref))
		  {
		    visited.insert(t,ref);
		    visited.set_app_by_ref(ref,lev);		    
		    levels[lev].push_back( pp );
		  }
		else
		  {		    
		    size_t l;
		    visited.get_app_by_ref(ref,l);
		    if (l==lev || mode==2)
		      {
			delete_state(t);
		      }
		    else
		      {
			visited.set_app_by_ref(ref,lev);
			levels[lev].push_back( pp );
		      }
		  }		  
	      }
	  }
      }
      comboBox->setCurrentIndex(comboBox->count()-1);  
      break;
    case 4: //Vector field
      comboBox->removeItem(comboBox->count()-1);        
      setupScene();
      break;
    default:
      mode=0;
      break;
  }
}
  

void myFrameVisual::setupScene()
{
  if (pSys==0) return;


  bool timesteps=false; 
  size_t _x=pSys->get_dim();

  if (comboBox->currentText()=="TIME STEPS")
    {
      timesteps=true;
      if (mode==4) return;
    }
  else
    {
      _x=pSys->get_varid(comboBox->currentText().toStdString());
    }

  size_t _y=pSys->get_varid(comboBox_2->currentText().toStdString());


  //QMessageBox::information(this,"info","Here! x="+QString::number(_x)+" y="+QString::number(_y) );

  myScene->clear();

  qreal xMax;
  qreal xScale;
  qreal yMax;
  qreal yScale;

  if (uniform_tresholds)
    {
      yMax = pSys->get_treshs(_y);
    }
  else
    {
      yMax = pSys->get_tresh(_y,pSys->get_treshs(_y)-1);
    }
  yScale = getYScale(_y);

  if (timesteps)
    {
      xMax = 1+bfs_depth;
    }
  else
    {
      if (uniform_tresholds)
	xMax = pSys->get_treshs(_x);
      else
	xMax = pSys->get_tresh(_x,pSys->get_treshs(_x)-1);
    }
  xScale = getXScale(_x);

  myScene->addLine(surroundingFrameWidth,
		   surroundingFrameWidth+(yMax/yScale)+axisSeparator,
		   surroundingFrameWidth+(xMax/xScale),
		   surroundingFrameWidth+(yMax/yScale)+axisSeparator);


  myScene->addLine(surroundingFrameWidth-axisSeparator,
		   surroundingFrameWidth,
		   surroundingFrameWidth-axisSeparator,
		   surroundingFrameWidth+(yMax/yScale));

  for (size_t i=0;
       i < ( timesteps ? xMax+1 : pSys->get_treshs(_x) );
       i++)
    {
      qreal y1=surroundingFrameWidth+(yMax/yScale)+axisSeparator+tickSize;
      qreal y2=y1-tickSize;
      qreal x1=surroundingFrameWidth+ 
	( (timesteps || uniform_tresholds) ? i/xScale : (pSys->get_tresh(_x,i)/xScale) );
      qreal x2=x1;
      myScene->addLine(x1,y1,x2,y2);
      QGraphicsTextItem *auxText;
      if (timesteps)
	{
	  auxText = myScene->addText(QString::number(i));
	}
      else
	{
	  auxText = myScene->addText(QString::number(pSys->get_tresh(_x,i)));
	}
      auxText->setPos(x1-auxText->boundingRect().width()/2,
		      y2+tickSize
		      );
    }

  for (size_t i=0; i<pSys->get_treshs(_y); i++)
    {
      qreal x1=surroundingFrameWidth-axisSeparator-tickSize;
      qreal x2=x1+tickSize;
      qreal y1=surroundingFrameWidth+(yMax/yScale)-
	(uniform_tresholds ? i/yScale : (pSys->get_tresh(_y,i)/yScale));
      qreal y2=y1;
      myScene->addLine(x1,y1,x2,y2);       
      QGraphicsTextItem *auxText = myScene->addText(QString::number(pSys->get_tresh(_y,i)));
      auxText->setPos(x1-tickSize-auxText->boundingRect().width(),
		      y1-auxText->boundingRect().height()/2
		      );
    }

  if (mode==1)
    {
      for (divine::succ_container_t::iterator j=initialStates.begin();
	   j!=initialStates.end();
	   j++)
	{
	  showState(*j,QColor("green"),0);
	}
    }

  if (mode==2 || mode==3)
    {
      for (size_t i=0;i<bfs_depth; i++)
	for (size_t j=0; j<levels[i].size(); j++)
	  showState (levels[i][j].second,
		     (levels[i][j].first ? QColor("red") : QColor("cyan")),
		     i);
    }

  if (mode == 4)
    {
      divine::state_t s=pSys->get_initial_state();
      size_t *_state = static_cast<size_t*>(static_cast<void*>(s.ptr));
      for (size_t k=0; k<pSys->get_dim(); k++)
	{
	  _state[k]=0;
	}
      for (size_t i=1; i<pSys->get_treshs(_x)-1; i++)
	for (size_t j=1; j< pSys->get_treshs(_y)-1; j++)
	  {
	    _state[_x]=i;
	    _state[_y]=j;
	    showState(s, QColor("red"), 0);
	  }
      delete_state(s);
    }
  showAll();
  graphicsView->update();
}

void myFrameVisual::showState(divine::state_t _s, QColor _col, size_t timePos)
{
  bool timesteps=false;
  if (comboBox->currentText()=="TIME STEPS")
    {
      timesteps=true;
    }
  
  size_t *_state = static_cast<size_t*>(static_cast<void*>(_s.ptr));


  if ((_state[0]==pSys->get_treshs(0)))
    {
      //This is a pre-initial state. We don't want to  draw it.
      return;
    }

  size_t _x=pSys->get_dim(); //Indicates TIME STEPS for getXScale()
  if (!timesteps)
    {
      _x=pSys->get_varid(comboBox->currentText().toStdString());
    }
  
  size_t _y=pSys->get_varid(comboBox_2->currentText().toStdString());


//   QMessageBox::information(this,"showState","in _X="+QString::number(_state[_x]) +
// 			        " in _Y="+QString::number(_state[_y]) +
// 			        " where max is "+QString::number(pSys->get_treshs(_x))
// 			   );

  qreal x,w;

  if (timesteps)
    {
      x=surroundingFrameWidth+(timePos/getXScale(_x));
    }
  else
    {
      if(uniform_tresholds)
        x=surroundingFrameWidth+(_state[_x]/getXScale(_x));
      else    
	{
	  x=surroundingFrameWidth+(pSys->get_tresh(_x,_state[_x])/getXScale(_x));
	}
    }

  qreal y;
  if (uniform_tresholds)
    {
      y=surroundingFrameWidth
	+(pSys->get_treshs(_y)-_state[_y]) / getYScale(_y);
    }
  else
    {
      y=surroundingFrameWidth
	+(pSys->get_tresh(_y,pSys->get_treshs(_y)-1)-pSys->get_tresh(_y,_state[_y])) / getYScale(_y);
    }

  if (timesteps)
    w= 1/getXScale(pSys->get_dim());
  else
    if (uniform_tresholds)
      {
	w=1/getXScale(_x);
      }
    else
      {
	w=(pSys->get_tresh(_x,1+_state[_x])-pSys->get_tresh(_x,_state[_x])) /getXScale(_x);
      }


  qreal h;
  if (uniform_tresholds)
    {
      h=1/getYScale(_y);
    }
  else
    {
      h=(pSys->get_tresh(_y,1+_state[_y])-pSys->get_tresh(_y,_state[_y])) /getYScale(_y);
//       QMessageBox::information(this,"info","Here! 4");
    }

  if (mode!=4)
    {
      if (w>2 && h>2)
	myScene->addRect(x+1,y+1,w-2,-h+2,QPen(),QBrush(_col));
      else
	myScene->addRect(x,y,w,-h,QPen(),QBrush(_col));
    }
  else
    {
      w=pSys->value(_state,_x);
      h=pSys->value(_state,_y);
      myScene->addLine(x,y,x+w,y-h,QPen());
      
      if ( ( qAbs(w) < qAbs(h) && qAbs(w)*2 > qAbs(h) ) ||
	   ( qAbs(h) < qAbs(w) && qAbs(h)*2 > qAbs(w) )
	 )
	{
	  myScene->addLine(x+w,y-h,x+w,y-h+(h>0?3:-3));
	  myScene->addLine(x+w,y-h,x+w+(w>0?-3:3),y-h);
	}
      else
	{
	  myScene->addLine(x+w,y-h,x+w+(w>0?-3:3),y-h+(h>0?3:-3));
	  myScene->addLine(x+w,y-h,x+w+(w>0?3:-3),y-h+(h>0?3:-3));
	}
    }
}
