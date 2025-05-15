#include <bits/stdc++.h>
using namespace std;

class Currencysorter // quicksort done
{
public:
    void operator()(vector<long long int> &v)
    {
        quicksort(v, 0, v.size() - 1);
    }

private:
    int partition(vector<long long int> &vec, int st, int end)
    {
        long long pivot = vec[end]; // Take last element as pivot
        int l = st;                 // Start of the smaller element region

        for (int i = st; i < end; i++)
        {
            if (vec[i] < pivot)
            {
                swap(vec[i], vec[l]);
                l++;
            }
        }
        swap(vec[l], vec[end]); // Place pivot in correct position
        return l;
    }

    void quicksort(vector<long long int> &v, int st, int end)
    {
        if (st >= end)
            return; // Base case

        int l = partition(v, st, end);
        quicksort(v, st, l - 1);  // Sort left partition
        quicksort(v, l + 1, end); // Sort right partition
    }
    // vector<long long int> vec; // the vector that is to be passed
};

class FibonacciGenerator
{
public:
    unsigned long long operator()(unsigned long long x) // Functor to find fib(n)
    {
        return fibgenerator(x);
    }

private:
    const unsigned long long MOD = 1000000007;

    void matrixmul(vector<vector<unsigned long long>> &a, vector<vector<unsigned long long>> &b)
    {
        unsigned long long x = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % MOD;
        unsigned long long y = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % MOD;
        unsigned long long z = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % MOD;
        unsigned long long w = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % MOD;

        a[0][0] = x;
        a[0][1] = y;
        a[1][0] = z;
        a[1][1] = w;
    }

    void exp(vector<vector<unsigned long long>> &a, unsigned long long n)
    {
        vector<vector<unsigned long long>> res = {{1, 0}, {0, 1}}; // Identity matrix
        vector<vector<unsigned long long>> base = a;

        while (n)
        {
            if (n % 2)
                matrixmul(res, base);
            matrixmul(base, base);
            n /= 2;
        }

        a = res;
    }

    unsigned long long fibgenerator(unsigned long long n)
    {
        if (n == 0)
            return 0;
        vector<vector<unsigned long long>> a = {{1, 1}, {1, 0}};
        exp(a, n - 1);
        return a[0][0];
    }
};

class PrimeCalculator
{
public:
    PrimeCalculator()
    {
        sieve();
    }

    void operator()(long long &x, long long &y)
    {
        final(x, y);
    }

    void sieve()
    {
        long long N = 1e6;
        vector<bool> is_prime(N + 1, true);
        is_prime[0] = is_prime[1] = false;

        for (long long i = 2; i * i <= N; i++)
        {
            if (is_prime[i])
            {
                for (long long j = i * i; j <= N; j += i)
                {
                    is_prime[j] = false;
                }
            }
        }

        for (long long i = 2; i <= N; i++)
        {
            if (is_prime[i])
            {
                primes.push_back(i);
            }
        }
    }

    void final(long long l, long long r)
    {
        vector<bool> vec(r - l + 1, true);

        if (l == 1)
            vec[0] = false; // 1 is not prime

        for (long long p : primes)
        {
            if (p * p > r)
                break;

            long long firstnum = max(p * p, (l + p - 1) / p * p);
            for (long long j = firstnum; j <= r; j += p)
            {
                vec[j - l] = false;
            }
        }

        ansprimes.clear();
        sum = 0;

        for (long long i = 0; i <= r - l; i++)
        {
            if (vec[i])
            {
                ansprimes.push_back(i + l);
                sum += (i + l);
            }
        }
    }

    void printansprimes()
    {
        for (long long p : ansprimes)
        {
            cout << p << ' ';
        }
        cout << endl;
    }

    void sumprimes()
    {
        cout << sum << endl;
    }

private:
    vector<long long> primes;
    vector<long long> ansprimes;
    long long sum;
};

class NumberAnalyzer
{
public:
    NumberAnalyzer(long long x)
    {
        this->num = x;
        computeprimefactors();
    }

    bool issquarefree()
    {
        for (long long i = 2; i * i <= num; i++)
        {
            if (num % (i * i) == 0)
            {
                return false;
            }
        }
        return true;
    }

    /*int numberofdivisors()
    {
        return divisors.size();
    }*/

    void computeprimefactors()
    {

        long long n = num;

        // Count power of 2
        while (n % 2 == 0)
        {
            mp[2]++;
            n /= 2;
        }

        for (long long i = 3; i * i <= n; i += 2)
        {
            while (n % i == 0)
            {
                mp[i]++;
                n /= i;
            }
        }

        if (n > 1)
        {
            mp[n]++;
        }
    }
    long long numberdiv()
    {
        long long ans = 1;
        auto it = mp.begin();
        while (it != mp.end())
        {
            ans *= (it->second + 1);
            it++;
        }
        return ans;
       // cout << ans << endl;
    }

    long long sumofdivisors()
    {
        long long sum = 1;
        auto it = mp.begin();
        while (it != mp.end())
        {
            sum *= (pow(it->first, it->second + 1) - 1) / (it->first - 1);
            it++;
        }

        return sum;
    }

private:
    long long num;
    map<long long, long long> mp;
    // set<long long> divisors;
};

int main()
{
    int s;
    cin >> s;

    if (s == 1)
    {
        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            int n;
            cin >> n;
            vector<long long> vec(n, 0);
            for (int i = 0; i < n; i++)
            {
                cin >> vec[i];
            }
            Currencysorter c;
            c(vec);

            for (int i = 0; i < n; i++)
            {
                cout << vec[i] << ' ';
            }
            cout << endl;
        }
    }
    if (s == 2)
    {
        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            unsigned long long x;
            cin >> x;
            FibonacciGenerator f;
            unsigned long long ans = f(x);
            cout << ans << endl;
        }
    }
    if (s == 3)
    {
        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            string p;
            cin >> p;
            long long l;
            long long r;
            cin >> l >> r;
            PrimeCalculator s;
            s(l, r);
            if (p == "printPrimes")
            {
                s.printansprimes();
            }
            else
            {
                s.sumprimes();
            }
        }
    }
    if (s == 4)
    {
        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            string p;
            cin >> p;
            long long x;
            cin >> x;
            NumberAnalyzer n(x);
            if (p == "isSquareFree")
            {
                if (n.issquarefree())
                {
                    cout << "yes" << endl;
                }
                else
                {
                    cout << "no" << endl;
                }
            }
            else if (p == "countDivisors")
            {
                cout << n.numberdiv() << endl;
            }
            else
            {
                cout << n.sumofdivisors() << endl;
            }
        }
    }
}