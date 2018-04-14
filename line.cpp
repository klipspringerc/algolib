// O(1) algorithm tot determine line intersection
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// Created by KevinCui on 20/3/18.
//

#include <iostream>
#include <cstdlib>
#include "line.h"
using namespace std;

// Find the orientation of two vectors made up of three points.
// 0 - colinear
// 1 - clockwise
// 2 - counterclockwise
int orientation(Point p1, Point p2, Point p3) {
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p2.x - p1.x);
    if (val == 0)
        return 0;
    return (val > 0)? 1 : -1;
}

bool on_segment_if_colinear(Point p1, Point p2, Point q) {
    return p1.x <= q.x && p2.x >= q.x || p1.x >= q.x && p2.x <= q.x;
}

bool do_intersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && on_segment_if_colinear(p1, q1, p2))
        return true;
    if (o2 == 0 && on_segment_if_colinear(p1, q1, q2))
        return true;
    if (o3 == 0 && on_segment_if_colinear(p2, q2, p1))
        return true;
    return o4 == 0 && on_segment_if_colinear(p2, q2, q1);
}
