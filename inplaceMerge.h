#include "algos.h"
#include "params.h"
#include "comparasions.h"

template <class Iter, class Iter2, class Compare>
int gallop(Iter first, Iter last, Iter2 to_cmp, Compare cmp) {
	//         [                ]
	int len = last - first + 1;
	int pw = 1;
	while (pw <= int(last - first)) {
		if (cmp(*to_cmp, *(first + pw))) {
			break;
		}
		pw <<= 1;
	}
	int left, right;
	if (pw <= int(last - first)) {
		left = pw >> 1;
		right = pw;
	} else {
		left = pw >> 1;
		right = len;
	}
	while (right - left > 1) {
		int mid = (right + left) >> 1;
		if (cmp(*to_cmp, *(first + mid))) {
			right = mid;
		} else {
			left = mid;
		}
	}
	assert((first + left) <= last);
	assert(!cmp(*to_cmp, *(first + left)));
	return left;
}

template <class Iter, class Iter2>
void Copy(Iter fir, Iter sec, Iter2 res) {
	//        [             ]
	int len = sec - fir + 1;
	for (int i = 0; i < len; ++i) {
		*(res + i) = *(fir + i);
	}
}

template <class iter, class Compare>
void useGallop(int &posm, iter &mid, int &len, iter &last, int &posl, Compare &cmp, iter &fir, int &posf, int &cntm, int &cntl){
    int next_posm = posm + gallop(mid + posm, mid + len - 1, last + posl, cmp);
    swap_ranges(mid + posm, mid + next_posm + 1, fir + posf);
    posf += next_posm - posm + 1;
    posm = next_posm + 1;
    cntm = 0;
    cntl = 0;
}

template <class iter, class Compare>
void mergeBlocks(iter fir, iter mid, iter last, int len, Compare cmp, const ITimSortParams &params) {
    assert(mid != last);
    assert(fir != last);
    for (int i = 0; i < len; i++) {
        iter_swap(fir + i, last + i);
    }
    int posf, posm, posl;
    posf = posm = posl = 0;
    int cntm, cntl;
    cntm = cntl = 0;
    while (posm < len && posl < len) {
        if (cntm == params.GetGallop() && lessEqual(mid + posm, last + posl, cmp)) {
            useGallop(posm, mid, len, last, posl, cmp, fir, posf, cntm, cntl);
            continue;
        } else if (cntl == params.GetGallop() && lessEqual(last + posl, mid + posm, cmp)) {
            useGallop(posl, last, len, last, posl, cmp, fir, posf, cntm, cntl);
            continue;
        }
        if (Less(mid + posm, last + posl, cmp)) {
            cntm++;
            cntl = 0;
            iter_swap(fir + posf++, mid + posm++);
        } else {
            cntl++;
            cntm = 0;
            iter_swap(fir + posf++, last + posl++);
        }
    }
    while (posm < len) {
        iter_swap(fir + posf++, mid + posm++);
    }
    while (posl < len) {
        iter_swap(fir + posf++, last + posl++);
    }
}

template <class Iter, class Iter2, class Compare>
int gallopBack(Iter end, Iter begin, Iter2 to_cmp, Compare cmp) {
	//         [                ]
	int len = begin - end + 1;
	int pw = 1;
	while (pw <= int(begin - end)) {
		if (cmp(*(begin - pw), *to_cmp)) {
			break;
		}
		pw <<= 1;
	}
	int left, right;
	if (pw <= int(begin - end)) {
		left = pw >> 1;
		right = pw;
	} else {
		left = pw >> 1;
		right = len;
	}
	while (right - left > 1) {
		int mid = (right + left) >> 1;
		if (cmp(*(begin - mid), *to_cmp)) {
			right = mid;
		} else {
			left = mid;
		}
	}
	assert((begin - left) >= end);
	assert(!cmp(*(begin - left), *to_cmp));
	return left;
}


template <class iter, class Compare>
void mergeBlocksBack(iter begin, iter first, iter mid, iter last, int s, Compare cmp, const ITimSortParams &params) {
	int len = int(first - begin) + 1;
	for (int i = 0; i < s; ++i) {
		iter_swap(mid - i, last - i);
	}
	int posf, posm, posl;
	posf = posm = posl = 0;
	int cntf, cntl;
	cntf = cntl = 0;
	while (posf < len && posl < s) {
		if (cntl == params.GetGallop() && lessEqual(first - posf, last - posl, cmp)) {
			int next_posl = posl + gallopBack(mid + 1, last - posl, first - posf, cmp);
			int p = 0;
			int steps = next_posl - posl + 1;
			int done = 0;
			for (iter i = last - posl; ; --i) {
				std::swap(*i, *(mid - posm - p++));
				done++;
				if (done == steps) break;
			}
			posm += next_posl - posl + 1;
			posl = next_posl + 1;
			cntl = 0;
			cntf = 0;
			continue;
		} else if (cntf == params.GetGallop() && lessEqual(last - posl, first - posf, cmp)) {
			int next_posf = posf + gallopBack(begin, first - posf, last - posl, cmp);
			int p = 0;
			int steps = next_posf - posf + 1;
			int done = 0;
			for (iter i = first - posf; ; --i) {
				std::swap(*i, *(mid - posm - p++));
				done++;
				if (done == steps) break;
			}
			posm += next_posf - posf + 1;
			posf = next_posf + 1;
			cntl = 0;
			cntf = 0;
			continue;
		}
		if (Less(first - posf, last - posl, cmp)) {
			cntl++;
			cntf = 0;
			iter_swap(mid - posm++, last - posl++);
		} else {
			cntf++;
			cntl = 0;
			iter_swap(mid - posm++, first - posf++);
		}
	}
	while (posl < s) {
		iter_swap(mid - posm++, last - posl++);
	}
	while (posf < len) {
		iter_swap(mid - posm++, first - posf++);
	}
}
template <class Iter, class Compare>
void inplaceMerge(Iter l1, Iter r1, Iter l2, Iter r2, Compare cmp, const ITimSortParams &params) {
	int lenl = r1 - l1 + 1;
	int lenr = r2 - l2 + 1;
	int len = lenl + lenr;
	if (len < 9) {
		slowSort(l1, r2 + 1, cmp);
		return;
	}
	int k = int(sqrt(len));
	int posMid = (lenl - 1) / k;
	int cnt_blocks = len / k;
	if (posMid < cnt_blocks) {
		swap_ranges(l1 + posMid * k, l1 + (posMid + 1) * k, l1 + (cnt_blocks - 1) * k);
	}
	for (int i = 0; i < cnt_blocks - 1; ++i) {
		int min_pos = i;
		for (int j = i + 1; j < cnt_blocks - 1; ++j) {
			if (Less(l1 + j * k, l1 + min_pos * k, cmp) || Equal(l1 + j * k, l1 + min_pos * k, cmp) && Less(l1 + (j * k + k - 1), l1 + (min_pos * k + k - 1), cmp)) {
				min_pos = j;
			}
		}
		swap_ranges(l1 + i * k, l1 + i * k + k, l1 + min_pos * k);
	}
	for (int i = 0; i < cnt_blocks - 2; ++i) {
		mergeBlocks(l1 + i * k, l1 + i * k + k, l1 + (cnt_blocks - 1) * k, k, cmp, params);
	}
	int s = k + len % k;
	assert(2 * s <= len);
	slowSort(r2 - (2 * s - 1), r2 + 1, cmp);
	mergeBlocksBack(l1, r2 - 2 * s, r2 - s, r2, s, cmp, params);
	slowSort(r2 - (2 * s - 1), r2 + 1, cmp);
}
