#include "../src/Autocomplete.hpp"
#include <vector>
#include <iostream>
using namespace std;
int main() {
  //TODO your tests here
    vector<string> s;
    s.push_back("abcá");
    s.push_back("abcá");
    s.push_back("abc");
    s.push_back("abcd");
    s.push_back("abcde!");
    s.push_back("abcaf!");
    s.push_back("abc!");
    s.push_back("abcdadlkfj!");
    s.push_back("abc!");
    s.push_back("abcdesdlkfj!");
    s.push_back("abc");
    s.push_back("abcdoeiru");
    s.push_back("a");
    s.push_back("bc");
    s.push_back("abcdecoivu");
    s.push_back("abcdofu");
    s.push_back("abcdqpwoei");
    s.push_back("abcdezpxociuv");
    Autocomplete test(s);
    string lookup="abc";
    vector<string> ans=test.predictCompletions(lookup);
    for(int i=0;i<ans.size();i++){
        cout << i+1 << ":" << ans[i] << endl;
    }
    return 0;
}
