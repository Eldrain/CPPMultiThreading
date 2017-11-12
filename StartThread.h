#pragma once
#include <list>
#include <thread>
#include <mutex>
#include "Crit.cpp"
#include "ArrFunctions.cpp"

class StartThread
{
private:
	std::list<std::thread> threads;
	std::mutex mutexObj;
	int bestF;
	int *best;
	double time;

public:
	StartThread();

	void StartSearch(int n);

	//void Search(int *var, int n, int set, Crit *value);

	double GetTime();

	void PrintRes(int n);

	int GetMinF();

	~StartThread();

	class SearchSol {
	public:
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
	};
};