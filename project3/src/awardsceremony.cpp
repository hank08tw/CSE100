#include "ActorGraph.hpp"
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
struct actor_value{
  int degree;
  string name;
};
class CustomCompare
{
public:
    bool operator()(actor_value& lhs, actor_value& rhs)
    {
        return lhs.degree > rhs.degree;
        //if(lhs.cost!=rhs.cost)
	      //return lhs.actor < rhs.actor;
    }
};

unordered_map<string,vector<string> > movieyear_actor;
unordered_map<string,vector<string> >::iterator movieyear_actor_it;
unordered_map<string,vector<string> > actor_actor;
unordered_map<string,unordered_map<string,bool> > actor_actor2;
unordered_map<string,int > actor_degree;

unordered_map<string,vector<string> >::iterator actor_actor_it;
//unordered_map<string,bool> allactor;
unordered_map<string,bool> visit;
unordered_map<string,bool> process;
unordered_map<string,int> vdegree;
int main(int argc, char *argv[]) {
  // TODO: Implement code for "Part 3: Award Ceremony Invitation"
  if(argc!=4){cout << "Please input 3 arguments!" << endl;return 0;}
  string input_path=argv[1];
  string input_path2=argv[2];
  string input_path3=argv[3];
  int k=atoi(input_path2.c_str());
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
    //numyear=atoi(year.c_str());
    string movieandyear=movie+'\t'+year;
    movieyear_actor[movieandyear].push_back(actor);
    //visit[actor]=false;
    //process[actor]=false;
  }
  inFile.close();

  for(movieyear_actor_it=movieyear_actor.begin();movieyear_actor_it!=movieyear_actor.end();movieyear_actor_it++){
    for(int i=0;i<(int)movieyear_actor_it->second.size();i++){
      for(int j=i+1;j<(int)movieyear_actor_it->second.size();j++){
        //if(i!=j){
        if(actor_actor2[movieyear_actor_it->second[i]].find(movieyear_actor_it->second[j])==actor_actor2[movieyear_actor_it->second[i]].end()){
          actor_actor[movieyear_actor_it->second[i]].push_back(movieyear_actor_it->second[j]);
          actor_actor2[movieyear_actor_it->second[i]][movieyear_actor_it->second[j]]=true;
        }
        if(actor_actor2[movieyear_actor_it->second[j]].find(movieyear_actor_it->second[i])==actor_actor2[movieyear_actor_it->second[j]].end()){
          actor_actor[movieyear_actor_it->second[j]].push_back(movieyear_actor_it->second[i]);
          actor_actor2[movieyear_actor_it->second[j]][movieyear_actor_it->second[i]]=true;
        }

        //}
      }
    }
  }
  for(actor_actor_it=actor_actor.begin();actor_actor_it!=actor_actor.end();actor_actor_it++){
      actor_degree[actor_actor_it->first]=actor_actor_it->second.size();
  }
  priority_queue<actor_value,vector<actor_value>, CustomCompare> p;
  //int sum=0;
  for(actor_actor_it=actor_actor.begin();actor_actor_it!=actor_actor.end();actor_actor_it++){
      actor_value tmp;
      tmp.name=actor_actor_it->first;
      tmp.degree=(int)actor_actor_it->second.size();
      //sum+=tmp.degree;
      p.push(tmp);
  }
  //cout << sum << endl;
  //cout << p.size() << endl;
  unordered_map<string,bool> removeactor;

  while(p.top().degree<k){//<=
    actor_value tmp=p.top();
    p.pop();
    if(removeactor.find(tmp.name)!=removeactor.end())continue;
    removeactor[tmp.name]=true;
    for(int i=0;i<(int)actor_actor[tmp.name].size();i++){
      if(removeactor.find(actor_actor[tmp.name][i])==removeactor.end()){
        actor_value tmp2;
        tmp2.name=actor_actor[tmp.name][i];
        --actor_degree[tmp2.name];
        tmp2.degree=actor_degree[tmp2.name];
        p.push(tmp2);
      }
    }
  }
  //cout << p.size() << endl;
  ofstream ofFile;
  ofFile.open(input_path3);
  if(!ofFile){cout << "Cannot open the second file!" << endl;return 0;}
  ofFile << "Actor" << endl;
  vector<string> ans;
  unordered_map<string,bool> alreadyinanswer;
  while(!p.empty()){
    actor_value tmp3=p.top();
    p.pop();
    if(removeactor.find(tmp3.name)==removeactor.end()&&alreadyinanswer.find(tmp3.name)==alreadyinanswer.end()){
      ans.push_back(tmp3.name);
      alreadyinanswer[tmp3.name]=true;
    }
  }
  sort(ans.begin(),ans.end());
  for(int i=0;i<(int)ans.size();i++){
    ofFile << ans[i] << endl;
  }

  ofFile.close();
  return 0;
}
/*
#include "ActorGraph.hpp"
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
unordered_map<string,vector<string> > actor_actor;
unordered_map<string,vector<string> >::iterator actor_actor_it;
//unordered_map<string,bool> allactor;
unordered_map<string,bool> visit;
unordered_map<string,bool> process;
unordered_map<string,int> vdegree;
bool dfs(string v, int k)
{
    visit[v] = true;
    for (int i = 0; i<actor_actor[v].size(); i++){
        if (vdegree[v] < k)vdegree[actor_actor[v][i]]--;
        if (!visit[actor_actor[v][i]])
        {
            if (dfs(actor_actor[v][i], k))
                vdegree[v]--;
        }
    }
    return (vdegree[v] < k);
}

int main(int argc, char *argv[]) {
  // TODO: Implement code for "Part 3: Award Ceremony Invitation"
  if(argc!=4){cout << "Please input 3 arguments!" << endl;return 0;}
  string input_path=argv[1];
  string input_path2=argv[2];
  string input_path3=argv[3];
  int k=atoi(input_path2.c_str());
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
    //numyear=atoi(year.c_str());
    string movieandyear=movie+'\t'+year;
    movieyear_actor[movieandyear].push_back(actor);
    visit[actor]=false;
    process[actor]=false;
  }
  inFile.close();
  //cout << "1" << endl;

  for(movieyear_actor_it=movieyear_actor.begin();movieyear_actor_it!=movieyear_actor.end();movieyear_actor_it++){
    for(int i=0;i<(int)movieyear_actor_it->second.size();i++){
      for(int j=i+1;j<(int)movieyear_actor_it->second.size();j++){
        actor_actor[movieyear_actor_it->second[i]].push_back(movieyear_actor_it->second[j]);
        actor_actor[movieyear_actor_it->second[j]].push_back(movieyear_actor_it->second[i]);
      }
    }
  }
  int minnum = 100000000;
  string start;

  //vector<int> vDegree(V);

  for (actor_actor_it=actor_actor.begin();actor_actor_it!=actor_actor.end();actor_actor_it++){
    vdegree[actor_actor_it->first]=actor_actor[actor_actor_it->first].size();
    if(vdegree[actor_actor_it->first]<minnum){
      minnum=vdegree[actor_actor_it->first];
      start=actor_actor_it->first;
    }
  }
  dfs(start, k);

  for(actor_actor_it=actor_actor.begin();actor_actor_it!=actor_actor.end();actor_actor_it++){
      if (!visit[actor_actor_it->first]) {
          dfs(actor_actor_it->first, k);
      }
  }

  ofstream ofFile;
  ofFile.open(input_path3);
  if(!ofFile){cout << "Cannot open the second file!" << endl;return 0;}

  ofFile << "Actor" << endl;
  vector<string> ans;
  for (actor_actor_it=actor_actor.begin();actor_actor_it!=actor_actor.end();actor_actor_it++){
      if (vdegree[actor_actor_it->first] >= k){
            //ofFile << actor_actor_it->first << endl;
            ans.push_back(actor_actor_it->first);
        }
  }
  sort(ans.begin(),ans.end());
  for(int i=0;i<(int)ans.size();i++){
    ofFile << ans[i] << endl;
  }
  ofFile.close();
  return 0;
}
*/
