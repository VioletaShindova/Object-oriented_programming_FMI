// Ex6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
6. Напишете функция filter, която приема масив arr от цели числа, за който е 
заделено точно количество памет, и указател към предикат (функция, която приема цяло 
число и връща булева стойност) pred. Нека функцията върне нов масив, за който е заделено точно 
количество памет, който съдържа само тези елементи на arr, за които pred е истина.
Пример:
Код:

bool pred(int a)
{
    return a % 2 == 0;
}

... filter(...)
{
    ...
}

int main()
{
    int* result = filter(..., pred);
}
Вход:

[1, 2, 3, 4, 5]

Ще подадем следната функция:
bool pred(int a)
{
    return a % 2 == 0;
}
Изход:

[2, 4]
*/

constexpr size_t ARR_SIZE = 5;
size_t countOfEvenNumbers = 0;

bool isEven(int number)
{
    int mask = 1;

    return !(mask & number);
}

void printNewArr(const int* arr)
{
    std::cout << "Modified array: ";
    for (size_t i = 0; i < countOfEvenNumbers; i++)
    {
        std::cout << arr[i] << " ";
    }
}

size_t findCountOfEvenNumbers(const int* arr, bool (*funcPtr)(int))
{
    size_t counter = 0;
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        if (funcPtr(arr[i]))
        {
            counter++;
        }
    }

    return counter;
}

int* filter(const int* arr, bool (*predPtr)(int))
{
    int* newArr = new int[countOfEvenNumbers + 1];
    int* temp = newArr;

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        if (predPtr(arr[i]))
        {
            *temp = arr[i];
            temp++;
        }
    }

    *temp = 0;

    return newArr;
}

int main()
{
    int arr[ARR_SIZE] = { 1,2,3,4,5 };

    countOfEvenNumbers = findCountOfEvenNumbers(arr, isEven);

    int* newArr = filter(arr, [](int a) { return (a % 2 == 0);});

    printNewArr(newArr);

    delete[] newArr;
}

