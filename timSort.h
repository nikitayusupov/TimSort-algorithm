#include "inplaceMerge.h"
#include "merges.h"

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
			if (monotony == decreasing) {
				Reverse(begin + (pos + 1 - curLen), begin + pos + 1);
			}
			runs.push_back({begin + (pos + 1 - curLen), curLen});
			mergeRuns(runs, cmp, params);
			break;
		}
		if (monotony == undefined) {
			if (greaterEqual(begin + pos + 1, begin + pos, cmp)) {
				monotony = nonDecreasing;
			} else {
				monotony = decreasing;
			}
			++curLen;
		} else if (monotony == decreasing) {
			if (lessEqual(begin + pos + 1, begin + pos, cmp)) {
				++curLen;
			} else {
				if (curLen < length) {
					int curLen2 = curLen;
					curLen = Min(length, curLen + (n - pos) - 1);
					pos = Min(pos + (length - curLen2), n - 1);
					slowSort(begin + (pos + 1 - curLen), begin + (pos + 1), cmp);
				} else {
					Reverse(begin + (pos + 1 - curLen), begin + pos + 1);
				}
				runs.push_back({begin + (pos + 1 - curLen), curLen});
				mergeRuns(runs, cmp, params);
				monotony = undefined;
				curLen = 1;
			}
		} else if (monotony == nonDecreasing) {
			if (greaterEqual(begin + pos + 1, begin + pos, cmp)) {
				++curLen;
			} else {
				if (curLen < length) {
					int curLen2 = curLen;
					curLen = Min(length, curLen + (n - pos) - 1);
					pos = Min(pos + (length - curLen2), n - 1);
					slowSort(begin + (pos + 1 - curLen), begin + (pos + 1), cmp);
				}
				runs.push_back({begin + (pos + 1 - curLen), curLen});
				mergeRuns(runs, cmp, params);
				monotony = undefined;
				curLen = 1;
			}
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
