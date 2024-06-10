#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())
using vi = vector<int>;
using pi = pair<int, int>;

class Solution {
    const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1};
public:
    bool isValid(int i, int j, int m, int n) {
        return 0 <= i && i < m && 0 <= j && j < n; 
    } 

    int bfs(queue<pi>& q1, vector<vector<int>>& grid, int m, int n) {
        int time = 0;
        queue<pi> q2;
        queue<pi>* active = &q1;
        queue<pi>* sup = &q2;
        while (true) {
            if ((*active).empty()) {
                if ((*sup).empty()) {
                    break;
                }
                queue<pi>* tmp = active;
                active = sup;
                sup = tmp;
                time++;
            }
            pi u = (*active).front();
            (*active).pop();
            for (int i = 0; i < 4; i++) {
                int new_i = u.first + dx[i];
                int new_j = u.second + dy[i];
                if (isValid(new_i, new_j, m, n) && grid[new_i][new_j] == 1) {
                    grid[new_i][new_j] = 2;
                    (*sup).push({new_i, new_j});
                }
            }
        }

        return time;
    }

    int orangesRotting(vector<vector<int>>& grid) {
        int m = sz(grid);
        int n = sz(grid[0]);
        int res = 0;

        queue<pi> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }

        res = bfs(q, grid, m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }

        return res;
    }
};
