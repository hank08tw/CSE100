#include "ActorGraph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
using namespace std;
/*
struct edge{
  string to;
  int cost;
};
*/
/*
struct edge2{
  string to;//actor
  string movie;//movie
  int cost;//cost
};
*/

unordered_map<string,unordered_map<string,bool> > m;
unordered_map<string,vector<edge2> > m2;
//unordered_map<string,vector<edge> > ans;

struct CustomCompare
{
    bool operator()(const edge2& lhs, const edge2& rhs)
    {
        if(lhs.cost!=rhs.cost)return lhs.cost < rhs.cost;
	      return lhs.to < rhs.to;
    }
};
void print_path(string& ans,const string &actor1,string tmp,unordered_map<string,vector<string> >& prev,unordered_map<string,int>& my){
    //cout << "a" << endl;
    if(tmp!=actor1){
      //cout << prev[tmp].size() << endl;
      //cout << "b" << endl;
      print_path(ans,actor1,prev[tmp][0],prev,my);
    }else return;
    string tmp2="("+prev[tmp][0]+")--["+prev[tmp][1]+"#@"+to_string(my[prev[tmp][1]])+"]-->";
    ans.append(tmp2);
}
int main(int argc, char *argv[]) {
  // TODO: Implement code for "Part 1: Path Finder"
  ifstream inFile;
  string input_path=argv[1];
  //cout << "1" << endl;
  input_path="./tsv/"+input_path;
  inFile.open(input_path);
  if(!inFile)cout << "Fail to open .tsv file in first argument!" << endl;
  string oneline="",actor="",movie="",year="";
  int numyear;
  bool first=true;
  bool isu=true;
  unordered_map<string,int> my;
  //cout << "2" << endl;
  if(strcmp(argv[2],"u")==0)isu=true;
  else if(strcmp(argv[2],"w")==0)isu=false;
  else cout << "Please enter u or w in second argument!" << endl;
  while(getline(inFile,oneline)){
   if(first){first=false;continue;}
    actor="";
    movie="";
    year="";
    int kind=1;
    for(int i=0;i<(int)oneline.length();i++){
      string c(1,oneline[i]);
      if(c=="\t"){
        kind++;
      }else{
        if(kind==1){
          actor.append(c);
        }else if(kind==2){
          movie.append(c);
        }else if(kind==3){
          year.append(c);
        }
      }
    }
    numyear=atoi(year.c_str());
    if(isu){
      edge2 tmp;
      tmp.to=actor;
      tmp.cost=1;
      tmp.movie=movie;
      m2[movie].push_back(tmp);
    }else{
      edge2 tmp;
      tmp.to=actor;
      tmp.movie=movie;
      tmp.cost=1+2018-numyear;
      m2[movie].push_back(tmp);
    }
    my[movie]=numyear;
    //cout << actor << endl;
  }
  inFile.close();
  //cout << "3" << endl;
  unordered_map<string,vector<edge2> >::iterator it;
  unordered_map<string,edge2>::iterator mit;
  for(it=m2.begin();it!=m2.end();it++){
    for(int i=0;i<(int)it->second.size();i++){
      for(int j=0;j<(int)it->second.size();j++){
        if(i!=j){
	        edge2 tmp;
          tmp.to=it->second[j].to;
          tmp.cost=it->second[j].cost;
          tmp.movie=it->second[j].movie;
          bool no=true;
          for(mit=m[it->second[i].to].begin();mit!=m[it->second[i].to].end();mit++){//!!!!!不同電影相同weight連相同點
            if(mit->second.to==tmp.to&&mit->second.cost>tmp.cost){mit->second.cost=tmp.cost;mit->second.movie=tmp.movie;no=false;break;}
            if(mit->second.to==tmp.to&&mit->second.cost<=tmp.cost){no=false;break;}
            //if(m[it->second[i].to][k].to==tmp.to&&m[it->second[i].to][k].cost>tmp.cost){m[it->second[i].to][k].cost=tmp.cost;m[it->second[i].to][k].movie=tmp.movie;no=false;break;}
            //if(m[it->second[i].to][k].to==tmp.to&&m[it->second[i].to][k].cost<=tmp.cost){no=false;break;}
          }
	        if(no){m[it->second[i].to][it->second[j].to]=tmp;/*cout << it->second[i].to << "  " << m[it->second[i].to].back().to << endl;cout << m[it->second[i].to].back().movie << endl;cout << m[it->second[i].to].back().cost << endl;*/}
	       }
      }
    }
  }
/*
  for(it=m.begin();it!=m.end();it++){
    unordered_map<string,int> s;
    s[it->first]=0;
    unordered_map<string,vector<edge> >::iterator it2;
    for(it2=m.begin();it2!=m2.end();it2++){
      if(it2->first!=it->first){
        s[it2->first]=1000000000;
      }
    }
    priority_queue<edge,vector<edge>,CustomCompare > p;
    edge tmp;
    tmp.cost=0;
    tmp.to=it->first;
    p.push(tmp);
    while(!p.empty()){
      edge e=p.top();p.pop();
      //int v=p.second;
      //if(d[v]<p.first)continue;
      for(int i=0;i<m[e.to].size();i++){
        edge e2=m[e.to][i];
        if(s[e2.to]>s[e.to]+e2.cost){
	  s[e2.to]=s[e.to]+e2.cost;
          edge nextone;
	  nextone.to=e2.to;
          nextone.cost=s[e2.to];
	  p.push(nextone);
	}
      }
    }
    unordered_map<string,int>::iterator it3;
    vector<edge> a;
    for(it3=s.begin();it3!=s.end();it3++){
      edge aa;
      aa.to=it3->first;
      aa.cost=it3->second;
      a.push_back(aa);
    }
    ans[it->first]=a;
  }
*/
  //cout << "4" << endl;
  ifstream inFile2;
  ofstream ofFile;
  string input_path2=argv[3];
  string output_path=argv[4];
  input_path2="./tsv/"+input_path2;
  output_path="./tsv/"+output_path;
  inFile2.open(input_path2);
  ofFile.open(output_path);
  if(!inFile2)cout << "Fail to open .tsv file in third argument!" << endl;
  if(!ofFile)cout << "Fail to open .tsv file in fourth argument!" << endl;
  string oneline2;
  bool first2=true;
  while(getline(inFile2,oneline2)){
   if(first2){first2=false;continue;}
    string actor1="";
    string actor2="";
    int kind=1;
    //cout << "asdf" << endl;
    for(int i=0;i<(int)oneline2.length();i++){
      string c(1,oneline2[i]);
      //cout << c << endl;
      if(c=="\t"){
        kind++;
      }else{
        if(kind==1){
          actor1.append(c);
        }else if(kind==2/*&&c!=" ""*/){
          actor2.append(c);
        }
      }
    }
    //cout << actor2 << endl;
    //cout << "5" << endl;
    unordered_map<string,int> s;//every actor smallest cost
    unordered_map<string,int>::iterator s2;
    unordered_map<string,vector<string> > prev;//[0] is prev actor [1] is prev movie

    unordered_map<string,unordered_map<string,edge2> >::iterator it2;
    s[actor1]=0;
    for(it2=m.begin();it2!=m.end();it2++){
      if(s.find(it2->first)==s.end()){
        s[it2->first]=1000000000;
      }
    }
    /*
    for(s2=s.begin();s2!=s.end();s2++){
      cout << s2->first << "  " << s[s2->first] << endl;
    }
    */
    priority_queue<edge2,vector<edge2>,CustomCompare > p;
    edge2 tmp;
    tmp.cost=0;

    tmp.to=actor1;
    tmp.movie="useless";
    p.push(tmp);
    unordered_map<string,edge2>::iterator it3;
    while(!p.empty()){
      edge2 e=p.top();p.pop();
      //int v=p.second;
      //if(d[v]<p.first)continue;
      for(it3=m[e.to].begin();it3!=m[e.to].end();it3++){
        //cout << i << endl;
        edge2 e2=it3->second;
        if(s[e2.to]>s[e.to]+e2.cost){
	         s[e2.to]=s[e.to]+e2.cost;
           //cout << "cost: " << e2.cost << endl;
           prev[e2.to].clear();
           prev[e2.to].push_back(e.to);
           prev[e2.to].push_back(m[e.to][e2.to].movie);
           edge2 nextone;
	         nextone.to=e2.to;
           nextone.cost=s[e2.to];
           nextone.movie="useless";
	         p.push(nextone);
	      }
      }
    }
    /*
    for(s2=s.begin();s2!=s.end();s2++){
      cout << s2->first << "  " << s[s2->first] << endl;
    }
    */
    //cout << "6" << endl;
    string ans;
    string tmp2=actor2;
    //cout << "7" << endl;
    print_path(ans,actor1,tmp2,prev,my);
    ans.append("("+actor2+")");
    ofFile << ans << "\n";
    //cout << s[actor2] << endl;
  }
//cout << "8" << endl;
  inFile2.close();
  ofFile.close();
  //priority_queue<int> p;
  return 0;
}
