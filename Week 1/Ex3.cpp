// Ex3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
/*
3. Напишете функция, която приема число K и два масива с произволен размер и връща нов масив с точна големина, 
съдържащ всички числа от двата масива, които се делят на K.
Пример:
Вход:

3
[2, 8, 3, 15, 27]
[5, 9, 4]
Изход:

[3, 15, 27, 9]
*/
unsigned sifeOfNewArr = 0;

bool dividesToK(int K, int number)
{
    return (number % K == 0);
}

unsigned findCountOfNumbersThatDivideToK(int K, const int* firstArr, size_t size1, const int* secondArr, size_t size2)
{
    unsigned counter = 0;

    for (size_t i = 0; i < size1; i++)
    {
        if (dividesToK(K, firstArr[i]))
        {
            counter++;
        }
    }

    for (size_t i = 0; i < size2; i++)
    {
        if (dividesToK(K, secondArr[i]))
        {
            counter++;
        }
    }

    return counter;  
}

int* findKDividers(int K, const int* firstArr, size_t size1, const int* secondArr, size_t size2)
{
    if (!size1 || !size2)
    {
        return nullptr;
    }

    unsigned digitsThatDivideK = findCountOfNumbersThatDivideToK(K, firstArr, size1, secondArr, size2);
    sifeOfNewArr = digitsThatDivideK + 1;
    int* newArr = new int[digitsThatDivideK + 1];
    int* temp = newArr;

    for (size_t i = 0; i < size1; i++)
    {
        if (dividesToK(K, firstArr[i]))
        {
            *temp = firstArr[i];
            temp++;
        }
    }

    for (size_t i = 0; i < size2; i++)
    {
        if (dividesToK(K, secondArr[i]))
        {
            *temp = secondArr[i];
            temp++;
        }
    }
    *temp = 0;
    return newArr;
}

void printNewArr(const int* newArr)
{
    if (!sifeOfNewArr)
    {
        return;
    }

    std::cout << '[';
    for (size_t i = 0; i < sifeOfNewArr - 1; i++)
    {
        if (i + 2 == sifeOfNewArr)
        {
            std::cout << newArr[i];
            break;
        }
        std::cout << newArr[i] << ", ";
    }
    std::cout << ']';

    return;
}

int main()
{
    int K;
    std::cin >> K;

    int arr1[5] = { 2, 8, 3, 15, 27 };
    int arr2[3] = { 5, 9, 4 };
    int* newArr = findKDividers(K, arr1, 5, arr2, 3);
    printNewArr(newArr);
    delete[] newArr;
}
