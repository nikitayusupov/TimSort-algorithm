#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using std::vector;
using std::cin;
using std::endl;
using std::cout;
using std::pair;
using std::swap_ranges;
using std::iter_swap;

template <class Iter, class Compare>
void slowSort(Iter begin, Iter end, Compare cmp) {
	for (Iter i = begin; i < end; ++i) {
		for (Iter j = i + 1; j < end; ++j) {
			if (!Less(i, j, cmp)) {
				iter_swap(i, j);
			}
		}
	}
}

template <class Iter>
void Reverse(Iter begin, Iter end) {
	int n2 = int(end - begin) / 2;
	Iter i = begin, j = end - 1;
	for (int cnt = 0; cnt < n2; ++cnt) {
		iter_swap(i, j);
		++i;
		--j;
	}
}
