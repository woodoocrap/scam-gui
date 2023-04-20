#include "signaturedialog.hpp"
#include <qnamespace.h>


SignatureDialog::SignatureDialog(QWidget * parent)
   : QDialog(parent)
{
   setButton.setText("Set");
   nameLabel.setText("name: ");
   emailLabel.setText("email: ");

   setStyleSheet("background: #0d1117; color: #e6edf3");
   nameInput.setStyleSheet("border: solid #005577; border-width: 0 0 1px 0;");
   emailInput.setStyleSheet("border: solid #005577; border-width: 0 0 1px 0;");

   connect(&setButton, &QPushButton::clicked, this, &SignatureDialog::setButtonPressed);

   hbox.addWidget(&nameLabel);
   hbox.addWidget(&nameInput);

   hbox.addWidget(&emailLabel);
   hbox.addWidget(&emailInput);

   vbox.addLayout(&hbox);
   vbox.addWidget(&setButton);

   setLayout(&vbox);
}


QString SignatureDialog::getName() const { return nameInput.text(); }

QString SignatureDialog::getEmail() const { return emailInput.text(); }

void SignatureDialog::setButtonPressed() { accept(); }


void SignatureDialog::clear()
{
   emailInput.clear();
   nameInput.clear();
}
