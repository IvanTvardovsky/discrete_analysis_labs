#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Graph {
    vector<vector<int>> list;
    vector<bool> visited;
    vector<int> color;
};

void dfs(int n, vector<vector<int>>& graph, vector<bool>& visit, vector<int>& component) {
    visit[n] = true;
    component.push_back(n);
    for (int elem : graph[n]) {
        if (!visit[elem] && elem != 0) {
            dfs(elem, graph, visit, component);
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph graph;
    vector<int> component;
    
    graph.visited = vector<bool>(n + 1, false);
    graph.list = vector<vector<int>>(n + 1, vector<int>());

    vector<vector<int>> matrix;
    
    int a, b;
    for (auto i = 0; i < m; ++i) {
        cin >> a >> b;
        graph.list[a].push_back(b);
        graph.list[b].push_back(a);
    }
    vector<vector<int>> answer;
    for (auto i = 1; i < graph.visited.size(); ++i) {
        if (!graph.visited[i]) {
            dfs(i, graph.list, graph.visited, component);
            answer.push_back(component);
            component.clear();
        }
    }
    for (int i = 0; i < answer.size(); ++i) {
        sort(answer[i].begin(), answer[i].end());
        for (auto j : answer[i]) {
            cout << j << " ";
        }
        cout << "\n";
    }
}
