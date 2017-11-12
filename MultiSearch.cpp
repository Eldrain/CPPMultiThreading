// MultiSearch.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "StartThread.h"
#include <vector>
#include <iostream>

#define N 10

using namespace std;

void Search(int *var, int n, int set, Crit *value, std::mutex &mutexObj, int &bestF, int *best) {
	if (set < n) {
		int j = 0;
		for (int i = 0; i < n; i++) {
			j = 0;
			while (var[j] != 0)
				if (var[j] == i + 1)
					break;
				else
					j++;
			if (j == set) {
				var[set] = i + 1;
				Search(var, n, set + 1, value, mutexObj, bestF, best);
				var[set] = 0;
			}
		}
	}
	else {
		int f = 0;
		f = value->crit(var, set);

		mutexObj.lock();
		if (f > bestF) {
			bestF = f;
			ArrFunctions::copyArr(best, var, n);
		}
		mutexObj.unlock();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	StartThread thrd;
	StartThread::SearchSol sol;

	vector<thread> td;
	int **var = new int*[N];
	Crit *value = new Crit[N];
	int bestF = 0;
	int *best = new int[N];

	mutex mtx;

	for (int i = 0; i < N; i++)
	{
		var[i] = new int[N];
		ArrFunctions::clearArr(var[i], N);

		var[i][0] = i + 1;
		td.emplace_back(&Search, var[i], N, 1, &value[i], ref(mtx), ref(bestF), best);
	}

	for (int i = 0; i < N; i++)
	{
		td[i].join();
	}
	
	//thrd.StartSearch(N);
	cout << "Несколько потоков: f = " << bestF << "; time = " << thrd.GetTime() << "s. Array: ";
	ArrFunctions::printArr(best, N);

	ArrFunctions::clearArr(var[0], N);
	sol.Search(var[0], N, 0, &value[0], mtx, bestF, best);
	cout << "Один поток: f = " << bestF << "; time = " << thrd.GetTime() << "s. Array: ";
	ArrFunctions::printArr(best, N);

	delete[] var;
	delete[] best;
	delete[] value;
	return 0;
}

