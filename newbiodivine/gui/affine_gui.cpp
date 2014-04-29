#include "affine_gui.h"

myAffineGui::myAffineGui(QWidget *)
{
  setupUi(this); // this sets up GUI

  verticalLayout->setContentsMargins(0, 0, 0, 0);
  actionClose->setEnabled(false);
  actionSave->setEnabled(false);

  dockDebug = new myDockDebug(this);
  dockDebug->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
  dockDebug->hide();
  addDockWidget(Qt::BottomDockWidgetArea, dockDebug);
  menu_View->addAction(dockDebug->toggleViewAction());

  visualNum=0;
  tabWidget->clear();
  
  connect (actionAbout, SIGNAL (triggered()), this, SLOT (about()));
  connect (actionOpen, SIGNAL (triggered()), this, SLOT (loadModel()));
  connect (actionClose, SIGNAL (triggered()), this, SLOT (unloadModel()));
  connect (actionSave, SIGNAL (triggered()), this, SLOT (saveModel()));
  connect (actionNewVisual, SIGNAL (triggered()), this, SLOT (newVisual()));
  connect (actionClearAllVisuals, SIGNAL (triggered()), this, SLOT (clearVisuals()));

  path.clear();
}

void myAffineGui::setModified()
{
    actionSave->setEnabled(true);
}

void myAffineGui::newVisual()
{
  myDialogNewVisual d(this);
  d.lineEdit->setText(tr("Visual ")+QString::number(visualNum++));
  if (QDialog::Accepted == d.exec())
    {
      myFrameVisual *fv = new myFrameVisual();
      fv->setUniformedTresholds(d.uniformedCheckBox->isChecked());
      fv->setWindowTitle(d.lineEdit->text());     
      fv->setSystem(pSys);
      if (d.radioButton->isChecked())
	{
	  fv->compute(1);
	}
      else if (d.radioButton_2->isChecked())
	{
	  fv->compute(2,d.spinBox->value());
	}
      else if (d.radioButton_3->isChecked())
	{
	  fv->compute(3,d.spinBox->value());
	}
      else if (d.radioButton_4->isChecked())
	{
	  fv->compute(4);
	}
	

      tabWidget->addTab(fv,d.lineEdit->text());
      tabWidget->setCurrentWidget(fv);
      fv->showAll();
      actionClearAllVisuals->setEnabled(true);
    }
}

void myAffineGui::clearVisuals()
{
  for (size_t i=0; i<=visualNum; i++)
    {
      tabWidget->removeTab(1);
    }
  visualNum=0;
}

void myAffineGui::saveModel()
{
  std::ofstream out;
  QString spath;    
  spath = QFileDialog::getSaveFileName(this,
				       "Choose a filename to save to",
				       loadedFile,
				       "*.bio");
  if (spath.size()==0) return;

  out.open(spath.toStdString().c_str());
  pSys->write(out);
  out.close();
  
  actionSave->setEnabled(false);
}

void myAffineGui::loadModel()
{
  divine::affine_explicit_system_t *auxPSys;
  if (path.size()==0)
    {
      path = QFileDialog::getOpenFileName(this,
					  "Choose a file to open",
					  QString::null,
					  "*.bio");
    }
  
  //QMessageBox::about(this,"Info","You have selected "+_fp+" to be opened.");
  
  auxPSys = new divine::affine_explicit_system_t (gerr);
  if (auxPSys->read(path.toStdString().c_str()))
    {
      QMessageBox::critical(this,tr("SimAff Error"), tr("The file cannot be loaded"));
    }
  else
    {
      if (actionClose->isEnabled())
	{
	  unloadModel();
	  if (actionClose->isEnabled())
	    return;
	}

      myFrameSystem *fs = new myFrameSystem(this);
      pSys = auxPSys;

//         QMessageBox::about(this,"Info",
//       		     "The model contains "+
//       		     QString::number(pSys->get_dim())+
//       		     " variables.");

      tabWidget->addTab(fs,tr("System"));
      fs->loadVars(pSys);
      actionClose->setEnabled(true);
      actionSave->setEnabled(false);
      menuVisual->setEnabled(true);

      loadedFile = path;
      setWindowTitle("SimAff - "+path);
    }
  path="";
}

void myAffineGui::unloadModel()
{

  if (actionSave->isEnabled())
    {
      
      if (QMessageBox::Save ==
	  QMessageBox::question(this,tr("SimAff Question"),
				tr("The current model has been modified. Shall it be saved?"),
				QMessageBox::Save|QMessageBox::Discard
				)
	  )
	{
	  saveModel();
	  if (actionSave->isEnabled())
	    return;
	}
    }
  tabWidget->clear();
  
  actionClose->setEnabled(false);
  clearVisuals();
  menuVisual->setEnabled(false);
}

void myAffineGui::about() 
{
  QMessageBox::about(this,
		     tr("Simaff About"),
		     tr("This app was coded to support EC-MOAN project.\n")
		     );                
}
