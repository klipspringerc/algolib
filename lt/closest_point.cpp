//
// Find the closest pair of points
// Created by KevinCui on 23/3/18.
//

#include <cmath>
#include <vector>
#include <algorithm>
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

// find the first element larger than given x
int find_lower(vector<Point> & points, int l, int r, int x) {
    if (points[r].x <=x)
        return -1;
    int pl = l;
    int pr = r;
    while (pl < pr) {
        int mid = ((pr-pl) >> 1) + pl;
        if (points[mid].x <= x) {
            pl = mid+1;
        } else {
            pr = mid;
        }
    }
    return pl;
}

// find the last element smaller than given x
int find_upper(vector<Point> & points, int l, int r, int x) {
    if (points[l].x >= x)
        return -1;
    int pl = l;
    int pr = r;
    int ans = -1;
    while (pl <= pr) {
        int mid = ((pr-pl) >> 1) + pl;
        if (points[mid].x >= x) {
            pr = mid-1;
        } else {
            ans = mid;
            pl = mid+1;
        }
    }
    return ans;
}

// points on the left side and point on the right side, along with current min distance d.
double closest_in_strip(vector<Point> & pl, vector<Point> & pr, double d) {
    double min_d = d;
    for (Point & p : pl) {
        for (Point &q : pr) {
            if (q.y >= p.y + min_d || q.y <= p.y - min_d)
                continue;
            min_d = min(min_d, getd(p, q));
        }
    }
    return min_d;
}

double bruteforce(vector<Point> &points, int l , int r) {
    double min_dist = -1;
    for (int i=l; i<r; i++){
        for (int j=i+1; j <= r; j++) {
            double d = getd(points[i], points[j]);
            if (min_dist < 0 || d < min_dist) {
                min_dist = d;
            }
        }
    }
    return min_dist;
}

double closest_recur(vector<Point> & points, int l, int r) {
    if (r-l <= 2)
        return bruteforce(points, l, r);
    int mid = ((r-l) >> 1) + l;
    double min_l = closest_recur(points, l, mid);
    double min_r = closest_recur(points, mid, r);
    double min_d = min(min_l, min_r);
    Point pm = points[mid];
    vector<Point> strip_points_l;
    vector<Point> strip_points_r;
    int l_idx = find_lower(points, l, mid, pm.x-min_d);
    int r_idx = find_upper(points, mid, r, pm.x + min_d);
    if (l_idx != -1  && r_idx != -1) {
        for (int i = l_idx; i < mid; i++) {
                strip_points_l.push_back(points[i]);
        }
        for(int i = mid+1; i <= r_idx; i++) {
                strip_points_r.push_back(points[i]);
        }
    }
//    for (int i = l; i < mid; i++) {
//        if (points[i].x > pm.x - min_d) {
//            strip_points_l.push_back(points[i]);
//        }
//    }
//    for(int i = mid+1; i <= r; i++) {
//        if (points[i].x < pm.x + min_d) {
//            strip_points_r.push_back(points[i]);
//        }
//    }
    if (strip_points_r.size() && strip_points_r.size()) {
        double min_strip = closest_in_strip(strip_points_l, strip_points_r, min_d);
        min_d = min(min_strip, min_d);
    }

    return min_d;
}

double closest_points(vector<Point> & points) {
    sort(points.begin(), points.end(), compareX);
    return closest_recur(points, 0, points.size()-1);
}



int main() {
    vector<Point> in = {
            {1,3},{2,5},{6,9}, {7,3}
    };
    printf("resulta: %f\n", closest_points(in));

    printf("pos last smaller: %d\n", find_upper(in, 0, 3, 8));
    printf("pos first larger: %d\n", find_lower(in, 0, 3, 0));
};