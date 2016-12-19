#include "inplaceMerge.h"
#include "merges.h"

template <class Iter, class Compare>
void checkIfLast(int &pos, int &n, MonotonyType &monotony, int &curLen, Iter &begin, Compare &cmp, vector<pair<Iter, int> > &runs,  const ITimSortParams &params){
    if (monotony == decreasing) {
        Reverse(begin + (pos + 1 - curLen), begin + pos + 1);
    }
    runs.push_back({begin + (pos + 1 - curLen), curLen});
    mergeRuns(runs, cmp, params);
}

template <class Iter, class Compare>
void checkIfUndefined(int &pos, int &n, MonotonyType &monotony, int &curLen, Iter &begin, Compare &cmp, vector<pair<Iter, int> > &runs,  const ITimSortParams &params){
    if (greaterEqual(begin + pos + 1, begin + pos, cmp)) {
        monotony = nonDecreasing;
    } else {
        monotony = decreasing;
    }
    ++curLen;
}

template <class Iter, class Compare>
void checkIfDecreasing(int &pos, int &n, MonotonyType &monotony, int &curLen, int &length, Iter &begin, Compare &cmp, vector<pair<Iter, int> > &runs,  const ITimSortParams &params){
    if (lessEqual(begin + pos + 1, begin + pos, cmp)) {
        ++curLen;
    } else {
        if (curLen < length) {
            movePos(curLen, length, n, pos, begin, cmp);
        } else {
            Reverse(begin + (pos + 1 - curLen), begin + pos + 1);
        }
        updateRuns(runs, pos, begin, curLen, cmp, monotony, params);
    }
}

template <class Iter, class Compare>
void checkIfNonDecreasing(int &pos, int &n, MonotonyType &monotony, int &curLen, int &length, Iter &begin, Compare &cmp, vector<pair<Iter, int> > &runs,  const ITimSortParams &params){
    if (greaterEqual(begin + pos + 1, begin + pos, cmp)) {
        ++curLen;
    } else {
        if (curLen < length) {
            movePos(curLen, length, n, pos, begin, cmp);
        }
        updateRuns(runs, pos, begin, curLen, cmp, monotony, params);
    }
}
