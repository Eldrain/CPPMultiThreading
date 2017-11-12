#pragma once
#include "stdafx.h"

class Crit {
public:
	int crit(int *var, int n) {
		int f = 0;

		for (int i = 0; i < n; i++) {
			f += (i + 1)*var[n - i - 1];
		}
		return f;
	}
};