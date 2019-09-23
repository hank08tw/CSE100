
#include "ActorGraph.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct actor_cost{
  string actor;
  int cost;
};

struct prev_actor_movie{
  string prev_actor;
  string prev_movie;
  string prev_year;
};
class actor_node{
public:
  class movie_year_edge{
  public:
    string movie;
    string year;
    vector<actor_node*> v;
  };
  string actor;
  vector<movie_year_edge*> v;
};
class movie_year_actor{
public:
  string actor;
  string str_movieandyear;
  string movie;
  string year;
  int num_year;
};
class node_to_node{
public:
    string actor;
    vector<movie_year_actor*> v;
};


class CustomCompare
{
public:
    bool operator()(actor_cost& lhs, actor_cost& rhs)
    {
        return lhs.cost >= rhs.cost;
        //if(lhs.cost!=rhs.cost)
	      //return lhs.actor < rhs.actor;
    }
};
unordered_map<string,actor_node> allactor;
unordered_map<string,actor_node::movie_year_edge> allmovieyear;
unordered_map<string,node_to_node> important;
unordered_map<string,actor_node>::iterator allactor_it;
unordered_map<string,actor_node>::iterator actor_it;
unordered_map<string,int> smallest_cost;//every actor smallest cost
unordered_map<string,prev_actor_movie > prevv;//prev actor movie year...
unordered_set<string> visit;
unordered_map<string,string>::iterator it;
void print_path(string& ans,const string &actor1,string end){
    if(end!=actor1){
      print_path(ans,actor1,prevv[end].prev_actor);
    }else return;
    string cur="("+prevv[end].prev_actor+")--["+prevv[end].prev_movie+"#@"+prevv[end].prev_year+"]-->";
    ans.append(cur);
}

