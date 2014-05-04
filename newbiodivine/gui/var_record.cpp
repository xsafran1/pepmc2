#include "var_record.h"

myVarRecord::myVarRecord(QWidget *)
{
  setupUi(this); // this sets up GUI
}

void myVarRecord::setVar(divine::affine_explicit_system_t *_p,size_t _i)
{
  QString auxStr;
  label_3->setText(QString::number(_i));
  lineEdit->insert(QString::fromStdString(_p->get_varname(_i)));

  auxStr="d"+QString::fromStdString(_p->get_varname(_i))+"= ";
  for (size_t j=0; j<_p->get_sums(_i); j++)
    {
      auxStr+="("+QString::number(_p->/*vars[_i].sums[j].k*/model.getSumForVarByIndex(_i, j).GetConstant())+")";
      //TODO: dalo by sa pridat ku konstante prinasobit aj hodnotu parametru ak nejaky je
      
    	if (_p->model.getSumForVarByIndex(_i, j).hasParam()) {
    		double fstValue = _p->model.getParamRange(_p->model.getSumForVarByIndex(_i,j).GetParam() - 1).first;
    		double sndValue = _p->model.getParamRange(_p->model.getSumForVarByIndex(_i,j).GetParam() - 1).second;
    		auxStr += "*";
    		auxStr += QString::number((sndValue + fstValue)*0.5);
    	}
      
      for (/*size_t k=0; k<_p->get_dim(); k++*/ size_t k = 0; k < _p->model.getSumForVarByIndex(_i, j).GetVars().size(); k++ )
		{
		  //if (_p->vars[_i].sums[j].used_vars.get(k))
			{
				size_t index = _p->model.getSumForVarByIndex(_i, j).GetVars().at(k) - 1;
			  auxStr+="*";
			  auxStr+=QString::fromStdString(_p->get_varname(/*k*/index));
			}
		}

      if (j!=_p->get_sums(_i)-1)
	auxStr+=" + ";      
    }
  lineEdit_2->insert(auxStr);

  auxStr="";
  for (size_t j=0; j<_p->get_treshs(_i); j++)
    {
      auxStr+=QString::number(_p->get_tresh(_i,j));
      if (j!=_p->get_treshs(_i)-1)
	auxStr+=", ";
    }
  lineEdit_3->insert(auxStr);
}

