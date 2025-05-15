#include <bits/stdc++.h>
using namespace std;

class Island {
public:
    pair<double,double> centre_of_fig;
    double reach;
    string id;

    Island() { }

    Island(pair<double,double> centre_of_fig, double reach, string id) {
        this->centre_of_fig = centre_of_fig;
        this->reach = reach;
        this->id = id;
    }

    friend ostream& operator << (           //overloading the cout operator using ostream
        std::ostream& stream,Island &i) {
         stream<<i.id;
         return stream;
        };
    
       // virtual void takeinput(istream &input)=0 ;   
};

class Rectangle : public Island {
public:
    pair<int,int> p1, p2, p3, p4;

    Rectangle(pair<int,int>& x1,
              pair<int,int>& x2,
              pair<int,int>& x3,
              pair<int,int>& x4,
              string x)
        : Island(
            { double(x1.first + x2.first + x3.first + x4.first) / 4,
              double(x1.second + x2.second + x3.second + x4.second) / 4 },
            // diagonal / 2
            sqrtl((x3.first - x1.first) * (long double)(x3.first - x1.first)
                + (x3.second - x1.second) * (long double)(x3.second - x1.second)) / 2,
            x)
    {
        p1 = x1; p2 = x2; p3 = x3; p4 = x4;
    }
};

long double dist_max_function(pair<int,int>& x1,
                              pair<int,int>& x2,
                              pair<int,int>& x3)
{
    pair<long double,long double> p = {
        (x1.first + x2.first + x3.first) / 3.0L,
        (x1.second + x2.second + x3.second) / 3.0L
    };
    long double d1 = sqrtl((x1.first - p.first)*(x1.first - p.first)
                        + (x1.second - p.second)*(x1.second - p.second));
    long double d2 = sqrtl((x2.first - p.first)*(x2.first - p.first)
                        + (x2.second - p.second)*(x2.second - p.second));
    long double d3 = sqrtl((x3.first - p.first)*(x3.first - p.first)
                        + (x3.second - p.second)*(x3.second - p.second));
    return max({d1,d2,d3});
}

long double distance_cf(pair<double,double>& x1,
                       pair<double,double>& x2)
{
    long double dx = x1.first  - x2.first;
    long double dy = x1.second - x2.second;
    return sqrtl(dx*dx + dy*dy);
}

class Triangle : public Island {
public:
    pair<int,int> p1, p2, p3;

    Triangle(string x,
             pair<int,int>& x1,
             pair<int,int>& x2,
             pair<int,int>& x3)
        : Island(
            { (x1.first + x2.first + x3.first) / 3.0,
              (x1.second + x2.second + x3.second) / 3.0 },
            dist_max_function(x1, x2, x3),
            x)
    {
        p1 = x1; p2 = x2; p3 = x3;
    }
};

class Circle : public Island {
public:
    Circle(string x,
           pair<int,int>& x1,
           int rad)
        : Island({ double(x1.first), double(x1.second) }, rad, x)
    { }
};

Rectangle * ReadRectangle(istream &in) {
    string x;
    in>>x;
    
    int x1,y1,x2,y2,x3,y3,x4,y4;
    in>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    auto p1 = make_pair(x1,y1);
            auto p2 = make_pair(x2,y2);
            auto p3 = make_pair(x3,y3);
            auto p4 = make_pair(x4,y4);
    return new Rectangle(p1,p2,p3,p4,x);

  
}

Triangle * readTriangle(istream &in) {
   string x;
   in>>x;
   int x1,y1,x2,y2,x3,y3;
            in >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            auto p1 = make_pair(x1,y1);
            auto p2 = make_pair(x2,y2);
            auto p3 = make_pair(x3,y3);
    return new Triangle(x,p1,p2,p3);
}

Circle * readCircle(istream &in) {
    string x;
    in>>x;
    int x1,y1,rad;
    in>> x1 >> y1 >> rad;
    auto p1 = make_pair(x1,y1);
    return new Circle (x,p1,rad);

}

int main() {
    int n;
    cin >> n;

    vector<Island *> islands;
    islands.reserve(n);

    // Input the islands
    for (int i = 0; i < n; i++) {
        string shape;
        cin >> shape;

        if (shape == "TRIANGLE") {
            Triangle *t=readTriangle(cin);
            islands.push_back(t);
        }
        else if (shape == "RECTANGLE") {
            Rectangle *t=ReadRectangle(cin);
            islands.push_back(t);
           
        }
        else if (shape == "CIRCLE") {
            Circle *t=readCircle(cin);
            islands.push_back(t);
        }
    }

    vector<vector<int>> mat(n, vector<int>(n,0));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            long double d = distance_cf(
                islands[i]->centre_of_fig,
                islands[j]->centre_of_fig);
            if (d <= islands[i]->reach + islands[j]->reach) {
                mat[i][j] = mat[j][i] = 1;
            }
        }
    }

    int M = 1 << n;
    vector<vector<bool>> dp(n, vector<bool>(M, false));
    vector<vector<int>> pred(n, vector<int>(M, -1));

    // base cases
    for (int i = 0; i < n; i++) {
        dp[i][1 << i] = true;
    }

    // fill DP and pred
    for (int mask = 0; mask < M; mask++) {
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j))) continue;
            int prevMask = mask ^ (1 << j);
            for (int k = 0; k < n; k++) {
                if (k != j
                    && (prevMask & (1 << k))
                    && mat[k][j]
                    && dp[k][prevMask]) {
                    dp[j][mask] = true;
                    pred[j][mask] = k;
                    break;
                }
            }
        }
    }

    int full = M - 1;
    int endVertex = -1;

    for (int i = 0; i < n; i++) {
        if (dp[i][full]) {
            endVertex = i;
            break;
        }
    }

    vector<int> path;
    int curMask, cur;

    if (endVertex != -1) {
        // Backtrack full path
        cur = endVertex;
        curMask = full;
    } else {
        // Find longest mask
        int bestLen = 0, bestEnd = -1, bestMask = 0;
        for (int mask = 0; mask < M; mask++) {
            int len = __builtin_popcount(mask);
            if (len <= bestLen) continue;
            for (int j = 0; j < n; j++) {
                if (dp[j][mask]) {
                    bestLen = len;
                    bestEnd = j;
                    bestMask = mask;
                    break;
                }
            }
        }
        cur = bestEnd;
        curMask = bestMask;
    }

    // Reconstruct path
    while (cur != -1) {
        path.push_back(cur);
        int prev = pred[cur][curMask];
        curMask ^= (1 << cur);
        cur = prev;
    }
    reverse(path.begin(), path.end());

    // Print IDs
    if(path.size()==n)
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
        cout<<path.size()<<endl;
    }
    for (int v : path) {
        cout << islands[v]->id << " ";
    }
    cout << "\n";

    return 0;
}