int main(int argc, char *argv[]) {
  // TODO: Implement code for "Part 1: Path Finder"
  //unordered_map<string,vector<string> > actortomovie;
  //unordered_map<string,vector<string> > movietoactor;

  ifstream inFile;
  string input_path=argv[1];
  //input_path="./tsv/"+input_path;
  inFile.open(input_path);
  //if(!inFile){cout << "Fail to open .tsv file in first argument!" << endl;return 0;}
  string oneline="",actor="",movie="",year="";
  bool first=true;
  bool isu=true;
  if(strcmp(argv[2],"u")==0)isu=true;
  else if(strcmp(argv[2],"w")==0)isu=false;
  //else {cout << "Please enter u or w in second argument!" << endl;return 0;}
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
    //numyear=atoi(year.c_str());
    string movieandyear=movie+'\t'+year;
    actor_node tmp1;
    tmp1.actor=actor;
    allactor[actor]=tmp1;
    actor_node::movie_year_edge tmp2;
    tmp2.movie=movie;
    tmp2.year=year;
    allmovieyear[movieandyear]=tmp2;
  }
  inFile.close();
  //cout << "1" << endl;
  inFile.open(input_path);
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
    //numyear=atoi(year.c_str());
    string movieandyear=movie+'\t'+year;
    allactor[actor].v.push_back(&allmovieyear[movieandyear]);
    allmovieyear[movieandyear].v.push_back(&allactor[actor]);
  }
  inFile.close();
  //cout << "2" << endl;
  ifstream inFile2;
  ofstream ofFile;
  string input_path2=argv[3];
  string output_path=argv[4];
  //input_path2="./tsv/"+input_path2;
  //output_path="./tsv/"+output_path;
  inFile2.open(input_path2);
  ofFile.open(output_path);
  //cout << "3" << endl;
  if(!inFile2){cout << "Fail to open .tsv file in third argument!" << endl;return 0;}
  if(!ofFile){cout << "Fail to open .tsv file in fourth argument!" << endl;return 0;}
  string oneline2;
  bool first2=true;
  ofFile << "(actor)--[movie#@year]-->(actor)--..." << '\n';
  //cout << "flag" << endl;

  for(allactor_it=allactor.begin();allactor_it!=allactor.end();allactor_it++){
    node_to_node ntn;
    important[allactor_it->first]=ntn;
  }
  for(allactor_it=allactor.begin();allactor_it!=allactor.end();allactor_it++){
    important[allactor_it->first].actor=allactor_it->first;
    for(int i=0;i<(int)allactor[allactor_it->first].v.size();i++){
      string ttmp=allactor[allactor_it->first].v[i]->movie+'\t'+allactor[allactor_it->first].v[i]->year;
      for(int j=0;j<(int)allmovieyear[ttmp].v.size();j++){
        movie_year_actor* tttmp=new movie_year_actor;
        tttmp->str_movieandyear=ttmp;
        tttmp->movie=allactor[allactor_it->first].v[i]->movie;
        tttmp->year=allactor[allactor_it->first].v[i]->year;
        tttmp->actor=allmovieyear[ttmp].v[j]->actor;
        tttmp->num_year=atoi(tttmp->year.c_str());
        important[allactor_it->first].v.push_back(tttmp);
      }
    }
  }
  while(getline(inFile2,oneline2)){
   if(first2){first2=false;continue;}
   int pos2=0;

   pos2 = oneline2.find('\t', pos2);
   string actor1=oneline2.substr(0,pos2);
   string actor2=oneline2.substr(pos2+1);
   //int movie_year=atoi(year_str.c_str());
   /*
    string actor1="";
    string actor2="";
    int kind=1;
    for(int i=0;i<(int)oneline2.length();i++){
      string c(1,oneline2[i]);
      if(c=="\t"){
        kind++;
      }else{
        if(kind==1){
          actor1.append(c);
        }else if(kind==2){
          actor2.append(c);
        }
      }
    }*/
    //cout << "4" << endl;
    //cout << "actor1: " << actor1 << endl;
    //cout << "actor2: " << actor2 << endl;
    smallest_cost.clear();//every actor smallest cost
    prevv.clear();//prev actor movie year...
    visit.clear();

    smallest_cost[actor1]=0;
    for(actor_it=allactor.begin();actor_it!=allactor.end();actor_it++){
      if(actor_it->first!=actor1){
        smallest_cost[actor_it->first]=10000;
      }
    }
    //cout << "5" << endl;
    //cout << "smallest_cost.size(): " <<smallest_cost.size() << endl;
    priority_queue<actor_cost,vector<actor_cost>,CustomCompare > p;

    actor_cost ac1;
    ac1.actor=actor1;
    ac1.cost=0;
    int cost_tmp;
    p.push(ac1);
    //cout << "6" << endl;
    while(!p.empty()){
      actor_cost actor_tmp=p.top();p.pop();
      if(visit.find(actor_tmp.actor)==visit.end()){
        visit.insert(actor_tmp.actor);
        if(actor2==actor_tmp.actor)break;
        //cout << "7" << endl;

        for(int i=0;i<(int)important[actor_tmp.actor].v.size();i++){
          movie_year_actor* rep=important[actor_tmp.actor].v[i];
          string nextactor=rep->actor;
          if(nextactor==actor_tmp.actor/*||visit.find(nextactor)!=visit.end()*/)continue;
          //int pos=0;
          //pos = thestr.find('\t', pos);
          //string movie_str=thestr.substr(0,pos);
          //string year_str=thestr.substr(pos+1);
          //int movie_year=atoi(year_str.c_str());
        //cout << nextactor << endl;
          if(!isu)cost_tmp=1+2018-rep->num_year;
          else cost_tmp=1;

          if(smallest_cost[nextactor]>smallest_cost[actor_tmp.actor]+cost_tmp){
            smallest_cost[nextactor]=smallest_cost[actor_tmp.actor]+cost_tmp;
            prev_actor_movie pam;
            pam.prev_actor=actor_tmp.actor;
            pam.prev_movie=rep->movie;
            pam.prev_year=rep->year;
            prevv[nextactor]=pam;
            actor_cost ac2;
            ac2.actor=nextactor;
            ac2.cost=smallest_cost[nextactor];
            p.push(ac2);
          }
        }
      }
    }
    string ans;
    string end=actor2;
    print_path(ans,actor1,end);
    ans.append("("+actor2+")");
    ofFile << ans << endl;
    //cout << smallest_cost[actor2] << endl;
    //cout << ans << endl;
    //cout << smallest_cost[actor2] << endl;
  }
  inFile2.close();
  ofFile.close();
  unordered_map<string,node_to_node>::iterator important_it;
  for(important_it=important.begin();important_it!=important.end();important_it++){
    for(int i=0;i<(int)important_it->second.v.size();i++){
      delete important_it->second.v[i];
    }
  }
  return 0;
}
