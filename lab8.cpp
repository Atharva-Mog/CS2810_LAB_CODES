#include<bits/stdc++.h>
using namespace std;

class GraphAlgorithm
{
    public:
    virtual void query(vector <vector <int>> &adjlist,vector <int> &hype){}     //virtual query function

};

bool checkcycle(vector <vector <int> > &adjlist,vector <bool> &visited,int u,vector <bool> &stack)
{
    if(stack[u]==true)
    return true;

    visited[u]=true;
    stack[u]=true;
    for(int i: adjlist[u])
    {
        if(!visited[i] && checkcycle(adjlist,visited,i,stack))
        {
            return true;
        }
        else if(stack[i])
        {
            return true;
        }
    }
    stack[u]=false;
    return false;
}
bool wrappercheckcycle(vector <vector <int>> &adjlist)
{
    int n=adjlist.size();
    vector <bool> visited(n,false);
    vector <bool> stack(n,false);
    for(int i=0;i<n;i++)
    {
        if(!visited[i] && checkcycle(adjlist,visited,i,stack))
        {
            return true;
        }
    }

    return false;
}

void dfsvisit(vector<vector<int>> &adjlist, int u, stack<int> &order, vector<int> &colour) {
    colour[u] = 1;
    for (int v : adjlist[u]) {
        if (colour[v] == 0) {
            dfsvisit(adjlist, v, order, colour);
        }
    }
    colour[u] = 2;
    order.push(u);
}

void dfsforscc(vector<vector<int>> &adjlist, stack<int> &order) {
    vector<int> colour(adjlist.size(), 0);
    for (int i = 0; i < adjlist.size(); i++) {
        if (colour[i] == 0) {
            dfsvisit(adjlist, i, order, colour);
        }
    }
}

void constructing_GTranspose(vector<vector<int>> &adjlist, vector<vector<int>> &gt) {
    gt.assign(adjlist.size(), vector<int>());
    for (int i = 0; i < adjlist.size(); i++) {
        for (int v : adjlist[i]) {
            gt[v].push_back(i);
        }
    }
}

int dfsTranspose(vector<vector<int>> &gt, int u, vector<bool> &visited) {
    visited[u] = true;
    int size = 1; 
    for (int v : gt[u]) {
        if (!visited[v]) {
            size += dfsTranspose(gt, v, visited);
        }
    }
    return size;
}

pair<int, int> findSCCWithMaxVertices(vector<vector<int>> &adjlist) {
    stack<int> order;
    dfsforscc(adjlist, order);
    
    vector<vector<int>> gt;
    constructing_GTranspose(adjlist, gt);
    
    vector<bool> visited(adjlist.size(), false);
    int maxSize = 0;
    int numSCCs = 0;

    while (!order.empty()) {
        int v = order.top();
        order.pop();
        
        if (!visited[v]) {
            int size = dfsTranspose(gt, v, visited);
            maxSize = max(maxSize, size);
            numSCCs++;
        }
    }
    
    return {numSCCs, maxSize};
}

void kahnalgo(vector <vector <int>> &adjlist,string &ans,vector <int> &result)
{
    vector <int> incomingdeg(adjlist.size());
    for(int i=0;i<adjlist.size();i++)
    {
        for(int j=0;j<adjlist[i].size();j++)
        {
            incomingdeg[adjlist[i][j]]++;
        }
    }
    priority_queue <int,vector <int> ,greater <int>> q;
   // vector <int> result;
    
    for(int i=0;i<incomingdeg.size();i++)
    {
        if(incomingdeg[i]==0)
        q.push(i);
    }
    while(!q.empty())   
    {
        int curr=q.top();
        q.pop();
        result.push_back(curr);
        for(int i:adjlist[curr])
        {
            incomingdeg[i]--;
            if(incomingdeg[i]==0)
            q.push(i);
        }

    }
    if(result.size()!=adjlist.size())
    {
        ans="NO";
    }
    return;

}


void dfstranspose2(vector<vector<int>> &gt, int u, vector<bool> &visited, vector<int> &component, 
    int &score, vector<int> &hypescore, vector<int> &nodeToComponent, int compID) {
visited[u] = true;
component.push_back(u);
score += hypescore[u]; 
nodeToComponent[u] = compID; 

for (int v : gt[u]) {
if (!visited[v]) {
dfstranspose2(gt, v, visited, component, score, hypescore, nodeToComponent, compID);
}
}
}

vector<vector<int>> findSCC2(vector<vector<int>> &adjlist, vector<int> &nodeToComponent, 
              vector<int> &sccScores, vector<int> &hypescore) {
stack<int> order;
dfsforscc(adjlist, order);  // First DFS pass to get finishing times

vector<vector<int>> gt;
constructing_GTranspose(adjlist, gt);  // Construct the transposed graph

vector<bool> visited(adjlist.size(), false);
vector<vector<int>> sccs;
int compID = 0;  // SCC counter

while (!order.empty()) {
int v = order.top();
order.pop();

if (!visited[v]) {
vector<int> component;
int score = 0;  // Sum of hypescores in SCC
dfstranspose2(gt, v, visited, component, score, hypescore, nodeToComponent, compID);
sccs.push_back(component);
sccScores.push_back(score);  // Store SCC hypescore sum
compID++;
}
}

return sccs;
}

