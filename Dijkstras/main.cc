/*
 * Course: CS 100 Summer Session 2 2012
 *
 * First Name: Sam
 * Last Name: Lee
 * Username: slee103
 * email address: slee103@ucr.edu
 *
 *
 * Assignment: assn5
 * Filename : main.cc
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there 
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 
#include "priority_queue.H"
#include <set>
#include <sstream>

template<typename Node>
map<Node,Node> dijkstra(map< Node,set<Node> >& neighbors, Node source) {
  map<Node,Node> parent; //tree to be returned
  map<Node,int> dist;    //per-node distances to source
  map<Node,bool> visited; //check if we already visited the node;
  priority_queue<Node> worklist; //main work horse
  typename map< Node,set<Node> >::iterator mit;
  //give all the distance type of max value
  for(mit=neighbors.begin();mit!=neighbors.end(); mit++){
    dist[(*mit).first]=2147480000;
    //worklist.push((*mit).first);
  }  
  dist[source]=0;
  worklist.push(source,0);
  Node top;
  typename set<Node>::iterator sitt;
  while(!worklist.empty()){
    //proceed as described above.
    //Take the min value 
    top=worklist.top();
    visited[top]=true;
    worklist.pop();
    //for all the neighbors of min, check min+1 and compare with
    //neighbors distance.
    for(sitt=neighbors[top].begin();sitt!=neighbors[top].end();sitt++){
      if(visited[(*sitt)]==true){}
      else if((dist[top]+1)<dist[(*sitt)]){
        dist[(*sitt)]=(dist[top]+1);
        parent[(*sitt)]=top;
        worklist.push((*sitt),dist[(*sitt)]);
      }
    }
       
 } 
  //print dist map
  /*typename map<Node,int>::iterator tit;
  for(tit=dist.begin();tit!=dist.end();tit++){
    cout<<(*tit).first<<" | "<<(*tit).second<<endl;
  }*/
  return parent;
}

//Compare function that returns true if two words are 1 letter apart.
//This function was used before new method was used.
bool compare(string a, string b){
  int counter=0;
  for(int i=0; i<a.size(); i++){
    if((a[i]-b[i]>0)||(a[i]-b[i]>0))
      counter++;
  }
  return (counter==1);
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    cerr<<argv[0]<<" usage: start end < dictionary\n";
    exit(-1);
  }

  map<string,bool> in_dictionary;
  map< string, set<string> > neighbors;
  map< string, set<string> >::iterator it;
  set<string>::iterator sit;
  string compare;
  bool build;//stops while loop when 5 iteration
  int cit; //tool used to stop iteration

  for(string s; cin>>s;) {
    cit=0;
    build=true;
    in_dictionary[s]=true;
    while(build){
      //change 1 letter at a time then check if that string is in dictionary.
      for(int j=97;j<123;++j){
        compare=s;
        string replace(1,char(j));
        compare.replace(cit,1,replace);
        if(in_dictionary[compare]&&compare!=s){
          neighbors[compare].insert(s);
          neighbors[s].insert(compare);
        }
      }
     ++cit;
     if(cit==5) build=!build;
    } 
  }
 
  //Show all the neighbors
  /*for(it=neighbors.begin();it!=neighbors.end(); it++){
    cout<<(*it).first<<" | ";
    for(sit=(*it).second.begin();sit!=(*it).second.end();sit++){
      cout<<*sit<<" ";
    }
    cout<<endl;
  }*/
  
  map<string,string> parent = dijkstra(neighbors, string(argv[2]));
  //print out parent
  /*map<string,string>::iterator mit;
  for(mit=parent.begin();mit!=parent.end();mit++){
    cout<<(*mit).first<<" "<<(*mit).second<<endl;
  }*/

  for(string s=argv[1];s!="";s=parent[s]) {
    cout<<s<<endl;
    if(s==argv[2]) exit(0);
  }
  cerr<<"No such ladder found." <<endl;
  exit(1);


}
