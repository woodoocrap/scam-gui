#ifndef SCAM_GUI_MAINWINDOW_HEADER
#define SCAM_GUI_MAINWINDOW_HEADER

#include "QMainWindow"
#include "QPushButton"
#include "QVBoxLayout"

#include "canvasarea.hpp"
#include "gitrepopicker.hpp"
#include "signaturedialog.hpp"

   
class MainWindow : public QWidget {

   QVBoxLayout vbox;

   QHBoxLayout topRow;
   QHBoxLayout bottomRow;

   SignatureDialog signatureDialog;
   GitRepoPicker repoPicker;
   CanvasArea canvasArea;

   QPushButton scamButton;

   void spamCommits(git_signature * signature, git_signature * empty);
 
 private slots:
   void scamButtonPressed();

 public:
   explicit MainWindow(QWidget * parent = nullptr);

};

#endif
