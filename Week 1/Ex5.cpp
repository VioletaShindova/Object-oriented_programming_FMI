// Ex5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
5. Напишете функция map, която приема масив arr от цели числа, за който е заделено точно количество памет, 
и указател към функция func (приемаща и връщаща цяло число). Нека функцията map промени всеки елемент 
на arr с резултата от func за съответния елемент. Пример:
Код:

int f(int a)
{
    return a * 2;
}

... map(...)
{
    ...
}

int main()
{
    map(..., f);
    или
    map(..., [](int a) {
        return a * 2;
    });
}
Вход:

[1, 2, 3, 4, 5]

Ще подадем следната функция:
int f(int a)
{
    return a * 2;
}
Изход:

[2, 4, 6, 8, 10]
*/

constexpr size_t ARR_SIZE = 5;

int func1(int a)
{
    return 2 * a;
}

void map1(int* arr, int (*funcPtr)(int))
{
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = funcPtr(arr[i]);
    }
}

void printNewArr(const int* arr)
{
    std::cout << "Modified array: ";
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        std::cout << arr[i] << " ";
    }
}

int main()
{
    int arr[ARR_SIZE] = { 1,2,3,4,5 };

    map1(arr, func1);

    printNewArr(arr);

    map1(arr, [](int a)
        { return 0; });

    printNewArr(arr);
}

