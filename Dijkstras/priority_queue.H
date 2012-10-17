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
 * Filename : priority_queue.H
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there 
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */ 
#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__
#include <map>
#include <vector>
#include <iostream>

using namespace std;
const int hType=0;


template< class Item >
class priority_queue {
private:
  vector<Item> heap; // The heap expands/shrinks to fit data
  typedef int indx;  // index with heap
  int time;
  map<Item,indx> index;  //records each Item's place in heap
  map<Item,float> priority; //records each Item's priority
  map<Item,int> timestamp; //keep track which came first
  map<Item,bool> in_heap;
  void percolate_up(indx i){ //moves up item at index i to right spot
    while((i>hType) && parent(i) >=hType && priority[heap[parent(i)]] >= priority[heap[i]]){
      if(priority[heap[parent(i)]]==priority[heap[i]])
        if(timestamp[heap[i]]>timestamp[heap[parent(i)]])
          break;
      
      int par=parent(i);
      swap(par,i);
      i=parent(i);
    }
  }
  void percolate_down(indx i){ //moves down item at index i to right spot recursively
    int c=left(i);
    //Case where same priority
    if((c>hType)&&(right(i)>hType) &&priority[heap[left(i)]]==priority[heap[right(i)]]){
      if(timestamp[heap[c]]>timestamp[heap[right(i)]])
        c=right(i);
    }
    if((c>hType)&&(right(i)>hType) && (priority[heap[c]]>priority[heap[right(i)]])){
      c=right(i);
    }

    if(c>hType && (priority[heap[c]]<=priority[heap[i]])){
      if(priority[heap[c]]==priority[heap[i]])
        if(timestamp[heap[i]]<timestamp[heap[c]])
          return; 
      swap(i,c);
      percolate_down(c);
    }
  }
  //get parent index
  int parent(int child){
    if(child==0) return -1;
    else return (child-1-hType)/2;
  }
  //get left child index
  int left(int parent){
    int ret=2*parent+1-hType;
    return(ret<heap.size()) ? ret : -1;
  }
  //get right child index
  int right(int parent){
    int ret=2*parent+2-hType;
    return(ret<heap.size()) ? ret : -1;
  }
  //swap items given 2 index
  void swap(indx par, indx c){
    Item temp=heap[par];
    heap[par]=heap[c];
    heap[c]=temp;
    index[temp]=c;
    index[heap[par]]=par;
  }
  void build_heap(){
    for(int i=size()/2;i>=hType;--i){
      percolate_down(i);
    }
  }
public:
  //These use the min-heap functions above.
  priority_queue(){
    time=0;
  }
  //overloaded function for build heap
  priority_queue(vector<Item> it, vector<float> pr){
    time=0;
    for(int i=hType; i<it.size(); i++){
      heap[i]=it[i];
      priority[it[i]]=pr[i];
      timestamp[it[i]]=time;
      time++;
    }
    build_heap();
  }
  int size() const{
    return heap.size();
  }
  bool empty() const{
    return (heap.empty());
  }
  //shows the top item
  const Item& top() const{
    return heap.front();
  }
  //deletes the top item
  void pop(){
    heap[hType]=heap[size()-1];
    heap.pop_back();
    percolate_down(hType);
    //print();
  }
  //pushes given item in to the priority queue
  void push(Item w, float prio=numeric_limits<float>::max()){
    priority[w]=prio;
    if(size()==0){
      timestamp[w]=time;
      time++;
      heap.push_back(w);
      index[w]=hType;
      return;
    } 
    if(in_heap[w]==true) return;
    heap.push_back(w);
    timestamp[w]=time;
    time++;
    in_heap[w]=true; 
    percolate_up(size()-1);  
  }
  //helper function that prints the heap
  void print(){
    for(int i=hType;i<heap.size();i++)
      cout<<heap[i];
    }
};
#endif

