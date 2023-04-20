#include "QPen"
#include "QPainter"

#include "QWidget"
#include "QLabel"
#include "QVBoxLayout"
#include "QApplication"

#include "mainwindow.hpp"


int main(int argc, char * argv[])
{
   QApplication app(argc, argv);
   
   MainWindow mainWindow;
   mainWindow.show();

   return app.exec();
}
