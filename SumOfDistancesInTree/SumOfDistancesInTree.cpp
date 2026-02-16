#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> subtree(n, 1), ans(n), parent(n, -1);
        vector<int> order;

        queue<int> q;
        q.push(0);
        parent[0] = -2;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int v : g[u]) {
                if (parent[v] == -1) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        reverse(order.begin(), order.end());
        for (int u : order) {
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                subtree[u] += subtree[v];
                ans[0] += subtree[v];
            }
        }

        reverse(order.begin(), order.end());
        for (int u : order) {
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                ans[v] = ans[u] - subtree[v] + (n - subtree[v]);
            }
        }

        return ans;
    }
};