#ifndef SCAM_GUI_SIGNATURE_DALOG_HEADER
#define SCAM_GUI_SIGNATURE_DALOG_HEADER

#include "QLabel"
#include "QDialog"
#include "QLineEdit"
#include "QHBoxLayout"
#include "QPushButton"

class SignatureDialog : public QDialog {
   
   QVBoxLayout vbox;
   QHBoxLayout hbox;

   QLabel nameLabel;
   QLabel emailLabel;

   QLineEdit nameInput;
   QLineEdit emailInput;

   QPushButton setButton;
 
 private slots:
   void setButtonPressed();

 public:
   explicit SignatureDialog(QWidget * parent = nullptr);

   QString getEmail() const;
   QString getName() const;

   void clear();
};

#endif
