#include "../src/DocumentGenerator.hpp"
#include <iostream>
using namespace std;
int main() {
  //TODO your tests here
    DocumentGenerator d("../ex");
    cout << d.generateDocument(150000) << endl;
}
