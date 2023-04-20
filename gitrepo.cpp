#include "gitrepo.hpp"

#include "QStringList"
#include "stdio.h"


GitRepo::GitRepo() { git_libgit2_init(); }


GitRepo::~GitRepo()
{
   reset();
   git_libgit2_shutdown();
}


void GitRepo::reset()
{
   git_repository_free(repo);
   git_reference_free(head);
   git_index_free(index);
   git_tree_free(tree);

   index = nullptr;
   tree = nullptr;
   head = nullptr;
   repo = nullptr;

   is_open = false;
}


bool GitRepo::initTree()
{
   git_oid tree_id;

   int err = git_repository_index(&index, repo);
   if ( err ) { return false; }

   err = git_index_write_tree(&tree_id, index);
   if ( err ) { return false; }

   err = git_tree_lookup(&tree, repo, &tree_id);

   return err == 0;
}


bool GitRepo::open(QString path)
{
   reset();

   std::string path_str = path.toStdString();
   int err = git_repository_open(&repo, path_str.c_str());
   if ( err ) { return false; }

   err = git_repository_head(&head, repo);
   if ( err ) { return false; }
   
   const char * branch_name = "no branch";
   git_branch_name(&branch_name, head);

   ncommits = countCommits(branch_name);
   branch = QString(branch_name);
   name = path.split("/").last();
   
   bool ok = initTree();
   if ( !ok ) { return false; }
   
   is_open = true;
   return true;
}


int GitRepo::countCommits(const char * branch_name)
{
   int result = 0;
   
   git_revwalk *walker;
   int err = git_revwalk_new(&walker, repo);
   if ( err ) { return -1; }
   
   std::string tmp = std::string("refs/heads/") + branch_name; 
   err = git_revwalk_push_ref(walker, tmp.c_str());

   if ( err ) { 
      git_revwalk_free(walker);
      return -1;
   }

   git_oid oid;
   while (git_revwalk_next(&oid, walker) == 0) { ++result; }

   git_revwalk_free(walker);

   return result;
}


const char * GitRepo::lastError() const 
{
   const git_error * err = git_error_last();
   return err == nullptr ? "No errors ocured" : err->message;
}


QString GitRepo::getActiveBranch() const { return branch; }

int GitRepo::getCommitCount() const { return ncommits; }

QString GitRepo::getName() const { return name; }

bool GitRepo::isOpen() const { return is_open; }


bool GitRepo::createCommit(QString filepath, git_signature * signature)
{
   if ( !is_open ) { return false; }

   bool result = false;
   git_oid parent_id;
   git_commit * parent = nullptr;
   
   int err = git_reference_name_to_id(&parent_id, repo, "HEAD");
   if ( err ) { goto freenquit; }
   
   err = git_commit_lookup(&parent, repo, &parent_id);
   if ( err ) { goto freenquit; }
   
   //add a file
   err = git_index_add_bypath(index, filepath.toStdString().c_str());
   if ( err ) { goto freenquit; }

   err = git_commit_create_v(&parent_id, repo, "HEAD", signature, signature, NULL, "_", tree, 1, parent);
   if ( err ) { goto freenquit; }

   //commit successfuly created
   result = true;
 
freenquit:
   git_commit_free(parent);
   return result;
}
