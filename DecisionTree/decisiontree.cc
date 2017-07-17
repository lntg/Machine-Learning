#include "decisiontree.h"
#include <fstream>



int decisionTree::buildFromFile(string file_name) {
  std::ifstream in(file_name.c_str());
  string line;
  vector<vector<string>> state;
  vector<int> attributes;
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
  if(state.size() > 0) {
    for(int i = 0; i < state[0].size() - 1; ++i) {
      attributes.push_back(i);
    }
  }

  root = generate(state, attributes);
  return 0;
}

string decisionTree::predict(const vector<string>& sample) {
  return root->find(sample);
}

void decisionTree::setStrategy(divideStrategy* strategy) {
  choice = strategy;
}

bool decisionTree::isAllInSameClass(vector<vector<string>>& dataset) {
  int pre = 0;
  for(int curr = 1;curr < dataset.size(); ++curr) {
    if(dataset[pre].back() != dataset[curr].back()) return false;
  }
  return true;
}

bool decisionTree::isAllSameAttrValue(vector<vector<string>>& dataset, vector<int>& attr) {
  int pre = 0;
  for(int curr = 1;curr < dataset.size(); ++curr) {
    for(int j = 0; j < attr.size(); ++j) {
      if(dataset[pre][attr[j]] != dataset[curr][attr[j]]) return false;
    }
  }
  return true;
}

string decisionTree::getMaxClass(vector<vector<string>>& dataset) {
  map<string, int> class_count;
  for(int i = 0; i < dataset.size(); ++i) {
    class_count[dataset[i].back()]++;
  }
  string max_str;
  int max_num = 0;
  for(map<string, int>::iterator iter = class_count.begin(); iter != class_count.end(); ++iter) {
    if(max_num < iter->second) {
      max_num = iter->second;
      max_str = iter->first;
    }
  }

  return max_str;
}

map<string, vector<vector<string>>> decisionTree::getSubs(vector<vector<string>>& dataset, int attr) {
  map<string, vector<vector<string>>> result;
  for(int i = 0; i < dataset.size(); ++i) {
    string attr_str = dataset[i][attr];
    result[attr_str].push_back(dataset[i]);
  }
  return result;
}

treeNode* decisionTree::generate(vector<vector<string>>& dataset, vector<int>& attr) {
  if(isAllInSameClass(dataset) || attr.size() == 0 || isAllSameAttrValue(dataset, attr)) {
    treeNode* top = new leaf(getMaxClass(dataset));
    return top;
  }

  int attr_i = choice->getDivideAttr(dataset, attr);
  vector<int> sub_attr = attr;
  for(int i = 0; i < sub_attr.size(); ++i) {
    if(sub_attr[i] == attr_i) {
      sub_attr.erase(sub_attr.begin() + i);
      break;
    }
  }
  treeNode* top = new branch(attr_i);

  map<string, vector<vector<string>>> sub_sets = getSubs(dataset, attr_i);
  for(map<string, vector<vector<string>>>::iterator iter = sub_sets.begin();
                                      iter != sub_sets.end(); ++iter) {
    treeNode* child = NULL;
    child = generate(iter->second, sub_attr);
    top->setchild(iter->first, child);
  }

  treeNode* child = NULL;
  child = new leaf(getMaxClass(dataset));
  top->setchild("other", child);

  return top;
}
