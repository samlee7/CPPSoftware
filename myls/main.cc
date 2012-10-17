// Course: CS 100 Summer 2012
//
// First Name: Sam
// Last Name: Lee
// Course username: slee103
// email address: slee103@ucr.edu
//
// Lecture Section: 201
// Lab Section: 221
// TA: Wojciech Karas
//
// Assignment: assn1
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include <string>
#include <list>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <locale.h>
#include <time.h>
#include <langinfo.h>
#include <pwd.h>
#include <sstream>
#include <grp.h>
#include <iomanip>
#define each(I) \
  for( __typeof__((I).begin()) it=(I).begin(); it!=(I).end(); ++it)

using namespace std;

int visit(const string root)
{
  DIR* dirp;
  if(!(dirp = opendir(root.c_str())))//Check if directory can be opened
  {
    cout<<"Could not open"<<endl;
    exit(0);
  }
  
  //List of variables to be used
  list<string> files;
  list<string> directories;
  struct stat sb;
  struct passwd* pwd;
  struct group* grp;
  struct tm* time;
  double block=0;
  int fileLen=0;

  //Push all files into file list and directories into directories
  while(dirent *dp=readdir(dirp))
  {
    string s = dp->d_name;
    if(s[0]!='.') //Disregard files starting with .
    {
      string filePath;
      if(root[root.length()-1]=='/')
        filePath=root+s;
      else
        filePath=root+"/"+s;
      files.push_back(s);
      lstat(filePath.c_str(), &sb);
      block=block+sb.st_blocks;

      if(sb.st_size >fileLen)
        fileLen=sb.st_size;
      if((dp->d_type & DT_DIR) && !(dp->d_type &DT_LNK))
      {
        string addDir;
        if(root[root.length()-1]=='/')
          addDir=root+s;
        else
          addDir=root+"/"+s;
        directories.push_back(addDir);
      }
    }
  }

  //Sort files and directories 
  closedir(dirp);
  directories.sort();
  files.sort();

  //Printing out ls -lR
  cout<<root<<":"<<endl;
  cout<<"total "<<block/2<<endl;
  each(files)
  {
    string filePath;
    if(root[root.length()-1]=='/')
      filePath=root+(*it);
    else
      filePath=root+"/"+(*it);
    lstat(filePath.c_str(), &sb);

    //Permissions
    if((sb.st_mode & S_IFMT) == S_IFLNK) cout<< "l";
    else cout<< ((sb.st_mode & S_IFDIR) ? "d" : "-");
    cout<<((sb.st_mode & S_IRUSR) ? "r" : "-");
    cout<<((sb.st_mode & S_IWUSR) ? "w" : "-");
    cout<<((sb.st_mode & S_IXUSR) ? "x" : "-");
    cout<<((sb.st_mode & S_IRGRP) ? "r" : "-");  
    cout<<((sb.st_mode & S_IWGRP) ? "w" : "-");
    cout<<((sb.st_mode & S_IXGRP) ? "x" : "-");
    cout<<((sb.st_mode & S_IROTH) ? "r" : "-"); 
    cout<<((sb.st_mode & S_IWOTH) ? "w" : "-");
    cout<<((sb.st_mode & S_IXOTH) ? "x" : "-");

    //Number of hardlinks
    stringstream hardlink;
    hardlink<<sb.st_nlink;
    cout<<" ";
    cout<<hardlink.str();

    //User id
    cout<<" ";
    if((pwd = getpwuid(sb.st_uid))!=0)
    {
      cout<<pwd->pw_name;
    }
    else //no name case
    {
      stringstream uid;
      uid <<sb.st_uid;
      cout<<uid.str();
    }

    //Group id
    cout<<" ";
    if((grp = getgrgid(sb.st_gid))!=0)
    {
      cout<<grp->gr_name;
    }
    else //no name case
    {
      stringstream gid;
      gid<<sb.st_gid;
      cout<<gid.str();
    }
    
    //file size
    stringstream fL;
    fL << fileLen;
    string fileL=fL.str();
    cout<<" "<<setw(fileL.length())<<sb.st_size;

    //date
    char date[100];
    time= localtime(&sb.st_mtime);
    strftime(date, sizeof(date), "%b %e %H:%M", time);
    cout<<" "<<date<<" "<<(*it);

    //Check if it is symbolic link
    if((sb.st_mode & S_IFMT) == S_IFLNK)
    {
      cout<<" -> ";
      char link[100];
      int linkLen=0;
      string linkPath=filePath;
      if((linkLen=readlink(linkPath.c_str(), link, sizeof(link)-1)) != -1)
        link[linkLen]='\0';
      cout<<link;
    }
    cout<<endl;
  }
  
  //Traverse each directory
  each(directories)
  {
    cout<<endl;
    visit(*it);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc !=1 && argc !=2)
  {
    cout<<"invalid argument"<<endl;
    exit(0);
  }

  string root;
  if(argc==1) //Root is home folder
  {
    root=".";
  }
  else //root is user inputed
  {
    root=argv[1];
  }

  visit(root);
    
  return 0;
}
