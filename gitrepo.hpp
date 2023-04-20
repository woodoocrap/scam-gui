#ifndef GIT_REPO_HEADER
#define GIT_REPO_HEADER

#include "QDate"
#include "QString"

#include "git2.h"

class GitRepo {

   bool is_open;

   QString name;
   QString branch;

   int ncommits = -1;

   git_tree * tree = nullptr;
   git_index * index = nullptr;
   git_reference * head = nullptr;
   git_repository * repo = nullptr;

   int countCommits(const char * branch_name);
   bool initTree();
   void reset();

 public:
   //single file comit cuz i dont need more than that
   bool createCommit(QString filepath, git_signature * signature);

   const char * lastError() const;
   QString getActiveBranch() const;
   int getCommitCount() const;
   QString getName() const;

   bool open(QString path);
   bool isOpen() const;

   ~GitRepo();
   GitRepo();
};

#endif
