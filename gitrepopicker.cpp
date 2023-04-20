#include "gitrepopicker.hpp"

#include "QMessageBox"


void GitRepoPicker::setupStyles()
{
   branch.setStyleSheet("font-size: 14px;");
   name.setStyleSheet("font-size: 16px; font-weight: 600;");

   name.setAlignment(Qt::AlignHCenter);
   hbox.setAlignment(Qt::AlignCenter);
   vbox.setAlignment(Qt::AlignCenter);
}


GitRepoPicker::GitRepoPicker(QWidget * parent)
   : QWidget(parent),
     fileDialog(nullptr, "select a repository folder", "")
{  
   name.setText("No Repo Selected");
   branch.setText("click here to select a repository");
   
   fileDialog.setOption(QFileDialog::ShowDirsOnly, false);
   fileDialog.setFileMode(QFileDialog::Directory);

   hbox.addWidget(&branch);

   vbox.addWidget(&name);
   vbox.addLayout(&hbox);

   setupStyles();
   setLayout(&vbox);
}


void GitRepoPicker::mousePressEvent(QMouseEvent * event)
{
   int result = fileDialog.exec();
   if ( result == QDialog::Rejected ) { return; }
   
   path = fileDialog.selectedFiles()[0];
   bool ok = repo.open(path);

   if ( !ok ) { 

      name.setText("No Repo Selected");
      branch.setText("click to select a repository");

      QMessageBox::critical(this, "error", repo.lastError());

      return;
   }
   
   QString commit_count = QString::number(repo.getCommitCount());
   branch.setText("[ " + repo.getActiveBranch() + " ] " + commit_count + " commits");
   name.setText(repo.getName());
}

QString GitRepoPicker::getPath() const { return path; }

GitRepo * GitRepoPicker::getRepo() { return &repo; }
