#include <QApplication>
#include <string>
 
#include "affine_gui.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myAffineGui *dialog = new myAffineGui;

    if (argc>1)
      {
	dialog->path=argv[1];
	dialog->loadModel();
      }

    dialog->show();    
    return app.exec();
}
