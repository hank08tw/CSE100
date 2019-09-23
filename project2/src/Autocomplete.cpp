#include <iostream>
#include <algorithm>
#include "Autocomplete.hpp"
using namespace std;
void Autocomplete:: insert(const string& s,int cur,node* thenode){
    //cout << "insert: " << s << " cur:" << cur << endl;
    if(cur==s.length()){
        thenode->num++;
    }else{
	//cout << s[cur] << endl;
	if(thenode->m.find(s[cur])!=thenode->m.end()){
		insert(s,cur+1,thenode->m[s[cur]]);
	}else{
		thenode->m[s[cur]]=new node;
		thenode->m[s[cur]]->num=0;
		insert(s,cur+1,thenode->m[s[cur]]);
	}
    }
}
Autocomplete::Autocomplete(const vector<string> & corpus){
    //cout << "constructor" << endl;
    root=new node;
    root->m.clear();
    root->num=0;
    for(int i=0;i<(int)corpus.size();i++){
        insert(corpus[i],0,root);
    }
}
void Autocomplete::dfs(const string& s,int cur,node* thenode,vector<wf>& ans,string cur_word) const{
   //cout << "dfs,string: " << s << " cur: " << cur << " cur_word: " << cur_word << endl;
   if(cur<s.length()){
        if(thenode->m.find(s[cur])!=thenode->m.end()){
            dfs(s,cur+1,thenode->m[s[cur]],ans,cur_word+s[cur]);
        }else{
            return;
        }
    }else{
        if(thenode->num>0){
            wf* tmp=new wf;
	    tmp->word=cur_word;
	    tmp->freq=thenode->num;
	    ans.push_back(*tmp);
            delete tmp;
        }
        unordered_map <char,node*>::iterator it;
        for(it=thenode->m.begin();it!=thenode->m.end();it++){
            dfs(s,cur+1,it->second,ans,cur_word+it->first);
        }
    }
}
bool Autocomplete:: compare(wf a, wf b) {
        if(a.freq!=b.freq)return (a.freq > b.freq);
        else return a.word < b.word;//must use >
}
vector<string> Autocomplete::predictCompletions(const string & prefix) const{
    //cout << "predictcompletion,prefix: " << prefix << endl; 
    vector<wf> ans;
    string ss;
    dfs(prefix,0,root,ans,ss);
    //cout << "finish dfs" << endl;
    sort(ans.begin(),ans.end(),compare);
    //cout << "finish sort" << endl;
    vector<string> ans2;
    for(int i=0;i<10;i++){
	//cout << "push in ans: " << i << endl;
        if((int)ans.size()>i)ans2.push_back(ans[i].word);
	else break;
    }
    ans.clear();
    return ans2;
}
void Autocomplete::freenode(node* thenode){
    if(!thenode)return;
    unordered_map <char,node*>::iterator it;
    for(it=thenode->m.begin();it!=thenode->m.end();it++){
	freenode((*it).second);	
    }
    thenode->m.clear();
    delete thenode;
}
Autocomplete::~Autocomplete(){
    //cout << "destructor" << endl;
    freenode(root);
}
