#include "decisiontree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  decisionTree dt;
  infoGain choice;
  dt.setStrategy(&choice);
  dt.buildFromFile("train.txt");

  std::ifstream in("test.txt");
  string line;
  vector<vector<string>> state;
  while(in) {
    std::getline(in, line);
    if(!line.empty()) {
      vector<string> columns;
      size_t last = line.find_first_not_of(" ,");
      size_t index = line.find_first_of(" ,", last);
      while(index != string::npos) {
        columns.push_back(line.substr(last, index - last));
        last = line.find_first_not_of(" ,", index);
        index = line.find_first_of(" ,", last);
      }
      if(index - last > 0) {
        columns.push_back(line.substr(last, index - last));
      }
      state.push_back(columns);
    }
  }
  for(int i = 0; i < state.size(); ++i) {
    cout<<dt.predict(state[i])<<endl;
  }
  return 0;
}
