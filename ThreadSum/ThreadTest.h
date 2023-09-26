#pragma once

#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iostream>

class ThreadTest
{
public:
	ThreadTest() { initialize(1); }; // —разу герерируетс€ массив с максимальным количеством случайных элементов
	ThreadTest(int num) { initialize(num); }; //  оличество потоков
	ThreadTest(std::vector<int> arr);
	~ThreadTest() = default;

	void startTest();
	void startTestTest();
	void setNumThread(int num) { _numThread = num; };

private:
	int _numThread;
	std::vector<int> _arr;
	int _sizeVector = 16777216; // 16 в 6 степени!

	void initialize(int num);
	void threadTest(int sizeVector);
	int getNumThread() { return _numThread; };
};

