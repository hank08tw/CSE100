#include "ActorGraph.hpp"
#include "MatrixMultiply.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
unordered_map<string,vector<string> > movieyear_actor;
unordered_map<string,vector<string> >::iterator movieyear_actor_it;
unordered_map<string,unordered_map<string,bool> > actor_actor;
unordered_map<string,int> allactor;
unordered_map<string,int>::iterator allactor_it;
struct actor_num{
  string actor;
  int value;
};
bool compare(actor_num left, actor_num right)
{
  if(left.value != right.value)return (left.value > right.value);
  return left.actor<right.actor;
}
bool compare2(actor_num left, actor_num right)
{
  if(left.value != right.value)return (left.value < right.value);
  return left.actor<right.actor;
}

int main(int argc, char *argv[]) {
  // TODO: Implement code for "Part 2: Link Predictor and Recommending New
  // Links"
  if(argc!=5){cout << "Please input 4 arguments!" << endl;return 0;}
  string input_path=argv[1];
  string input_path2=argv[2];
  string input_path3=argv[3];
  string input_path4=argv[4];
  ifstream inFile;
  inFile.open(input_path);
  if(!inFile){cout << "Cannot open the first file!" << endl;return 0;}
  string oneline;
  bool first=true;
  string actor,movie,year;
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
    string movieandyear=movie+'\t'+year;
    movieyear_actor[movieandyear].push_back(actor);
    allactor[actor]=0;
    //visit[actor]=false;
    //process[actor]=false;
  }
  inFile.close();
  vector<string> allactor2;
  for(allactor_it=allactor.begin();allactor_it!=allactor.end();allactor_it++){
    allactor2.push_back(allactor_it->first);
  }
  sort(allactor2.begin(),allactor2.end());


  for(int i=0;i<(int)allactor2.size();i++){
    allactor[allactor2[i]]=i;
  }
  /*
  for(int i=0;i<allactor2.size();i++){
    cout << allactor2[i] << endl;
    cout << allactor[allactor2[i]] << endl;
    cout << endl;
  }*/
  vector<vector<int> > v;
  for(int i=0;i<(int)allactor2.size();i++){
    vector<int> t;
    for(int j=0;j<(int)allactor2.size();j++){
      t.push_back(0);
    }
    v.push_back(t);
  }
  for(movieyear_actor_it=movieyear_actor.begin();movieyear_actor_it!=movieyear_actor.end();movieyear_actor_it++){
    for(int i=0;i<(int)movieyear_actor_it->second.size();i++){
      for(int j=0;j<(int)movieyear_actor_it->second.size();j++){
        actor_actor[movieyear_actor_it->second[i]][movieyear_actor_it->second[j]]=true;
        actor_actor[movieyear_actor_it->second[j]][movieyear_actor_it->second[i]]=true;
        v[allactor[movieyear_actor_it->second[i]]][allactor[movieyear_actor_it->second[j]]]=1;
        v[allactor[movieyear_actor_it->second[j]]][allactor[movieyear_actor_it->second[i]]]=1;
      }
    }
  }
  /*
  cout << v.size() << endl;
  cout << v[0].size() << endl;
  cout << allactor2.size() << endl;
  cout << allactor.size() << endl;
  */
  inFile.open(input_path2);
  //cout << "mid" << endl;
  ofstream ofFile1;
  ofstream ofFile2;
  ofFile1.open(input_path3);
  ofFile2.open(input_path4);
  if(!inFile){cout << "Cannot open the second file!" << endl;return 0;}
  first=true;
  ofFile1 << "Actor1,Actor2,Actor3,Actor4" << endl;
  ofFile2 << "Actor1,Actor2,Actor3,Actor4" << endl;
  while(getline(inFile,oneline)){
    if(first){first=false;continue;}
    //vector<int> t=;
    vector<vector<int> > t2;
    t2.push_back(v[allactor[oneline]]);
    MatrixOperations<int> m(t2,v);
    vector<vector<int> > a=m.matrixMultiply();
    //cout << a.size() << endl;
    vector<int> a1=a[0];
    vector<actor_num> an;
    for(int i=0;i<(int)a1.size();i++){
      actor_num tt;
      tt.value=a1[i];
      tt.actor=allactor2[i];
      an.push_back(tt);
    }
    sort(an.begin(),an.end(),compare);
    int count2=0;
    int i2=1;
    while(count2<4){
      if(i2>=(int)an.size())break;
      if(!actor_actor[oneline][an[i2].actor]){i2++;continue;}
      if(count2==0)ofFile1 << an[i2].actor;
      else ofFile1 << '\t' << an[i2].actor;
      count2++;
      i2++;
    }
    if(count2>0)ofFile1 << endl;
    /*
    for(int i=1;i<=min(4,(int)an.size()-1);i++){
      if(an[i].value==0)break;
      if(i==1)ofFile1 << an[i].actor; //<< " " << an[i].value;
      else ofFile1 << '\t' << an[i].actor; //<< " " << an[i].value;
    }
    ofFile1 << endl;
*/
    int cnt=0;
    int i=1;
    while(cnt<4){
      if(i>=(int)an.size())break;
      if(actor_actor[oneline][an[i].actor]){i++;continue;}
      if(cnt==0)ofFile2 << an[i].actor;
      else ofFile2 << '\t' << an[i].actor;
      cnt++;
      i++;
    }
    ofFile2 << endl;
    /*
    sort(an.begin(),an.end(),compare2);

    int i=1;
    while(i<(int)an.size()&&an[i].value==0)i++;

    for(int j=i;j<=min(i+3,(int)an.size()-1);j++){
      //if(an[j].value!=0)break;
      if(j==i)ofFile2 << an[j].actor; //<< " " << an[i].value;
      else ofFile2 << '\t' << an[j].actor; //<< " " << an[i].value;
    }
    ofFile2 << endl;
    */

  }
  inFile.close();
  ofFile1.close();
  ofFile2.close();
  return 0;
}
