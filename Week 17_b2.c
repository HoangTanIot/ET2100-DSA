/Cài đặt cấu trúc đồ thị cho trên bảng và thực hiện các hàm sau 
/Nhập các đỉnh và liên kết của đồ thị G(V,E) 
/Duyệt đồ thị theo 2 cách BFS, DFS và in thứ tự các đỉnh duyệt 

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Định nghĩa đồ thị
class Graph {
    int V; // Số lượng đỉnh
    vector<vector<int>> adj; // Danh sách kề

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Hàm thêm cạnh vào đồ thị
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Nếu đồ thị vô hướng
    }

    // Hàm duyệt BFS
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Hàm duyệt DFS
    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        cout << "DFS: ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
            }

            for (auto it = adj[current].rbegin(); it != adj[current].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Nhập số đỉnh: ";
    cin >> V;
    cout << "Nhập số cạnh: ";
    cin >> E;

    Graph g(V);

    cout << "Nhập các cạnh (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Nhập đỉnh bắt đầu: ";
    cin >> start;

    g.BFS(start);
    g.DFS(start);

    return 0;
}
