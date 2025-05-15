#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node(string s, long long d, int p) 
   {
    this->room_name=s;
    this->dist=d;
    this->parity=p;
   } 
    
    string getRoomName() const { return room_name; } //getter functions for private attributes
    long long getDist() const { return dist; }
    int getParity() const { return parity; }
    
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }

    bool operator<(const Node& other) const {
        return dist < other.dist;
    }

    bool operator>=(const Node& other) const {
        return dist >= other.dist;
    }

    bool operator<=(const Node& other) const {
        return dist <= other.dist;
    }
    
private:
    string room_name;
    long long dist;
    int parity; // 0 for even, 1 for odd
};

template <typename T>
class custom_min_heap {
public:
    vector<T> heap;

    void push(const T & value) {
        heap.push_back(value);
        percolate_up(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        percolate_down(0);
    }

    const T& top() {
        return heap.front();
    }

    const bool empty() {
        return heap.empty();
    }

    const size_t size()
    {
        return heap.size();
    }

private:
    void percolate_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] <= heap[index]) break;
            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void percolate_down(int index) {
        int size = heap.size();
        while (true) {
            int child1 = 2 * index + 1;
            int child2 = 2 * index + 2;
            int smallest = index;

            if (child1 < size && heap[child1] < heap[smallest])
                smallest = child1;
            if (child2 < size && heap[child2] < heap[smallest])
                smallest = child2;

            if (smallest == index) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }
};

//global adjlist and room mapping
vector<vector<pair<string, long long>>> adjlist;
map<string, int> room_index;

void dij(string source, string sink) {
    custom_min_heap<Node> pq;
    map<string, array<long long, 2>> dist; 

    for (auto &it : room_index) {
        dist[it.first] = {LLONG_MAX, LLONG_MAX};
    }

    dist[source][0] = 0;
    pq.push(Node(source, 0, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        string u = current.getRoomName();
        int u_parity = current.getParity();

        if (u == sink && u_parity == 0) {
            cout << dist[u][0] << endl;
            return;
        }

        int u_index = room_index[u];

        for (size_t i = 0; i < adjlist[u_index].size(); i++) {
            string v = adjlist[u_index][i].first;
            long long weight = adjlist[u_index][i].second;
            int new_parity = 1 - u_parity;

            if (dist[u][u_parity] + weight < dist[v][new_parity]) {
                dist[v][new_parity] = dist[u][u_parity] + weight;
                pq.push(Node(v, dist[v][new_parity], new_parity));
            }
        }
    }

    cout << -1 << endl; // No valid path with even edges
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> rooms(n);
    adjlist.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> rooms[i];
        room_index[rooms[i]] = i;
    }

    for (int i = 0; i < m; i++) {
        string a, b;
        int w;
        cin >> a >> b >> w;
        int n1 = room_index[a];
        int n2 = room_index[b];
        adjlist[n1].push_back({b, w});
        adjlist[n2].push_back({a, w});
    }

    string source, sink;
    cin >> source >> sink;
    dij(source, sink);
}
