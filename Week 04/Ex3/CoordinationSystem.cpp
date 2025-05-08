#include "CoordinationSystem.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define MIN(a, b) (a < b) ? a : b

size_t getFileSize(std::ifstream& ifs) {
    int currPosition = ifs.tellg();

    ifs.seekg(0, std::ios::end);

    int result = ifs.tellg();

    ifs.seekg(currPosition, std::ios::beg);

    return result;
}

double CoordinationSystem::Pair::getX() const
{
    return x;
}

double CoordinationSystem::Pair::getY() const
{
    return y;
}

void CoordinationSystem::Pair::print() const
{
    std::cout << "X: " << this->x << " Y: " << this->y << std::endl;
}

CoordinationSystem::CoordinationSystem(int size) {
    if (setSize(size) <= 0)
        throw "Invalid size!";
    else
        this->pairs = new Pair[size]{};
}

CoordinationSystem::CoordinationSystem(const Pair* pairs, int size) {
    if (setSize(size) <= 0)
        throw "Invalid size!";

    this->pairs = new (std::nothrow) Pair[size];

    if (!this->pairs)
        throw "Invalid pointer address!";

    for (size_t i = 0; i < size; i++) {
        this->pairs[i] = pairs[i];
    }
}

CoordinationSystem::CoordinationSystem(const CoordinationSystem& other) : size(other.size) {
    copyDynamic(other);
}

CoordinationSystem& CoordinationSystem::operator=(const CoordinationSystem& other) {
    if (this != &other) {
        freeDynamic();
        copyDynamic(other);

        size = other.size;
    }
    return *this;
}

CoordinationSystem::~CoordinationSystem() {
    freeDynamic();
}

int CoordinationSystem::setSize(size_t size) {
    if (isValid(size) < 0)
        return -1;

    if (size == 0)
        return 0;

    this->size = size;
    return 1;
}

size_t CoordinationSystem::getSize() const {
    return this->size;
}

CoordinationSystem::Pair CoordinationSystem::getCenterOfGravity() const {
    return { getSumOfCoodrinatesX(size) / size, getSumOfCoodrinatesY(size) / size };
}

CoordinationSystem::Pair* CoordinationSystem::getTheThreeClosestPointsToTheCenter() {
    Pair centerOfGravity = getCenterOfGravity();

    Pair* result = new Pair[3];

    for (size_t i = 0; i < this->size - 1; i++) {
        if (i == 3)
            break;

        size_t minIndex = i;

        for (size_t j = i + 1; j < this->size; j++) {
            if (!isShorterLengthToCenter(getLength(this->pairs[minIndex], centerOfGravity), getLength(this->pairs[j], centerOfGravity)))
                minIndex = j;
        }

        if (minIndex != i)
            std::swap(this->pairs[minIndex], this->pairs[i]);

        result[i] = this->pairs[i];
    }

    return result;
}

bool CoordinationSystem::writeToBinaryFile(const char* fileName) const {
    if (!fileName)
        return false;

    std::ofstream ofs(fileName, std::ios::binary);

    if (!ofs.is_open())
        return false;

    ofs.write((const char*)pairs, sizeof(Pair) * size);

    ofs.close();

    return true;
}

bool CoordinationSystem::readFromBinaryFile(const char* fileName) {
    if (!fileName)
        return false;

    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open())
        return false;

    ifs.read((char*)pairs, MIN(getFileSize(ifs), (size_t)(sizeof(Pair) * size)));

    ifs.close();

    return true;
}

void CoordinationSystem::print() const
{
    for (size_t i = 0; i < this->size; i++)
    {
        std::cout << this->pairs[i].getX() << ' ' << this->pairs[i].getY() << ' ';
    }
}

void CoordinationSystem::printFirstThreePoints() const
{
    std::cout << std::endl;

    for (size_t i = 0; i < 3; i++)
    {
        pairs[i].print();
    }
}

int CoordinationSystem::isValid(int size) const {
    return size;
}

double CoordinationSystem::getLength(const Pair& firstPoint, const Pair& secondPoint) const {
    return sqrt(((firstPoint.getX() - secondPoint.getX()) * (firstPoint.getX() - secondPoint.getX())) +
        ((firstPoint.getY() - secondPoint.getY()) * (firstPoint.getY() - secondPoint.getY())));
}

bool CoordinationSystem::isShorterLengthToCenter(double fistLength, double secondLength) const {
    return fistLength < secondLength;
    //return (0 < abs(fistLength - secondLength)) && (abs(fistLength - secondLength) < 1);
}

double CoordinationSystem::getSumOfCoodrinatesX(size_t size) const {
    if (size == 0)
        return 0;

    return pairs[size - 1].getX() + getSumOfCoodrinatesX(size - 1);
}

double CoordinationSystem::getSumOfCoodrinatesY(size_t size) const {
    if (size == 0)
        return 0;

    return pairs[size - 1].getY() + getSumOfCoodrinatesY(size - 1);
}

void CoordinationSystem::copyDynamic(const CoordinationSystem& other) {
    pairs = new (std::nothrow) Pair[other.size];
    if (!other.pairs)
        throw std::bad_alloc();

    for (size_t i = 0; i < other.size; i++) {
        pairs[i] = other.pairs[i];
    }
}

void CoordinationSystem::freeDynamic() {
    delete[] pairs;
}