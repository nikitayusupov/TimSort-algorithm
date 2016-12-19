#include "inplaceMerge.h"
#include "merges.h"
#include "checks.h"

template <class Iter, class Compare>
void movePos(int &curLen, int &length, int &n, int &pos, Iter &begin, Compare &cmp){
    int curLen2 = curLen;
    curLen = Min(length, curLen + (n - pos) - 1);
    pos = Min(pos + (length - curLen2), n - 1);
    slowSort(begin + (pos + 1 - curLen), begin + (pos + 1), cmp);
}

template <class Iter, class Compare>
void updateRuns(vector<pair<Iter, int> > &runs, int &pos, Iter &begin, int &curLen, Compare &cmp, MonotonyType &monotony, const ITimSortParams &params){
    runs.push_back({begin + (pos + 1 - curLen), curLen});
    mergeRuns(runs, cmp, params);
    monotony = undefined;
    curLen = 1;
}