vector<vector<int>> Condensed_Graph(vector<vector<int>> &adjlist, vector<int> &nodetocomp, int nsccs) {
vector<set<int>> condensedg(nsccs);  // Using set to avoid duplicate edges

for (int node = 0; node < adjlist.size(); node++) {  // Iterate over all nodes
int u = nodetocomp[node];  // SCC ID of current node
for (int v : adjlist[node]) {
int w = nodetocomp[v];  // SCC ID of adjacent node
if (u != w) {
 condensedg[u].insert(w);  // Add directed edge in the condensed graph
}
}
}

vector<vector<int>> condensedgfinal(nsccs);
for (int i = 0; i < nsccs; i++) {
condensedgfinal[i] = vector<int>(condensedg[i].begin(), condensedg[i].end());
}

return condensedgfinal;
}

//  DFS function to compute max hype scores in condensed graph
void dfs3(vector<vector<int>> &adjlist, vector<int> &hype, vector<int> &dp, 
int start, vector<bool> &visited) {
visited[start] = true;
dp[start] = hype[start];

for (int v : adjlist[start]) {
if (!visited[v]) {
dfs3(adjlist, hype, dp, v, visited);
}
dp[start] = max(dp[start], dp[v] + hype[start]);
}
}

//  Wrapper function to find the max hype score in condensed graph
long long  wrapperhypefunction(vector<vector<int>> &adjlist, vector<int> &hype) {
vector<int> nodeToComponent(adjlist.size(), -1);
vector<int> sccScores;

// Find SCCs
vector<vector<int>> SCC = findSCC2(adjlist, nodeToComponent, sccScores, hype);

// Construct condensed graph
int nsccs = SCC.size();
vector<vector<int>> condensedGraph = Condensed_Graph(adjlist, nodeToComponent, nsccs);

// Compute max hype score using DFS on condensed graph
vector<int> dp(nsccs, 0);
vector<bool> visited(nsccs, false);

for (int i = 0; i < nsccs; i++) {
if (!visited[i]) {
dfs3(condensedGraph, sccScores, dp, i, visited);
}
}

// Return the max element from dp vector
return *max_element(dp.begin(), dp.end());
}



class iscycle: public GraphAlgorithm
{
    public:
    void query(vector <vector <int>> &adjlist,vector <int> &hype)
    {
        bool var=wrappercheckcycle(adjlist);
        if(var)
        {ans="YES";
        return;}
        ans="NO";
        return ;
    }
    public:
    string ans;
};
class SCC:public GraphAlgorithm
{
    public:
    void query(vector <vector <int>> &adjlist,vector <int> &hype)
    {
        res=findSCCWithMaxVertices(adjlist);
        //cout<<res.first<<' '<<res.second<<endl;
        return;
    }
    public:
    pair <int,int> res;
};
class Topo: public GraphAlgorithm
{
    public:
    void query(vector <vector <int>> & adjlist,vector <int> &hype)
    {

       
        kahnalgo(adjlist,ans,res);
    }
    public:
    string ans;
    vector <int> res;
    //vector <int> res;
};
class HypeScore: public GraphAlgorithm
{
    public:
    void query(vector <vector <int>> &adjlist,vector <int> &hype)
    {
        ans=wrapperhypefunction(adjlist,hype);
        //cout<<ans<<endl;
    }
    public:
    long long ans;
};
int main()
{
    int n,m;
    cin>>n>>m;
    vector <int> hype;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        hype.push_back(x);
    }
    vector <vector <int>> adjlist(n);
    //vector <int> indeg(n,0);
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        adjlist[x-1].push_back(y-1);
        //indeg[y-1]++;
    }
    iscycle i;
    i.query(adjlist,hype);
    SCC s;
    s.query(adjlist,hype);
    Topo t;
    t.query(adjlist,hype);
    HypeScore h;
    h.query(adjlist,hype);
    int q;
    cin>>q;
    while(q--)
    {
        int k;
        cin>>k;
        if(k==1)
        {
            cout<<i.ans<<endl;
        }
        if(k==2)
        {
            cout<<s.res.first<<' '<<s.res.second<<endl;
        }
        if(k==3)
        {
            if(t.ans=="NO")
            {
                cout<<"NO"<<endl;
            }
            else
            {
                for(int i=0;i<t.res.size();i++)
                {
                    cout<<t.res[i]+1<<' ';
                }
                cout<<endl;
            }
        }
        if(k==4)
        {
            cout<<h.ans<<endl;
        }
    }



}