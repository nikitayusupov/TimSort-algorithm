template<class C>
C Min(C a, C b) {
	return a < b ? a : b;
}

template <class Iter, class Compare>
bool Less(Iter first, Iter second, Compare cmp) {
	return cmp(*first, *second);
}

template <class Iter, class Compare>
bool Equal(Iter first, Iter second, Compare cmp) {
	return !Less(first, second, cmp) && !Less(second, first, cmp);
}

template <class Iter, class Compare>
bool lessEqual(Iter first, Iter second, Compare cmp) {
	return Less(first, second, cmp) || Equal(first, second, cmp);
}

template <class Iter, class Compare>
bool greater(Iter first, Iter second, Compare cmp) {
	return !lessEqual(first, second, cmp);
}

template <class Iter, class Compare>
bool greaterEqual(Iter first, Iter second, Compare cmp) {
	return greater(first, second, cmp) || Equal(first, second, cmp);
}

