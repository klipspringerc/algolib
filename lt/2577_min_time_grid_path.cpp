//
// https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/
// each step we must move to another grid
// each step, time + 1
// if no grid accessible, return -1;
// Use modified Dijkstra / BFS, with priority queue on all possible routes
// Note that we could move back and forth to accumulate t

#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        class Cell {
        public:
            int x;
            int y;
            int t;
            int st; // visit time
            Cell(int _x, int _y, int _t, int _st): x(_x), y(_y), t(_t), st(_st)  {}
        };
        class MaxCell {
        public:
            bool operator() (const Cell   ca, const Cell  cb) {
                return ca.st > cb.st;
            }
        };
        int m = grid.size();
        int n = grid[0].size();
        // as long as the first step is doable, then actor could always move
        // back and forth to accumulate more time.
        if (grid[1][0] > 1 && grid[0][1] > 1)
            return -1;
        priority_queue<Cell, vector<Cell>, MaxCell> pq; // min heap of cells
        Cell nc(0,0,grid[0][0], 0);
        vector<vector<bool>> visited(m, vector<bool>(n,false));
        vector<vector<int>> directions = {{0,1}, {1,0}, {-1,0}, {0,-1}};
        pq.push(nc);
        while (!pq.empty()) {
            Cell cur = pq.top();
            pq.pop();
            if (cur.x == m-1 && cur.y == n-1)
                return cur.st;
            int cur_step = cur.st + 1, x = cur.x, y = cur.y;
            if (visited[x][y])
                continue;
            visited[x][y] = true;
            // test four directions,
            for (const auto & dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                if (nx >= m || nx < 0 || ny >= n || ny < 0 || visited[nx][ny])
                    continue;
                // if distance is even, need extra step to circle back
                // since each jump back and forth would add 2 to cur t
                int extra_wait = ((grid[nx][ny] - cur.st) % 2) == 0;
                // no need to increment t one by one, directly jump to next t.
                int nt = max(cur_step, grid[nx][ny] + extra_wait);
                pq.push(Cell(nx, ny, grid[nx][ny], nt));
            }
        }
        return -1;
    }
};

int main() {
    vector<vector<int>> grid = {
            {0,1,3,2},{5,1,2,5},{4,3,8,6}
//            {0,1,9,9},{5,9,9,9},{4,3,8,6}
    };
    Solution s;
    printf("%d\n", s.minimumTime(grid));
}