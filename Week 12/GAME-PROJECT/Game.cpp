#include "Game.h"
#include "Artifact.h"
#include "Teleport.h"
#include "Present.h"
#include "CombinationSubject.h"
#include "Monster.h"
#include "Player.h"
#include "LivingThings.h"

unsigned Game::currentIndexOfLineOfArtifact = 0;

Game::WrapperArtifacts::WrapperArtifacts()
	: artifacts(nullptr), sizeOfArtifacts(0)
{
	setArtifacts();
}

Game::WrapperArtifacts::WrapperArtifacts(const WrapperArtifacts& other) : sizeOfArtifacts(other.sizeOfArtifacts)
{
	copyDynamic(other);
}

Game::WrapperArtifacts& Game::WrapperArtifacts::operator=(const WrapperArtifacts& other)
{
	if (this != &other)
	{
		sizeOfArtifacts = other.sizeOfArtifacts;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Game::WrapperArtifacts::~WrapperArtifacts() noexcept
{
	freeDynamic();
}

void Game::WrapperArtifacts::setArtifact(int position, const Artifact& artifact)
{
	if (position < GlobalConstants::MIN_BORDER || GlobalConstants::MAX_BORDER < position)
		throw std::invalid_argument("Invalid position\n");

	while (artifacts[position])
	{
		position = rand() % GlobalConstants::MAX_BORDER;
	}

	artifacts[position] = artifact.clone();
}

void Game::WrapperArtifacts::setArtifacts()
{
	Artifact** temp = new (std::nothrow) Artifact * [GlobalConstants::MAX_BORDER] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < sizeOfArtifacts; i++)
		delete artifacts[i];
	delete[] artifacts;

	artifacts = temp;
	sizeOfArtifacts = GlobalConstants::MAX_BORDER;
}	

void Game::WrapperArtifacts::freeDynamic()
{
	for (size_t i = 0; i < sizeOfArtifacts; i++)
		delete artifacts[i];
	delete[] artifacts;
	artifacts = nullptr;
}

void Game::WrapperArtifacts::copyDynamic(const WrapperArtifacts& other)
{
	Artifact** temp = new (std::nothrow) Artifact * [other.sizeOfArtifacts] {nullptr};

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.sizeOfArtifacts; i++)
		temp[i] = other.artifacts[i] ? other.artifacts[i]->clone() : nullptr;

	artifacts = temp;
}

Game::Game() : Game(1, 0) {}

Game::Game(int capacity) : Game(capacity, 0) {}

Game::Game(int capacity, int countOfArtifacts)
	: eachLineOfArtifact(nullptr), size(0), capacity(1)
{
	setCapacity(capacity);
	setArtifacts(countOfArtifacts);
}

Game::Game(const Game& other) : size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		size = other.size;
		capacity = other.capacity;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Game::~Game() noexcept
{
	freeDynamic();
}

void Game::run(Game& game)
{
	Player player;
	unsigned tempIndexOfLineArtifact = currentIndexOfLineOfArtifact;
	Artifact** artifactsOfEachLine = game.eachLineOfArtifact[currentIndexOfLineOfArtifact].getArtifacts();
	size_t tempIndexOfPlayer = player.getCurrentPosition();

	while (player.getBlood() && currentIndexOfLineOfArtifact < game.size)
	{
		if (Teleport* t = dynamic_cast<Teleport*>(artifactsOfEachLine[tempIndexOfPlayer]))
			t->interact(player);
		else 
		{
			try {
				game.rollDice(player);
			}
			catch (...) {
				return;
			}

			if (tempIndexOfLineArtifact != currentIndexOfLineOfArtifact)
			{
				artifactsOfEachLine = game.eachLineOfArtifact[currentIndexOfLineOfArtifact].getArtifacts();
				tempIndexOfLineArtifact = currentIndexOfLineOfArtifact;
			}
			
			game.interact(artifactsOfEachLine[tempIndexOfPlayer], player); //consciously don't catch the exception in order to call std::terminate()
		}
	}
}

void Game::interact(Artifact* artifact, Player& player)
{
	if (Teleport* t = dynamic_cast<Teleport*>(artifact))
		t->interact(player);
	else if (Present* p = dynamic_cast<Present*>(artifact))
		p->interact(player);
	else if (Monster* m = dynamic_cast<Monster*>(artifact))
		m->interact(player);
	else if (CombinationSubject* cs = dynamic_cast<CombinationSubject*>(artifact))
		cs->interact(player);
}

