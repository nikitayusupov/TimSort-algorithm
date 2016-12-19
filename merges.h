#include "inplaceMerge.h"

template <class Iter, class Compare>
void mergeAt(vector<pair<Iter, int> > &runs, int pos, Compare cmp, const ITimSortParams &params) {
	Iter l1 = runs[pos].first, r1 = runs[pos].first + runs[pos].second - 1, l2 = runs[pos + 1].first, r2 = runs[pos + 1].first + runs[pos + 1].second - 1;
	int sz = runs.size();
	runs[pos].second += runs[pos + 1].second;
	if (pos == sz - 3) {
		runs[pos + 1] = runs[pos + 2];
	}
	runs.pop_back();
	inplaceMerge(l1, r1, l2, r2, cmp, params);
}

template <class Iter, class Compare>
void mergeRuns(vector<pair<Iter, int> > &runs, Compare cmp, const ITimSortParams &params) {
	while (runs.size() > 1) {
		int n = runs.size() - 2;
		if ((n > 0 && runs[n - 1].second <= runs[n].second + runs[n + 1].second) ||
			(n > 1 && runs[n - 2].second <= runs[n - 1].second + runs[n].second)) {
			if (runs[n - 1].second < runs[n + 1].second) {
				--n;
			}
			mergeAt(runs, n, cmp, params);
		} else if (runs[n].second <= runs[n + 1].second) {
			mergeAt(runs, n, cmp, params);
		} else {
			break;
		}
	}
}

template <class Iter, class Compare>
void mergeAllRuns(vector<pair<Iter, int> > &runs, Compare cmp, const ITimSortParams &params) {
	while (runs.size() > 1) {
		int n = runs.size() - 2;
		if (n > 0 && runs[n - 1].second < runs[n + 1].second) {
			--n;
		}
		mergeAt(runs, n, cmp, params);
	}
}
