#pragma once

class CoordinationSystem {
public:
    struct Pair {
    public:
        Pair() = default;
        Pair(int x, int y) : x(x), y(y){}
        Pair(double x, double y) : x(x), y(y){}

        double getX() const;

        double getY() const;

        void print() const;

    private:
        double x = 0;
        double y = 0;
    };

    CoordinationSystem() = default;

    explicit CoordinationSystem(int size);

    CoordinationSystem(const Pair* pairs, int size);

    CoordinationSystem(const CoordinationSystem& other);

    CoordinationSystem& operator=(const CoordinationSystem& other);

    ~CoordinationSystem();

    int setSize(size_t size);

    size_t getSize() const;

    Pair getCenterOfGravity() const;

    Pair* getTheThreeClosestPointsToTheCenter();

    bool writeToBinaryFile(const char* fileName) const;

    bool readFromBinaryFile(const char* fileName);

    void print() const;

    void printFirstThreePoints() const;

private:
    int isValid(int size) const;

    double getLength(const Pair& firstPoint, const Pair& secondPoint) const;

    bool isShorterLengthToCenter(double fistLength, double secondLength) const;

    double getSumOfCoodrinatesX(size_t size) const;
    
    double getSumOfCoodrinatesY(size_t size) const;

    void copyDynamic(const CoordinationSystem& other);

    void freeDynamic();

    Pair* pairs = nullptr;
    size_t size = 0;
};
