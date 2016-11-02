#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "timSort.h"

using std::string;
using std::vector;
using std::cin;
using std::endl;
using std::sort;
using std::cout;
using std::pair;
using std::clock;
using std::swap_ranges;
using std::iter_swap;

void testVector(int n) {
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = rand();
	}
	vector<int> b = a;
	int tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	sort(b.begin(), b.end());
	int tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " ints std::sort " << tm2 - tm1 << "ms\n";
	tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	timSort(a.begin(), a.end());
	tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " ints timSort " << tm2 - tm1 << "ms\n";
	assert(a == b);
}

void testArray(int n) {
	int *a = new int[n];
	int *b = new int[n];
	for (int i = 0; i < n; ++i) {
		a[i] = rand();
		b[i] = a[i];
	}
	int tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	sort(b, b + n);
	int tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "array " << n << " ints std::sort " << tm2 - tm1 << "ms\n";
	tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	timSort(a, a + n);
	tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "array " << n << " ints timSort " << tm2 - tm1 << "ms\n";
	for (int i = 0; i < n; ++i) {
		if (a[i] != b[i]) {
			throw 1;
		}
	}
}

struct Point {
	int x, y, z;
	Point() {}
	Point(int x, int y, int z): x(x), y(y), z(z) {}
};

bool cmp(Point a, Point b) {
	if (a.x != b.x) {
		return a.x < b.x;
	}
	if (a.y != b.y) {
		return a.y < b.y;
	}
	return a.z < b.z;
}

bool operator == (Point a, Point b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

void testPoints(int n) {
	vector<Point> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = Point(rand(), rand(), rand());
	}
	vector<Point> b = a;
	int tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	sort(b.begin(), b.end(), cmp);
	int tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " Points std::sort " << tm2 - tm1 << "ms\n";
	tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	timSort(a.begin(), a.end(), cmp);
	tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " Points timSort " << tm2 - tm1 << "ms\n";
	assert(a == b);
}

void testStrings(int n) {
	vector<string> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = "";
		for (int j = 0; j < 100; j++) {
			a[i] += rand() % 25 + 'a';
		}
	}
	vector<string> b = a;
	int tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	sort(b.begin(), b.end());
	int tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " strings std::sort " << tm2 - tm1 << "ms\n";
	tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	timSort(a.begin(), a.end());
	tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
	cout << "vector " << n << " strings timSort " << tm2 - tm1 << "ms\n";
	assert(a == b);
}

void testSorted() {
	int lens[] = {20, 40, 80, 128, 1024};
	int cnt[] = {2, 4, 10, 100, 1000, 10000};
	for (int L = 0; L < 5; ++L) {
		for (int C = 0; C < 6; ++C) {
			int n = lens[L] * cnt[C];
			vector<int> a(n);
			for (int i = 0; i < n; ++i) a[i] = rand();
			for (int i = 0; i < cnt[C]; ++i) {
				sort(a.begin() + i * lens[L], a.begin() + (i + 1) * lens[L]);
			}
			vector<int> b = a;
			int tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
			sort(b.begin(), b.end());
			int tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
			cout << "vector of " << cnt[C] << " arrays " << " of length " << lens[C] << " std::sort " << tm2 - tm1 << "ms\n";
			tm1 = int(clock()*1000.0 / CLOCKS_PER_SEC);
			timSort(a.begin(), a.end());
			tm2 = int(clock()*1000.0 / CLOCKS_PER_SEC);
			cout << "vector of " << cnt[C] << " arrays " << " of length " << lens[C] << " timSort " << tm2 - tm1 << "ms\n";
			assert(a == b);
		}
	}
}

int main() {
	freopen("ou.txt", "wt", stdout);
	testVector(100500);
	testVector(50);
	testArray(100500);
	testArray(50);
	testPoints(100500);
	testStrings(10200);
	testSorted();
}