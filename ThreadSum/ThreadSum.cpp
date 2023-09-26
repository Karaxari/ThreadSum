#include "ThreadTest.h"

int main()
{
    setlocale(LC_ALL, "rus");
    //std::vector<int> arr = { 5,3,2,4,8,9,6,1,1,7,9,3,8,2,6,3,5,5,4,7 };
    //ThreadTest* test = new ThreadTest(arr);
    //test->startTestTest();

    ThreadTest* testThread = new ThreadTest(1);

    testThread->startTest();
    // остыль с задержкой!, так как реализаци€ с использованием единного вектора данных привела к состо€нию гонки )))
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    testThread->setNumThread(2);
    testThread->startTest();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    testThread->setNumThread(4);
    testThread->startTest();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    testThread->setNumThread(8);
    testThread->startTest();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    testThread->setNumThread(16);
    testThread->startTest();
}