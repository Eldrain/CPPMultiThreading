#include "stdafx.h"
#include "StartThread.h"
#include <vector>

StartThread::StartThread()
{
	best = NULL;	
}

void StartThread::StartSearch(int n) 
{
	bestF = 0;
	delete[] best;
	best = new int[n];
	bestF++;

	time = clock();
	int **var = new int*[n];

	std::vector<std::thread> threads;
	Crit *values = new Crit[n];

	for (int i = 0; i < n; i++) {
		var[i] = new int[n];
		ArrFunctions::clearArr(var[i], n);
		var[i][0] = i + 1;
		threads.emplace_back(&SearchSol::Search, new SearchSol, var[i], n, 1, &values[i], std::ref(mutexObj), std::ref(bestF), best);
	}

	for (int i = 0; i < n; i++)
	{
		threads[i].join();
		delete[] var[i];
		var[i] = NULL;
	}
	delete[] values;
	delete[] var;
	var = NULL;

	time = (clock() - time) / 1000;
}

double StartThread::GetTime() {
	return time;
}

void StartThread::PrintRes(int n) {
	ArrFunctions::printArr(best, n);
}

int StartThread::GetMinF() {
	return bestF;
}

StartThread::~StartThread()
{
	delete[] best;
}