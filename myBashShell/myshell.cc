/*
 * Course: CS 100 Summer Session 2 2012
 *
 * First Name: Sam
 * Last Name: Lee
 * Username: slee103
 * email address: slee103@ucr.edu
 *
 *
 * Assignment: assn3
 * Filename : myshell.cc
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there 
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <fcntl.h>

using namespace std;

string pd;

int do_it(vector<string> tok) //function at reads in arguments
{
  if(!tok.size()) return 0; //empty vector, return
  //special case for cd: need to check for home
  //or user inputed directory
  if(tok[0]=="cd"){        
    if(tok.size()<=1){ chdir(getenv("HOME")); pd="~"; }
    else{
      string dir=tok[1];
      if(chdir(dir.c_str())==-1) {
        cerr<<"-bash: cd: "<<dir<<": No such file or directory"<<endl;
        return -1;
      }
      //changing the current path
      char path[MAXPATHLEN];
      getcwd(path,MAXPATHLEN);
      pd=path;
      pd.replace(0,22,"~");
    }
    return 0;
  } 
  if(pid_t kidpid=fork()) {
    //you are parent
    if(tok.back()=="&")return 0;
    int temp=0;
    waitpid(kidpid, &temp,0);
    return (WIFEXITED(temp) ? WEXITSTATUS(temp):0);
  }
  //you are child
  //create arglist to take in arguments
  char *arglist[1+tok.size()];
  int argct=0;
  for(unsigned int i=0; i!=tok.size(); ++i){
    if(tok[i]=="&"||tok[i]==";")break;
    //Check for I/O and pipeline
    else if(tok[i]=="<") freopen(tok[++i].c_str(),"r",stdin);
    else if(tok[i]==">") freopen(tok[++i].c_str(),"w",stdout);
    else if(tok[i]==">>") freopen(tok[++i].c_str(),"a",stdout);
    else if(tok[i]=="2>") freopen(tok[++i].c_str(),"w",stderr);
    else if(tok[i]=="|"){
      int mypipe[2];
      int &pipeout=mypipe[0];
      int &pipein=mypipe[1];
      pipe(mypipe);
      //constructing the pipeline
      if(fork()==0){
        dup2(pipein, 1);
        close(pipein);
        close(pipeout);
        execvp(tok[0].c_str(),arglist);
      }
      else{
          dup2(pipeout, 0);
          close(pipein); 
          close(pipeout);
          tok.erase(tok.begin(),tok.begin()+i+1);
          exit(do_it(tok));
      }
      close(pipeout);
      close(pipein);
      wait(NULL);
    }
    //If its not any of the previous cases, its an argument
    else{
      arglist[argct]=new char[1+tok[i].size()];
      strcpy(arglist[argct],tok[i].c_str());
      arglist[++argct]=0;
    }
  }
  //run execvp to run program
  string progname=tok[0];
  execvp(progname.c_str(), arglist);
  //Error checking. if it works, it would never reach here
  cerr<<"-bash: "<<progname.c_str()<<": command not found"<<endl;
  exit(errno);
}

int main(){
  //Set present working directory
  pd=getenv("PWD");
  //replace home with tilde.
  string hm=getenv("HOME");
  int hmlen=hm.length();
  pd.replace(0,hmlen,"~");
  //while loop that takes in the commands.
  while(!cin.eof()){
    cout<<"? ";
    string temp="";
    getline(cin,temp);
    //terminating statement
    if(temp=="exit") return 0;
    stringstream ss(temp);
    vector<string> v;
    string s;
    //ss to read in variables
    while(ss>>s){
      //tilde expansion
      if(s[0]=='~') s=getenv("HOME")+s.substr(1);
      v.push_back(s);
      if(s=="&" || s==";"){
      do_it(v);
      
      v.clear();
      }
    }
    do_it(v);
    //print out current working directory
    cout<<pd<<endl;
  
  }
  return 0;
} 
