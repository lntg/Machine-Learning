#ifndef __DECISIONTREE_H_
#define __DECISIONTREE_H_

#include <string>
#include <vector>
#include <map>
#include "dividestrategy.h"
#include "treenode.h"

using std::map;
using std::string;
using std::vector;

class decisionTree {
public:
  int buildFromFile(string file_name);
  string predict(const vector<string>& sample);
  void setStrategy(divideStrategy* strategy);

private:
  treeNode* generate(vector<vector<string>>& dataset, vector<int>& attr);
  bool isAllInSameClass(vector<vector<string>>& dataset);
  bool isAllSameAttrValue(vector<vector<string>>& dataset, vector<int>& attr);
  string getMaxClass(vector<vector<string>>& dataset);
  map<string, vector<vector<string>>> getSubs(vector<vector<string>>& dataset, int attr);
  treeNode* root;
  divideStrategy* choice;
};

#endif
