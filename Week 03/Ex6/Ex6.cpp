// Ex6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Relation.h"
#include "Pair.h"
#include <iostream>
/*
Създайте структура Pair, която представя наредена двойка от естествени числа. 
Създайте структура, която представя релация. В релацията има най-много 25 наредени двойки 
и структурата пази текущия си размер.

Напишете функция, която прочита релация от даден файл.
Напишете функция, която добавя наредена двойка към релацията.
Напишете функция, която записва релацията в даден файл.
*/

int main()
{
    Relation rel1(Relation(3));

    if (!rel1.readRelationFromFile("ex6_RelPairs.txt"))
        return 0;

    rel1.printRelations();

    std::cout << std::endl;

    Pair pr1(2, 3);
    Pair pr2(34, 56);
    Pair* pair = new Pair[2]{pr1, pr2};
    Relation rel2(pair, 2);
    if (!rel2.writeRelationToFile("ex6_NewRelPairs.txt"))
        return 0;

    Pair pr3(6, 6);

    if(rel2.addPairToRelation(pr3))
        rel2.printRelations();
}

