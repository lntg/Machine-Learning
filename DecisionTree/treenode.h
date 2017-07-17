#ifndef __TREENODE_H_
#define __TREENODE_H_

#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

class treeNode {
public:
  virtual string find(const vector<string>& sample) = 0;
  virtual void setchild(string val, treeNode* childNode) {}
  virtual ~treeNode() {}
private:
};

class leaf : public treeNode {
public:
  explicit leaf(string c) : cluster(c) {}
  string find(const vector<string>& sample);

private:
  string cluster;
};

class branch : public treeNode {
public:
  explicit branch(int attribute) : attr(attribute) {}
  string find(const vector<string>& sample);
  void setchild(string val, treeNode* childNode);

private:
  map<string, treeNode*> child;
  int attr;
};

#endif
