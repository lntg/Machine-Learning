#include "treenode.h"

string leaf::find(const vector<string>& sample) {
  return cluster;
}

string branch::find(const vector<string>& sample) {
  string attr_val = sample[attr];
  if(child.find(attr_val) == child.end()) attr_val = "other";
  return child[attr_val]->find(sample);
}

void branch::setchild(string val, treeNode* childNode) {
  child[val] = childNode;
}
