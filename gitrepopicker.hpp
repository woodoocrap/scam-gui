#ifndef SCAM_GUI_GIT_REPO_PICKER_HEADER
#define SCAM_GUI_GIT_REPO_PICKER_HEADER

#include "QLabel"
#include "QWidget"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QFileDialog"

#include "gitrepo.hpp"

class GitRepoPicker : public QWidget {
   
   QString path;
   GitRepo repo;

   QLabel name;
   QLabel branch;

   QVBoxLayout vbox;
   QHBoxLayout hbox;

   QFileDialog fileDialog;
 
   void setupStyles();

 protected: 
   void mousePressEvent(QMouseEvent *event) override;

 public:
   explicit GitRepoPicker(QWidget * parent = nullptr);

   bool repoSelected() const;
   QString getPath() const;

   GitRepo * getRepo();
};

#endif
