#pragma once

struct Point {
	int x = 0;
	int y = 0;
};

void readInputOfCoordinates(Point& p);

void printOutput(const Point& p);

double getLengthBetweenTwoPoints(const Point& p1, const Point& p2);