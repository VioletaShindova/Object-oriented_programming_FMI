// Ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
2. Напишете функция, която приема символен низ и връща броя на думите в него. 
(Думите са разделени с произволен брой интервали, табулации и препинателни знаци)
Пример:
Вход:

  Good  morning,     Vietnam!
Изход:

3
*/

bool isLetter(char letter)
{
    return (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z');
}

unsigned countWords(const char* text)
{
    if (!text)
    {
        return 0;
    }

    unsigned countWords = 0;
    
    while (*text)
    {
        if (isLetter(*text) && !isLetter(*(text + 1)))
        {
            countWords++;
        }
        text++;
    }

    return countWords;
}

int main()
{
    char text[] = "    Good,    morning, Leti is in     Vietnam";
    std::cout << countWords(text);
}

