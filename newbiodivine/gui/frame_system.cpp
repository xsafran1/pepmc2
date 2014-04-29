#include "frame_system.h"

myFrameSystem::myFrameSystem(QWidget *parent)
{
  setupUi(this); // this sets up GUI
  varsLayout = new QVBoxLayout(varFrame);
  pSys = 0;
  loaded = false;
  connect (significanceCheckBox, SIGNAL( stateChanged(int) ), parent, SLOT ( setModified() ));
  connect (significanceCheckBox, SIGNAL( stateChanged(int) ), this, SLOT ( updateSystem() ));
  connect (significanceSpinBox, SIGNAL( valueChanged(int) ), parent, SLOT ( setModified() ));
  connect (significanceSpinBox, SIGNAL( valueChanged(int) ), this, SLOT ( updateSystem() ));

  connect (zeroCheckBox, SIGNAL( stateChanged(int) ), parent, SLOT ( setModified() ));
  connect (zeroCheckBox, SIGNAL( stateChanged(int) ), this, SLOT ( updateSystem() ));
  connect (zeroSpinBox, SIGNAL( valueChanged(int) ), parent, SLOT ( setModified() ));
  connect (zeroSpinBox, SIGNAL( valueChanged(int) ), this, SLOT ( updateSystem() ));
  connect (zeroEdit, SIGNAL( editingFinished() ), parent, SLOT ( setModified() ));
  connect (zeroEdit, SIGNAL( editingFinished() ), this, SLOT ( updateSystem() ));
}

void
myFrameSystem::loadVars(divine::affine_explicit_system_t *_pSys)
{
  pSys=_pSys;
  for (size_t _i=0; _i<pSys->get_dim(); _i++)
    {
      myVarRecord *tmp = new myVarRecord();
      tmp->setVar(pSys,_i);
      varsLayout->addWidget(tmp);
    }      
  if (pSys->get_significance_treshold()<1)
    {
      significanceCheckBox->setChecked(true);
    } 
  else
    {
      significanceCheckBox->setChecked(false);
    }
  int val=round(1000*pSys->get_significance_treshold());
  significanceSpinBox->setValue(val);      

  loaded = true;
}

void
myFrameSystem::updateSystem()
{
  if (!loaded) return;
  if (significanceCheckBox->isChecked())
    {
      divine::real_t val = 0.001*significanceSpinBox->value();
      pSys->set_significance_treshold(val);      
      //QMessageBox::information(this,"",QString::number(pSys->get_significance_treshold()));
    }
  else
    {
      pSys->set_significance_treshold(1);
    }
  if (zeroCheckBox->isChecked())
    {
      divine::real_t val = pSys->parseNumber(zeroEdit->text().toStdString());
      val = val * pow(10,zeroSpinBox->value());
      pSys->set_zero_range(val);            
    }
  else
    {
      pSys->set_zero_range(0);
    }

}
