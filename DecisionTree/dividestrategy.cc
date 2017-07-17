#include "dividestrategy.h"
#include <math.h>
#include <map>

using std::map;

int infoGain::getDivideAttr(vector<vector<string>>& dataset, vector<int>& attr) {
  double max_entropy = 0.0;
  int max_attr = 0;
  map<string, int> p_dv_count;
  for(int i = 0; i < attr.size(); ++i) {
    map<string, int> dv_count;
    map<string, map<string, int>> dv_pk;
    for(int j = 0; j < dataset.size(); ++j) {
      string attr_val = dataset[j][attr[i]];
      dv_count[attr_val]++;
      dv_pk[attr_val][dataset[j].back()]++;
      if(i == 0) {
        p_dv_count[dataset[j].back()]++;
      }
    }

    double sum_entropy = 0.0;
    for(map<string, int>::iterator iter = dv_count.begin(); iter != dv_count.end(); ++iter) {
      double entropy = 0.0;
      for(map<string, int>::iterator iter_inner = dv_pk[iter->first].begin(); iter_inner != dv_pk[iter->first].end(); ++iter_inner) {
        double pk = iter_inner->second * 1.0 / iter->second;
        entropy += pk * log(pk) / log(2);
      }
      entropy *= iter->second;
      sum_entropy += entropy;
    }

    if(i == 0) {
      max_attr = attr[i];
      max_entropy = sum_entropy;
    }
    else if(max_entropy < sum_entropy) {
      max_attr = attr[i];
      max_entropy = sum_entropy;
    }
  }

  return max_attr;
}
