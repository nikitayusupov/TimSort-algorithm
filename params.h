enum EWhatMerge {
	WM_NoMerge,
	WM_MergeXY,
	WM_MergeYZ
};

class ITimSortParams {
public:
	virtual int minRun(int n) const = 0;
	virtual bool needMerge(int lenX, int lenY) const = 0;
	virtual EWhatMerge whatMerge(int lenX, int lenY, int lenZ) const = 0;
	virtual int GetGallop() const = 0;
};

class TimSortParams: public ITimSortParams {
public:
	int minRun(int n) const {
		int flag = 0;
		while (n >= 64) {
			flag |= n & 1;
			n >>= 1;
		}
		return n + flag;
	}
	bool needMerge(int lenX, int lenY) const {
		return lenX <= lenY;
	}
	int GetGallop() const {
		return 7;
	}
	EWhatMerge whatMerge(int lenX, int lenY, int lenZ) const {
		if (lenZ <= lenY + lenX) {
			if (lenZ < lenX) {
				return WM_MergeYZ;
			}
			return WM_MergeXY;
		} else if (lenY <= lenX) {
			return WM_MergeXY;
		} else {
			return WM_NoMerge;
		}
	}
};

