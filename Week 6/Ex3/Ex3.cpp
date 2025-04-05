#include <iostream>
#include "Game.h"
#include "GamePlatform.h"

using std::cin;
using std::cout;
using std::endl;

/*
Имплементирайте клас Game, който съдържа следните член-данни (полета): title, price, isAvailable. 
Член-данната title е от тип символен низ с максимална дължина 64.

Бележка. В реалните софтуерни продукти не се използват floating-point числа, за да се моделират пари и други данни, 
изискващи прецизност. Тук го моделираме по този начин за целите на упражнението.

Нека Game да съдържа:

Селектори (getter);
Мутатори (setter);
isFree() - връща информация дали играта е безплатна;
print() - отпечатва информация за играта в подходящ формат.
Напишете клас GamePlatform (платформа за игри), който съдържа най-много 64 игри (Games).

За да работим с GamePlatform, се нуждаем от следните функции:

Добавяне на игра, ако има място.
Извеждане на игра по индекс.
Извеждане на списък с всички игри в платформата.
Извеждане на най-евтината / скъпата игра в платформата.
Извеждане на всички безплатни игри.
Премахване на игра от библиотеката.
Възможност за запазване на данните от платформата в текстов и в двоичен файл.
Възможност за изчитане на данните от текстов и от двоичен файл и запазване в платформата за игри.
*/

int main()
{
    Game game1;
	try
	{
		game1 = Game("League of Legends");
	}
	catch (const std::invalid_argument& in_arg)
	{
		cout << in_arg.what();
	}

	Game game2("League of Legends", 20, 1);
	game1.setTitle("Fortnite");
	game1.setPrice(40);

	Game game3("World of tanks", 100, 0);

	Game games[3] {game1, game2, game3};

	GamePlatform platform1(games, 3);

	//(void)platform1.writeToBinaryFile("ex3_binaryFile.dat");
	(void)platform1.writeToBinaryFile("ex3_binaryFile.txt");
	GamePlatform platform2;

	//(void)platform2.readFromBinaryFile("ex3_binaryFile.dat");
	(void)platform2.readFromBinaryFile("ex3_binaryFile.txt");
	platform2.printGames();
	platform2.printParticularGame(1);
	
	Game game4("Granny", 0, 1);
	if (!platform2.addGame(game4))
		cout << "Not possible to add";

	cout << endl;
	platform2.printGames();

	cout << endl;
	platform2.printAllFreeGames();

	if (!platform2.removeGame(game4))
		cout << "Not possible to remove";

	cout << endl;
	platform2.printGames();

}
