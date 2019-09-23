#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdlib.h>

#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "DocumentGenerator.hpp"
using namespace std;
DocumentGenerator::DocumentGenerator(const string & documentsDirectory){
	vector<string> file_name;
	DIR* d;
	struct dirent *dir;
	d = opendir(documentsDirectory.c_str());
	if (d){
		while ((dir = readdir(d)) != NULL){
                	if (dir->d_name[0] == '.')continue;
                	string tmp = documentsDirectory + "/"+ dir->d_name;
                	file_name.push_back(tmp);
		}
	}
	closedir(d);
	ifstream inFile;
        for(int i=0;i<(int)file_name.size();i++){
		//ifstream inFile;
		inFile.open(file_name[i]);
		vector<string> v;
		string tmp;
		string word="";
		while(inFile >> tmp){
			//string word;
			for(int j=0;j<tmp.length();j++){
				string s(1,tmp[j]);
				size_t punctuation = PUNCTUATION.find_first_of(tmp[j]);
				if (punctuation != string::npos){
					if(!word.empty()){
						v.push_back(word);
						word="";
					}
					v.push_back(s);
					continue;
                    		}
				size_t unwanted = UNWANTED_CHARACTERS.find_first_of(tmp[j]);
				if(unwanted != string::npos){
					continue;
				}
				word=word.append(s);
			}
			if(!word.empty()){v.push_back(word);word="";}
		}
		//for(int j=0;j<v.size();j++)cout << v[j] << endl;
		for(int j=0;j<v.size()-1;j++){
			m[v[j]].push_back(v[j+1]);
		}
		inFile.close();
	}
	/*
	for(int a=0;a<(int)ans.size();a++){
	vector<string> v;
	string tmp;
	for(int i=0;i<ans[a].length();i++){
		bool unwant=false;

		for(int j=0;j<UNWANTED_CHARACTERS.length();j++){
			if(ans[a][i]==UNWANTED_CHARACTERS[j]){
				unwant=true;
				break;
			}
		}

		if(unwant)continue;

		if(ans[a][i]==PUNCTUATION[0]){
			if(tmp!=""){
				v.push_back(tmp);
				tmp="";
			}
			v.push_back(".");
			continue;
		}
		if(ans[a][i]==PUNCTUATION[1]){
                        if(tmp!=""){
                                v.push_back(tmp);
                                tmp="";
                        }
                        v.push_back("!");continue;
                }
		if(ans[a][i]==PUNCTUATION[2]){
                        if(tmp!=""){
                                v.push_back(tmp);
                                tmp="";
                        }
                        v.push_back(",");continue;
                }
		if(ans[a][i]==PUNCTUATION[3]){
                        if(tmp!=""){
                                v.push_back(tmp);
                                tmp="";
                        }
                        v.push_back("?");continue;
                }

		if(ans[a][i]==' '){
                        if(tmp!=""){
                                v.push_back(tmp);
                                tmp="";
                        }
			continue;
                }
		tmp=tmp+ans[a][i];
	}
	if(tmp!=""){v.push_back(tmp);tmp="";}
	for(int i=0;i<(int)v.size()-1;i++){
		m[v[i]].push_back(v[i+1]);
	}
	}
*/
	
}
string DocumentGenerator::generateNextWord(const string & prevWord){
	if(m.find(prevWord)==m.end())return ".";
	return m[prevWord][rand()%((int)m[prevWord].size())];
}
string DocumentGenerator::generateDocument(const int numWords){
	string ans="";
	string first=".";
	ans=ans.append(generateNextWord(first));
	string prev=ans;
	for(int i=1;i<numWords;i++){
		string getNext=generateNextWord(prev);
		if(getNext=="."||getNext=="!"||getNext==","||getNext=="?"){
			ans=ans.append(getNext);
		}
		else{ ans=ans.append(" ");ans=ans.append(getNext);}
		prev=getNext;
	}
	return ans;
}
DocumentGenerator::~DocumentGenerator(){
	m.clear();
}
