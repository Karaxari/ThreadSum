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
    _arr.reserve(_sizeVector); // Резервируем размерность вектора

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    for (int i = 0; i < _sizeVector; ++i) {
        _arr.push_back(dist(gen));
    }
}

void ThreadTest::threadTest(int sizeVector)
{
    auto start = std::chrono::high_resolution_clock::now(); // сохраняем время начала работы алгоритма

    std::vector<int> arr;
    arr.reserve(_arr.size());
    std::copy(_arr.begin(), std::begin(_arr) + sizeVector, std::back_inserter(arr));

    std::vector<std::thread> threads;
    std::vector<int> arrSum = {};
    int dif = sizeVector / _numThread; // _numThread - должно быть кратно sizeVector, иначе будет пропуск элементов вектора!

    for (int i = 0; i < _numThread; i++)
    {
        int start = i * dif;
        int end = start + dif;

        // Хотел сделать крассиво, но получилось как всегда ), да здраствует состояние гонки при увеличении числа потоков работающих с arrSum
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

    auto finish = std::chrono::high_resolution_clock::now(); // сохраняем время конца работы алгоритма
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\t Размер массива: " << sizeVector << ", Время обработки: " << elapsed.count() << ", Результат: " << sum << '\n'; // вычисляем продолжительность работы в сек. и выводим на экран
}

void ThreadTest::startTest()
{
    std::cout << "\n Запускается тестирование работы алгоритма с " << getNumThread() << " - потоками! \n";
    threadTest(_sizeVector); // Большой массив данных 16^6
    threadTest(_sizeVector / 16); // Средний массив данных 16^5
    threadTest(_sizeVector / (16 * 16)); // Маленький массив данных 16^4
}

void ThreadTest::startTestTest()
{
    std::cout << "\n Запускается тестирование работы алгоритма с: 1,2,4 - потоками! \n\t Массив: ";
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