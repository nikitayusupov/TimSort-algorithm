#include "inplaceMerge.h"
#include "merges.h"
#include "checks.h"
#include "updates.h"

enum MonotonyType {
	undefined,
	decreasing,
	nonDecreasing
};

template <class Iter, class Compare>
void timSort(Iter begin, Iter end, Compare cmp, const ITimSortParams &params) {
    int n = end - begin;
    if (n == 1) {
        return;
    }
    int length = params.minRun(n);
    vector<pair<Iter, int> > runs;
    int curLen = 1;
    int pos = 0;
    MonotonyType monotony = undefined;
    while (pos < n) {
        if (pos + 1 == n) {
            checkIfLast(pos, n, monotony, curLen, begin, cmp, runs, params);
            break;
        }
        if (monotony == undefined) {
            checkIfUndefined(pos, n, monotony, curLen, begin, cmp, runs, params);
        } else if (monotony == decreasing) {
            checkIfDecreasing(pos, n, monotony, curLen, length, begin, cmp, runs, params);
        } else if (monotony == nonDecreasing) {
            checkIfNonDecreasing(pos, n, monotony, curLen, length, begin, cmp, runs, params);
        }
        ++pos;
    }
    mergeAllRuns(runs, cmp, params);
    assert(runs.size() == 1);
}

template <class Iter, class Compare>
void timSort(Iter begin, Iter end, Compare cmp) {
	timSort(begin, end, cmp, TimSortParams());
}

template <class Iter>
void timSort(Iter begin, Iter end) {
	typedef typename std::iterator_traits<Iter>::value_type value_type;
	std::less<value_type> cmp = std::less<value_type>();
	timSort(begin, end, cmp, TimSortParams());
}
