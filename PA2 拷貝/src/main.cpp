#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>

#include "Autocomplete.hpp"

using namespace std;

const string whitespace = " \t\r\n\v\f";

//--------Utilities
//break a line over whitespace separators
//caller must delete returned vector
vector<string> * tokenize(const string & line) {
	vector<string> * words = new vector<string>();
	vector<char> word;
	for (unsigned char c : line) {
		if (whitespace.find(c) == string::npos) {
			word.push_back(c);
		} else if (word.size() > 0) {
			words->push_back(string(word.begin(), word.end()));
			word.clear();
		}
	}
	if (word.size() > 0) {
		words->push_back(string(word.begin(), word.end()));
	}
	return words;
}

//load a file and return a vector of all the words in that file
//this function only splits the contents of the file over whitespace
//and does not make exceptions for punctuation or unwanted characters
//caller must delete returned vector
vector<string> * getWords(const string & fileLocation) {
	vector<string> * words = new vector<string>();

	ifstream infile;
	infile.open(fileLocation);

	if (!infile) {
		cerr << "Couldn't open file: " << fileLocation << endl;
		exit(1);
	}

	string line;
	while(getline(infile, line)) {
		vector<string> * wordsInLine = tokenize(line);
		words->insert(words->end(), wordsInLine->begin(), wordsInLine->end());
		delete wordsInLine;
	}

	return words;  
}

//----------------Test runner
// generates predictions based on the dictionary at the given file location, using the given list of prefixes
// predictions are printed to cout:
// all the predictions for a single prefix are printed out in order on a single line, separated by spaces
// the predictions for each prefix are printed on their own line
void runTest(const string & fileLocation, const vector<string> & prefixes, int searchReps) {
  vector<string> * words = getWords(fileLocation);
  Autocomplete* autocomplete = new Autocomplete(*words);

  for (int i=0; i<searchReps; i++) {
    for (string prefix : prefixes) {
      vector<string> completions = autocomplete->predictCompletions(prefix);
      for (string completion : completions) {
        cout << completion << " ";
      } 
      cout << endl;
    }
  }

  delete autocomplete;
  delete words;
}

//------------main
//Example use: ./main path/to/corpus.txt prefix1 prefix2, e.g. ./main TestCases/ModerateCorpus w wasn't wasn'ta x
//First argument: path to the file containing the corpus of words to be loaded
//If the second argument is '-o', then its followed by a fixed number of arguments
//All the following arguments (or all the arguments after the first, if '-o' is not supplied)
//are prefixes to be completed
//e.g. ./main path/to/corpus.txt prefix1 prefix2 ...
// or ./main path/to/corpus.txt -o option1 prefix1 prefix2 ...
//currently, there is only one option
//option1: number of times to repeat the test
//instead of a list of prefixes, a file of prefixes can be supplied
//e.g. ./main path/to/corpus.txt -p path/to/prefixes.txt
//see runTest for output details
int main(int argc, const char ** argv) {

  bool waitingForArg = true;
  bool nextIdxNumReps = false;
  bool nextIdxSearchReps = false;
  bool nextIdxPrefixFile = false;
  
  unsigned int numRepetitions = 1;
  unsigned int numSearchReps = 1;
  vector<string> * prefixes = nullptr; 
  string pathToCorpus = "";
  int idx;
  for(idx = 1; idx < argc; idx ++) {
     if (nextIdxNumReps) {
      try {
        numRepetitions = stoi(string(argv[idx]));
        nextIdxNumReps = false;
      } catch (exception e) {
        cout << "-o option must be an integer - the number of repetitions" << endl;
        exit(-1);
      }
    } else if (nextIdxSearchReps) {
      try {
        numSearchReps = stoi(string(argv[idx]));
        nextIdxSearchReps = false;
      } catch (exception e) {
        cout << "-r option must be an integer - the number of search repetitions" << endl;
        exit(-1);
      }
    } else if (nextIdxPrefixFile) {
      prefixes = getWords(argv[idx]);
      nextIdxPrefixFile = false;
    } else if (string(argv[idx]).compare("-o") == 0) {
      nextIdxNumReps = true;
    } else if (string(argv[idx]).compare("-r") == 0) {
      nextIdxSearchReps = true;
    } else if (string(argv[idx]).compare("-p") == 0) {
      nextIdxPrefixFile = true;
    } else {
      pathToCorpus = string(argv[idx]);
      waitingForArg = false;
      idx += 1;
      break;
    }
  }

  if (waitingForArg) {
    cout << "expected another argument after the final flag (if any)" << endl;
    cout << "Need a name of a dictionary file as the final argument." << endl;
    exit(-1);
  }
  
  //Load prefixes, either from input vector or from file
  if (prefixes != nullptr) {
    for (unsigned int count = 0; count < numRepetitions; count ++) {
      runTest(pathToCorpus, *prefixes, numSearchReps);
    }
    delete prefixes;
  } else {
    vector<string> commandLinePrefixes;
    for (; idx < argc; idx ++) {
      commandLinePrefixes.push_back(argv[idx]);
    }
    for (unsigned int count = 0; count < numRepetitions; count ++) {
      runTest(pathToCorpus, commandLinePrefixes, numSearchReps);
    }
  }
}
