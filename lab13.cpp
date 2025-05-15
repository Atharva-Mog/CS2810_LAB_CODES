#include <bits/stdc++.h>
using namespace std;

template <class T>
class Kingdom;  // Forward declaration so that i can use counthigherranked in the Sentinel class

class Sentinel {
public:
    Sentinel() {}
    Sentinel(string a, int b, int c) : name(a), id(b), rank(c) {}

    virtual long long counthigherranked(Kingdom<Sentinel*>& k) = 0;  //purely virtual function 

    string getname() { return name; }
    int getid() { return id; }
    int getrank() { return rank; }

    void printsentinel() {
        cout << this->id;
    }

protected:
    string name;
    int id;
    int rank;
};

class Senapati : public Sentinel { //senapati class
public:
    Senapati() {}
    Senapati(string a, int b, int c = 0) : Sentinel(a, b, 0) {}
    long long counthigherranked(Kingdom<Sentinel*>& k) override;
};

class Dandanayaka : public Sentinel { //dandanayaka class
public:
    Dandanayaka() {}
    Dandanayaka(string a, int b, int c = 1) : Sentinel(a, b, 1) {}
    long long counthigherranked(Kingdom<Sentinel*>& k) override;
};

class Chaturangini : public Sentinel { //chaturangini class
public:
    Chaturangini() {}
    Chaturangini(string a, int b, int c = 2) : Sentinel(a, b, 2) {}
    long long counthigherranked(Kingdom<Sentinel*>& k) override;
};

bool comparator(Sentinel*& a, Sentinel*& b) { //comparator function
    if (a->getrank() == b->getrank())
        return a->getid() < b->getid();
    return a->getrank() < b->getrank();
}

template <class T>
class Kingdom {
public:
    Kingdom() {
        numberofSenapatis = 0;
        numberofDandanayakas = 0;
        numberofChaturangini = 0;
    }

    void addedge(int u, int v) {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    void insertelements() {
        listofsentinels.resize(n);
        for (int i = 0; i < n; i++) {
            string a, b;
            cin >> a >> b;
            if (b == "SENAPATI") {
                Senapati* s = new Senapati(a, i);
                listofsentinels[i] = s;
                numberofSenapatis++;
            } else if (b == "DANDANAYAKA") {
                Dandanayaka* s = new Dandanayaka(a, i);
                listofsentinels[i] = s;
                numberofDandanayakas++;
            } else if (b == "CHATURANGINI") {
                Chaturangini* s = new Chaturangini(a, i);
                listofsentinels[i] = s;
                numberofChaturangini++;
            }
        }
    }

    void dfs(int node, int parent, const vector<vector<int>>& adj, vector<vector<int>>& directedAdj) {
        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                directedAdj[node].push_back(neighbor);
                dfs(neighbor, node, adj, directedAdj);
            }
        }
    }

    vector<vector<int>> getDirectedTree(const vector<vector<int>>& adj, int root = 0) {
        int n = adj.size();
        vector<vector<int>> directedAdj(n);
        dfs(root, -1, adj, directedAdj);
        return directedAdj;
    }

    void treeDP(int node, const vector<vector<int>>& tree) {
        dp[node][0] = 0;
        dp[node][1] = 1;
        for (int child : tree[node]) {
            treeDP(child, tree);
            dp[node][0] += dp[child][1];
            dp[node][1] += min(dp[child][0], dp[child][1]);
        }
    }

    vector<Sentinel*> listofsentinels_sort() {
        vector<Sentinel*> Copy = listofsentinels;
        sort(Copy.begin(), Copy.end(), comparator);
        return Copy;
    }

    vector<Sentinel*> listofsentinels;
    vector<vector<int>> adjlist;
    int numberofSenapatis;
    int numberofDandanayakas;
    int numberofChaturangini;
    vector<vector<int>> directedadjlist;
    vector<vector<int>> dp;
    int n;
};



long long Senapati::counthigherranked(Kingdom<Sentinel*>& k) {
    return 0;
}

long long Dandanayaka::counthigherranked(Kingdom<Sentinel*>& k) {
    return k.numberofSenapatis;
}

long long Chaturangini::counthigherranked(Kingdom<Sentinel*>& k) {
    return k.numberofSenapatis + k.numberofDandanayakas;
}



int main() {  //int main function
    Kingdom<Sentinel*> k;
    cin >> k.n;
    k.adjlist.resize(k.n);

    for (int i = 0; i < k.n - 1; i++) {
        int x, y;
        cin >> x >> y;
        k.addedge(x, y);
    }

    k.insertelements();
    k.directedadjlist = k.getDirectedTree(k.adjlist, 0);
    k.dp.assign(k.n, vector<int>(2, 0));
    k.treeDP(0, k.directedadjlist);

    vector<Sentinel*> Copy = k.listofsentinels_sort();

    int q;
    cin >> q;
    while (q--) {
        int p;
        cin >> p;
        if (p == 1) {
            cout << min(k.dp[0][0], k.dp[0][1]) << "\n";
        } else if (p == 2) {
            for (int i = 0; i < k.n; i++) {
                cout << Copy[i]->getid() << ' ';
            }
            cout << "\n";
        } else if (p == 3) {
            int num;
            cin >> num;
            cout << k.listofsentinels[num]->counthigherranked(k) << "\n";
        }
    }

    return 0;
}
