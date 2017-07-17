#ifndef __DIVIDESTRATEGY_H
#define __DIVIDESTRATEGY_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class divideStrategy {
public:
  virtual int getDivideAttr(vector<vector<string>>& dataset, vector<int>& attr) = 0;
};

class infoGain : public divideStrategy {
  int getDivideAttr(vector<vector<string>>& dataset, vector<int>& attr);
};

#endif
