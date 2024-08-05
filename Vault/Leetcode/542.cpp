#include <bits/stdc++.h>
using namespace std;

#define sz(x) int((x).size())
using vi = vector<int>;
using pi = pair<int, int>;

class Solution {
public:
    bool isValid(int i, int j, int m, int n) {
        return 0 <= i && i < m && 0 <= j && j < n; 
    } 

    vector<vector<int>> bfs(vector<vector<int>>& mat, queue<pi> &q, int m, int n) {
        const int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1};
        int level = 1;
        vector<vector<int>> res_mat(m, vector<int>(n, 0));
        while (!q.empty()) {
            pi u = q.front();
            q.pop();
            if (u.first == -1 && u.second == -1) {
                cout << endl << endl;
                if (!q.empty()) {
                    q.push({-1, -1});
                    level++;
                    u = q.front();
                    q.pop();
                } else {
                    break;
                }
            }
            for (int i = 0; i < 4; i++) {
                int new_i = u.first + dx[i];
                int new_j = u.second + dy[i];
                if (isValid(new_i, new_j, m, n) && mat[new_i][new_j] == 1) {
                    mat[new_i][new_j] = 0;
                    res_mat[new_i][new_j] = level;
                    q.push({new_i, new_j});
                }
            }
        }
        return res_mat;
    }

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = sz(mat);
        int n = sz(mat[0]);

        queue<pi> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        q.push({-1, -1});
        return bfs(mat, q, m, n);
    }
};