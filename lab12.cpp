#include <bits/stdc++.h>
using namespace std;

class Card {
public:
    Card() { strength = 0; }

    Card(long long s, int p, long long f, long long u)
    {
        this->strength = s;
        this->p = p;
        this->first = f;
        this->second = u;
    }

    long long getstrength() const { return this->strength; }
    int getp() const { return this->p; }

    bool operator<(const Card &b) const { return this->strength < b.strength; }
    bool operator>(const Card &b) const { return this->strength > b.strength; }

    long long printfirst() const { return this->first; }
    long long printsecond() const { return this->second; }

    friend ostream &operator<<(ostream &stream, const Card &c)
    {
        if(c.getp() == 0) {
            stream << "SQUARE " << c.printfirst();
        } else if (c.getp() == 1) {
            stream << "RECTANGLE " << c.printfirst() << " " << c.printsecond();
        } else {
            stream << "TRIANGLE " << c.printfirst() << " " << c.printsecond();
        }
        return stream;
    }

protected:
    long long strength;
    int p;
    long long first;
    long long second;
};

class Square : public Card {
public:
    Square(long long e) : Card(e * e, 0, e, e) { }
};

class Rectangle : public Card {
public:
    Rectangle(long long l, long long r) : Card(l * r, 1, l, r) { }
};

class Triangle : public Card {
public:
    Triangle(long long x, long long y) : Card(x * y / 2, 2, x, y) { }
};

bool comp(const Card &A, const Card &B)
{
    return A.getstrength() < B.getstrength();
}

class CardOrganizer {
public:
    void add_card(const Card &c)
    {
        listofcards.push_back(c);
        addtopile(c);
        isLISDirty = true;
    }

    void addtopile(const Card &c)
    {
        auto it = lower_bound(listofpilestop.begin(), listofpilestop.end(), c, comp);
        if (it == listofpilestop.end()) {
            listofpilestop.push_back(c);
        } else {
            *it = c;
        }
    }

    size_t getpilecount() const {
        return listofpilestop.size();
    }

    vector<Card> getLIS()
    {
        if (!isLISDirty) return cachedLIS;

        if (listofcards.empty()) return {};

        int n = listofcards.size();
        vector<Card> dp;
        vector<int> prev(n, -1);
        vector<int> indices(n, -1);

        for (int i = 0; i < n; ++i) {
            int pos = lower_bound(dp.begin(), dp.end(), listofcards[i],
                                  [](const Card& a, const Card& b) {
                                      return a.getstrength() < b.getstrength();
                                  }) - dp.begin();

            if (pos < dp.size()) {
                dp[pos] = listofcards[i];
            } else {
                dp.push_back(listofcards[i]);
            }

            if (pos > 0) prev[i] = indices[pos - 1];
            indices[pos] = i;
        }

        vector<Card> result;
        int idx = indices[dp.size() - 1];
        while (idx != -1) {
            result.push_back(listofcards[idx]);
            idx = prev[idx];
        }

        reverse(result.begin(), result.end());
        cachedLIS = result;
        isLISDirty = false;
        return cachedLIS;
    }

private:
    vector<Card> listofcards;
    vector<Card> listofpilestop;
    vector<Card> cachedLIS;
    bool isLISDirty = true;
};

// Custom input functions
Square readSquare(istream &in) {
    long long side;
    in >> side;
    return Square(side);
}

Rectangle readRectangle(istream &in) {
    long long l, b;
    in >> l >> b;
    return Rectangle(l, b);
}

Triangle readTriangle(istream &in) {
    long long base, height;
    in >> base >> height;
    return Triangle(base, height);
}

int main()
{
    int q;
    cin >> q;
    CardOrganizer org;

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            string shape;
            cin >> shape;
            if (shape == "SQUARE") {
                Square s = readSquare(cin);
                org.add_card(s);
            } else if (shape == "RECTANGLE") {
                Rectangle r = readRectangle(cin);
                org.add_card(r);
            } else if (shape == "TRIANGLE") {
                Triangle t = readTriangle(cin);
                org.add_card(t);
            }
        } else if (x == 2) {
            cout << org.getpilecount() << "\n";
        } else if (x == 3) {
            cout << org.getpilecount() << "\n";
            vector<Card> lis = org.getLIS();
            for (const auto &card : lis) {
                cout << card << "\n";
            }
        }
    }

    return 0;
}
