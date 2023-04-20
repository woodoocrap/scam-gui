#include "mainwindow.hpp"
#include "QMessageBox"


MainWindow::MainWindow(QWidget * parent) 
   : QWidget(parent)
{
   scamButton.setText("Execute");
   setStyleSheet("background: #0d1117; color: #e6edf3");

   scamButton.setStyleSheet(R"(
      max-width: 200px;
      font-size: 20px;
      padding: 20px 0;
      font-weight: 600;
   )");

   connect(&scamButton, &QPushButton::clicked, this, &MainWindow::scamButtonPressed);

   vbox.setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

   topRow.addWidget(&repoPicker);
   vbox.addLayout(&topRow);

   vbox.addWidget(&canvasArea);

   bottomRow.addWidget(&scamButton);
   vbox.addLayout(&bottomRow);

   setLayout(&vbox);
}


void MainWindow::scamButtonPressed()
{
   if ( !repoPicker.getRepo()->isOpen() ) {
      QMessageBox::critical(this, "error", "no repository selected");
      return;
   }
 
   git_signature * empty = nullptr;
   git_signature * signature = nullptr;

   if ( signatureDialog.getName() == "" ) { signatureDialog.exec(); }
   size_t timestamp = canvasArea.getDate().endOfDay().toSecsSinceEpoch();

   int err = git_signature_new (
      &signature,
      signatureDialog.getName().toStdString().c_str(),
      signatureDialog.getEmail().toStdString().c_str(),
      timestamp, 0
   );

   if ( err ) {
      QMessageBox::critical(this, "signature failure", repoPicker.getRepo()->lastError());
      signatureDialog.clear();
      return;
   }

   err = git_signature_now(&empty, "_", "_");

   if ( err ) {
      QMessageBox::critical(this, "signature failure", repoPicker.getRepo()->lastError());
      return;
   }

   spamCommits(signature, empty);

   git_signature_free(signature);
   git_signature_free(empty);
}


void MainWindow::spamCommits(git_signature * signature, git_signature * empty)
{  
   GitRepo * repo = repoPicker.getRepo();
   std::vector<int> days = canvasArea.getDays();

   QString filename = QString::number(QDateTime::currentSecsSinceEpoch());
   QString filepath = repoPicker.getPath() + "/" + filename;
   QFile modFile(filepath);

   if ( !modFile.open(QFile::WriteOnly) ) {
      QMessageBox::critical(this, "error", "failed to open a mod file");
      return;
   }

   QFileDevice::Permissions permissions = modFile.permissions();
   //add a file with empty signature so it doesnt count as your commits
   bool ok = repo->createCommit(filename, empty);
   if ( !ok ) { goto commit_failure; }
   
   //draw all of the commits from canvas
   for ( int commits : days ) {

      for ( int i = 0; i < commits; i+=1 ) {
         
         modFile.setPermissions(permissions ^ QFileDevice::ExeOwner);
         ok = repo->createCommit(filename, signature);
         if ( !ok ) { goto commit_failure; }
      }

      signature->when.time += 3600 * 24;
   }

   //remove a file with empty signature
   modFile.remove();

   repo->createCommit(filename, empty);
   if ( !ok ) { goto commit_failure; }

   return;

commit_failure:
   QMessageBox::critical(this, "commit error", repo->lastError());
   return;
}

