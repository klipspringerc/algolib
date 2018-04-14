//
// Find the closest pair of points
// Created by KevinCui on 23/3/18.
//

#include <cmath>
using namespace std;

struct Point{
    int x, y;
};

bool compareX(Point pA, Point pB) {
    return pA.x < pB.x;
}

bool compareY(Point pA, Point pB) {
    return pA.y < pB.y;
}

double getd(Point pA, Point pB) {
    return sqrt((pA.x - pB.x)*(pA.x - pB.x) + (pA.y - pB.y)*(pA.y - pB.y));
}



