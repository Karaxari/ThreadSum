#include "ThreadTest.h"

ThreadTest::ThreadTest(std::vector<int> arr)
{
    _numThread = 4;
    _sizeVector = arr.size();
    _arr.reserve(_sizeVector);
    std::copy(arr.begin(), arr.end(), std::back_inserter(_arr));
}

void ThreadTest::initialize(int num)
{
    _numThread = num;
    _arr.reserve(_sizeVector); // ����������� ����������� �������

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    for (int i = 0; i < _sizeVector; ++i) {
        _arr.push_back(dist(gen));
    }
}

void ThreadTest::threadTest(int sizeVector)
{
    auto start = std::chrono::high_resolution_clock::now(); // ��������� ����� ������ ������ ���������

    std::vector<int> arr;
    arr.reserve(_arr.size());
    std::copy(_arr.begin(), std::begin(_arr) + sizeVector, std::back_inserter(arr));

    std::vector<std::thread> threads;
    std::vector<int> arrSum = {};
    int dif = sizeVector / _numThread; // _numThread - ������ ���� ������ sizeVector, ����� ����� ������� ��������� �������!

    for (int i = 0; i < _numThread; i++)
    {
        int start = i * dif;
        int end = start + dif;

        // ����� ������� ��������, �� ���������� ��� ������ ), �� ���������� ��������� ����� ��� ���������� ����� ������� ���������� � arrSum
        threads.push_back(std::thread([&arrSum, arr, start, end]()
            { arrSum.push_back(std::accumulate(std::begin(arr) + start, std::begin(arr) + end, int(), [](int a, int b) {
                return std::move(a) + b;
                }));
            })
        );
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread& t)
        { t.join(); });

    int sum = std::accumulate(arrSum.begin(), arrSum.end(), int(), [](int a, int b) {
        return std::move(a) + b;
        });

    auto finish = std::chrono::high_resolution_clock::now(); // ��������� ����� ����� ������ ���������
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\t ������ �������: " << sizeVector << ", ����� ���������: " << elapsed.count() << ", ���������: " << sum << '\n'; // ��������� ����������������� ������ � ���. � ������� �� �����
}

void ThreadTest::startTest()
{
    std::cout << "\n ����������� ������������ ������ ��������� � " << getNumThread() << " - ��������! \n";
    threadTest(_sizeVector); // ������� ������ ������ 16^6
    threadTest(_sizeVector / 16); // ������� ������ ������ 16^5
    threadTest(_sizeVector / (16 * 16)); // ��������� ������ ������ 16^4
}

void ThreadTest::startTestTest()
{
    std::cout << "\n ����������� ������������ ������ ��������� �: 1,2,4 - ��������! \n\t ������: ";
    for (int a : _arr) {
        std::cout << a << " ";
    }
    std::cout << '\n';

    _numThread = 1;
    threadTest(_sizeVector); 
    _numThread = 2;
    threadTest(_sizeVector);
    _numThread = 4;
    threadTest(_sizeVector);
}