unsigned Game::incrementCurrentIndexOfLineOfArtifact()
{
	return ++currentIndexOfLineOfArtifact;
}

void Game::rollDice(Player& player)
{
	if (currentIndexOfLineOfArtifact >= size && player.getCurrentPosition() > GlobalConstants::MAX_BORDER)
		throw "You won!\n";

	int randomNumber = rand() % GlobalConstants::MAX_BORDER;

	if (player.getCurrentPosition() + randomNumber > GlobalConstants::MAX_BORDER)
	{
		player.setCurrentPosition(GlobalConstants::MAX_BORDER % (player.getCurrentPosition() + randomNumber));
		(void)incrementCurrentIndexOfLineOfArtifact();
	}
	else
		player.setCurrentPosition(player.getCurrentPosition() + randomNumber);
}

void Game::setCapacity(int capacity)
{
	if (capacity <= 0 || capacity < size)
		throw std::invalid_argument("Invalid capacity\n");

	WrapperArtifacts* temp = new (std::nothrow) WrapperArtifacts[capacity]; //calls out capacity-times def ctor of WrapperArtifacts

	if (!temp)
		throw std::bad_alloc();

	delete[] eachLineOfArtifact;
	eachLineOfArtifact = temp;
}

void Game::setArtifacts(int countOfArtifacts)
{
	if (countOfArtifacts < 0 && countOfArtifacts >= size)
		throw std::invalid_argument("Invalid count of atifacts\n");

	using std::cin;
	using std::cout;

	int indexingDifferentArtifacts = 0;

	while (countOfArtifacts)
	{
		switch ((TypeArtifact)indexingDifferentArtifacts)
		{
		case TypeArtifact::TELEPORT:
		{
			int number;
			cout << "Input number of cage: ";
			cin >> number;
			if (!cin)
				throw std::runtime_error("Invalid input\n");
			eachLineOfArtifact[rand() % capacity].setArtifact(rand() % GlobalConstants::MAX_BORDER, Teleport(number));
			indexingDifferentArtifacts++;
			break;
		}

		case TypeArtifact::PRESENT:
		{
			int type, value;
			cout << "Type a number between 1 and 4: ";
			cin >> type;

			cout << "Value of a present: ";
			cin >> value;
			eachLineOfArtifact[rand() % capacity].setArtifact(rand() % GlobalConstants::MAX_BORDER, Present(type, value));
			indexingDifferentArtifacts++;
			break;
		}

		case TypeArtifact::MONSTER:
		{
			char buffer[128];
			cout << "Name: ";
			cin.get();
			cin.getline(buffer, 128, '\n');

			int power, blood;
			cout << "Power: ";
			cin >> power;

			cout << "Blood: ";
			cin >> blood;
			eachLineOfArtifact[rand() % capacity].setArtifact(rand() % GlobalConstants::MAX_BORDER, Monster(buffer, power, blood));
			indexingDifferentArtifacts++;
			break;
		}

		case TypeArtifact::COMBINED_SUBJECTS:
		{
			int cageNumber, type, value;
			cout << "Cage number: ";
			cin >> cageNumber;

			cout << "Type: ";
			cin >> type;

			cout << "Value: ";
			cin >> value;

			eachLineOfArtifact[rand() % capacity].setArtifact(rand() % GlobalConstants::MAX_BORDER, CombinationSubject(cageNumber, type, value));
			indexingDifferentArtifacts++;
			break;
		}
		default:
			indexingDifferentArtifacts = 1;
			break;
		}
		countOfArtifacts--;
	}
}

bool Game::isPositionInBorders(int newPosition) const
{
	return (GlobalConstants::MIN_BORDER <= newPosition) && (newPosition <= GlobalConstants::MAX_BORDER);
}

void Game::freeDynamic()
{
	delete[] eachLineOfArtifact;
	eachLineOfArtifact = nullptr;
}

void Game::copyDynamic(const Game& other)
{
	WrapperArtifacts* temp = new (std::nothrow) WrapperArtifacts[other.capacity];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
		temp[i] = other.eachLineOfArtifact[i];

	eachLineOfArtifact = temp;
}

void Game::resize()
{
	size_t tempCapacity = capacity * 2 + 1;
	WrapperArtifacts* temp = new (std::nothrow) Game::WrapperArtifacts[tempCapacity];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
		temp[i] = eachLineOfArtifact[i];

	delete[] eachLineOfArtifact;
	eachLineOfArtifact = temp;
	capacity = tempCapacity;
}