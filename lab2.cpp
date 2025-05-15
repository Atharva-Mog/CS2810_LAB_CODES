#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    Graph() { ; }


    const vector <vector <int>> showadjm() const
    {
        return this->adjmatrix;
    }
    Graph &operator+(Graph g2) // denotes the union of graphs
    {
        int num1 = this->n;
        int num2 = g2.n;
        int num3 = max(num1, num2);
        int newsides=0;
        vector<vector<int>> newmatrix(num3, vector<int>(num3, 0));

        for (int i = 0; i < num3; i++)
        {
            for (int j = 0; j < num3; j++)
            {
                if ((i < num1 && j < num1 && this->adjmatrix[i][j] == 1) || (i < num2 && j < num2 && g2.adjmatrix[i][j] == 1))
                { newmatrix[i][j] = 1; newsides++;}
            // newmatrix[j][i] = 1;
            }
        }
        this->n = num3;
        this->adjmatrix.resize(num3, vector<int>(num3, 0));
        this->adjmatrix = newmatrix;
        this->m=newsides;
        return *this;
    }

Graph &operator -(Graph g2)
{
    int num1=this->n;
    int num2=g2.n;
    int num3=max(num1,num2);
    int newsides=0;
    vector < vector <int> > newmat(num3, vector <int> (num3,0));

    for(int i=0;i<num3;i++)
    {
        for(int j=0;j<num3;j++)
        {
                if ((i < num1 && j < num1 && this->adjmatrix[i][j] == 1) && (i < num2 && j < num2 && g2.adjmatrix[i][j] == 1))
                {newmat[i][j] = 1;newsides++;}
        }
    }

    this->n=num3;
    this->adjmatrix.resize(num3, vector <int> (num3,0));
    this->adjmatrix=newmat;
    this->m=newsides;
    return *this;
}
    Graph &operator!() // complement of a graph
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(i!=j)
                {
                adjmatrix[i][j] = 1 - adjmatrix[i][j];
                }
            }
        }
        return *this;
    }

    bool dfs(int u, int v, vector<vector<int>> &adj, vector<bool> &visited)
    {
        if (u == v)
            return true;
        visited[u] = true;

        for (int i = 0; i < int(adj.size()); i++)
        {
            if (adj[u][i] && !visited[i])
            {
                if (dfs(i, v, adj, visited))
                    return true;
            }
        }
        return false;
    }
    bool isreachable(int u, int v, vector<vector<int>> &adjm)

    {
        vector<bool> visited(adjm.size(), false);
        return dfs(u, v, adjm, visited);
    } 
    void addedge(int v1, int v2) // add edge and remove edge functions
    {
        adjmatrix[v1][v2] = 1;
        adjmatrix[v2][v1]=1;
        m++;
    }
    void removeedge(int v1, int v2)
    {
        adjmatrix[v1][v2] = 0;
        adjmatrix[v2][v1]=0;
        m--;
    }

private:
    int n; // number of vertices
    // vector <int> vertices(n);
    int m;                         // number of edges
    vector<vector<int>> adjmatrix; // adjacency matrix to store the edges, have to initiliaze it to zero

    friend std::istream &operator>>(
        std::istream &stream, Graph &g);

    friend std::ostream &operator<<(
        std::ostream &stream, Graph &g);
};

std::istream &operator>>(
    std::istream &stream, Graph &g)
{
    int n, m;
    stream >> n >> m;
    g.n = n;
    g.m = m;
    g.adjmatrix.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            g.adjmatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        stream >> x >> y;
        g.adjmatrix[x][y] = 1;
        g.adjmatrix[y][x] = 1;
    }

    return stream;
}

std::ostream &operator<<(
    std::ostream &stream, Graph &g)
{
    for (int i = 0; i < g.n; i++)
    {
        stream << "Vertex " << i << ": ";
        for (int j = 0; j < g.n; j++)
        {
            if (g.adjmatrix[i][j] == 1)
            {
                stream << j << ' ';
            }
        }
        cout << endl;
    }
    return stream;
}


int main()
{

    Graph g1;

    string s;

    while (true)
    {
        cin >> s;
        if (s == "Graph")
        {
            cin >> g1;
        }
        else if (s == "printGraph")
        {
            cout << g1;
        }
        else if (s == "union")
        {
            string p;
            cin >> p;
            Graph g2;
            cin >> g2;
            g1 + g2;
        }
        else if (s == "intersection")
        {
            string p;
            cin >> p;
            Graph g2;
            cin >> g2;
            g1-g2;
        }
        else if (s == "complement")
        {
            g1 = !g1;
        }
        else if(s=="isReachable")
        {
            int x,y;
            cin>>x>>y;
            vector <vector <int>> v=g1.showadjm();
            bool var=g1.isreachable(x,y,v);
            if(var==true)
            {
                cout<<"Yes"<<endl;
            }
            else
            {
                cout<<"No"<<endl;
            }
        }
        else if (s == "add_edge")
        {
            int x, y;
            cin >> x >> y;
            g1.addedge(x, y);
        }
        else if (s == "remove_edge")
        {
            int x, y;
            cin >> x >> y;
            g1.removeedge(x, y);
        }
        else if (s == "printGraph")
        {
            cout << g1;
        }
        else if (s == "end")
        {
            break;
        }
    }

}
