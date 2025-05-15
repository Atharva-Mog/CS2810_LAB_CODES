#include <bits/stdc++.h>
using namespace std;

string operator*(const string &s, int x) {  //overloading the * operator for string evaluation
    string res="";
    for (int i = 0; i < x; i++) {
        res += s;
    }
    return res;
}

class Complex       //creating the complex class
{
public:
    Complex() : realpart(0), imaginarypart(0) {}
    Complex(long long int a, long long int b) : realpart(a), imaginarypart(b) {}
    Complex(long long int a) : realpart(a), imaginarypart(0) {} 

    Complex operator+(const Complex &a2) const
    {
        return Complex(realpart + a2.realpart, imaginarypart + a2.imaginarypart);
    }

    Complex operator-(const Complex &a2) const
    {
        return Complex(realpart - a2.realpart, imaginarypart - a2.imaginarypart);
    }

    Complex operator*(const Complex &a2) const
    {
        return Complex(realpart * a2.realpart - imaginarypart * a2.imaginarypart,
                       realpart * a2.imaginarypart + imaginarypart * a2.realpart);
    }

    Complex &operator+=(const Complex &a2) 
    {
        realpart += a2.realpart;
        imaginarypart += a2.imaginarypart;
        return *this;
    }

    long long getreal() const { return realpart; }
    long long getimag() const { return imaginarypart; }

private:
    long long int realpart;
    long long int imaginarypart;
};

// Karatsuba Multiplication for Polynomials
template <typename T>
class Polynomial_Mult
{
public:
    Polynomial_Mult(const vector<T> &a, const vector<T> &b, int actualSize)
        : actualSize(actualSize)
    {
        int n = 16; // Fixed size for Karatsuba
        A = a;
        B = b;
        A.resize(n, T(0)); // Fix: `T(0)` works for Complex now
        B.resize(n, T(0));
    }

    vector<T> actualmul()
    {
        vector<T> result = karatsuba(A, B);
        result.resize(actualSize); // Trim excess padding
        return result;
    }

private:
    vector<T> A, B;
    int actualSize;

    vector<T> karatsuba(const vector<T> &a, const vector<T> &b)
    {
        int n = a.size();
        if (n == 1)
            return {a[0] * b[0]};

        int mid = n / 2;
        vector<T> aLow(a.begin(), a.begin() + mid);
        vector<T> aHigh(a.begin() + mid, a.end());
        vector<T> bLow(b.begin(), b.begin() + mid);
        vector<T> bHigh(b.begin() + mid, b.end());

        vector<T> low = karatsuba(aLow, bLow);
        vector<T> high = karatsuba(aHigh, bHigh);

        vector<T> aSum(mid), bSum(mid);
        for (int i = 0; i < mid; i++)
        {
            aSum[i] = aLow[i] + aHigh[i];
            bSum[i] = bLow[i] + bHigh[i];
        }

        vector<T> midProd = karatsuba(aSum, bSum);
        for (size_t i = 0; i < low.size(); i++)
            midProd[i] = midProd[i] - low[i] - high[i];

        vector<T> result(2 * n, T(0)); 
        for (size_t i = 0; i < low.size(); i++)
            result[i] += low[i];
        for (size_t i = 0; i < midProd.size(); i++)
            result[i + mid] += midProd[i];
        for (size_t i = 0; i < high.size(); i++)
            result[i + 2 * mid] += high[i];

        return result;
    }
};

// Polynomial Class
template <class T>
class Polynomial
{
public:
    Polynomial(vector<T> vec) : coefficients(vec), size(vec.size()) {}

    vector<T> getCoefficients() const { return coefficients; }

    Polynomial operator*(const Polynomial &p2) const
    {
        int resultSize = size + p2.size - 1; // actual result size
        Polynomial_Mult<T> poly_mult(coefficients, p2.coefficients, resultSize);
        return Polynomial(poly_mult.actualmul());
    }

private:
    vector<T> coefficients;
    int size;
};

template <class T>
class Polynomial_Diff
{
public:
    Polynomial_Diff(Polynomial<T> &inp) : poly(inp) {}

    Polynomial<T> pdiff()
    {
        vector<T> coefficients = poly.getCoefficients();
        vector<T> res;

        for (size_t i = 1; i < coefficients.size(); i++) // power 0 has no contribution
        {
            res.push_back(i * coefficients[i]);
        }

        return Polynomial<T>(res); //returning a polynomial 
    }

private:
    Polynomial<T> poly;
};


template <class T>
class Poly_eval {
public:
    
    Poly_eval(Polynomial<T> &poly, int x) : poly(poly), x(x) {}

    T eval() {
        vector<T> coefficients = poly.getCoefficients();
        if (coefficients.empty()) return T(); 

        T result = 0;
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            result = result * x + coefficients[i];  // horners rule
        }
        return result;
    }

    string evalstringspecial() {
        vector<T> coefficients = poly.getCoefficients();
        if (coefficients.empty()) {
            return "";
        }

        string result = "";
        long long xpow = x;

        for (size_t i = 2; i < coefficients.size(); i++) {  
            xpow *= x;
        }

        for (int i = coefficients.size() - 1; i >= 0; i--) {
            result = result+(coefficients[i] * xpow);
            xpow /= x;
        }

        return result;
    }

private:
    Polynomial<T> poly;
    long long int x;
};


//main function 

int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)  //case for t==1
        {
            string p;
            cin >> p;
            if (p == "integer")
            {
                int deg, deg2;
                cin >> deg;
                vector<long long> vec(deg);
                for (int i = 0; i < deg; i++)
                {
                    cin >> vec[i];
                }

                cin >> deg2;
                vector<long long> vec2(deg2);
                for (int i = 0; i < deg2; i++)
                {
                    cin >> vec2[i];
                }

                Polynomial<long long> p1(vec);
                Polynomial<long long> p2(vec2);
                Polynomial<long long> result = p1 * p2;

                vector<long long> resvec = result.getCoefficients();
                for (long long val : resvec)
                {
                    cout << val << ' ';
                }
                cout << endl;
            }

            else if (p == "float")
            {
                int deg, deg2;
                cin >> deg;
                vector<long double> vec(deg);
                for (int i = 0; i < deg; i++)
                {
                    cin >> vec[i];
                }

                cin >> deg2;
                vector<long double> vec2(deg2);
                for (int i = 0; i < deg2; i++)
                {
                    cin >> vec2[i];
                }

                Polynomial<long double> p1(vec);
                Polynomial<long double> p2(vec2);
                Polynomial<long double> result = p1 * p2;

                vector<long double> resvec = result.getCoefficients();
                cout << fixed << setprecision(6);
                for (long double val : resvec)
                {
                    cout << val << ' ';
                }
                cout << endl;
            }

            else if (p == "complex")
            {
                int deg, deg2;
                cin >> deg;
                vector<Complex> vec;
                for (int i = 0; i < deg; i++)
                {
                    long long x, y;
                    cin >> x >> y;
                    vec.push_back(Complex(x, y));
                }

                cin >> deg2;
                vector<Complex> vec2;
                for (int i = 0; i < deg2; i++)
                {
                    long long x, y;
                    cin >> x >> y;
                    vec2.push_back(Complex(x, y));
                }

                Polynomial<Complex> p1(vec);
                Polynomial<Complex> p2(vec2);
                Polynomial<Complex> result = p1 * p2;

                vector<Complex> resvec = result.getCoefficients();
                for (const Complex &c : resvec)
                {
                    cout << c.getreal() << ' ' << c.getimag() << ' ';
                }
                cout << endl;
            }
        }
        if(t==2)  //case for t==2
        {
            string p;
            cin >> p;
            if (p == "integer") {
                long long int n;
                cin >> n;
                vector< long long int> vec(n);
                for (int i = 0; i < n; i++) {
                    cin >> vec[i];
                }
                long long int evalp;
                cin >> evalp;
                Polynomial<long long int> poly(vec);
                Poly_eval<long long int> pe(poly, evalp);
                cout << pe.eval() << endl;
            } else if (p == "string") {
                long long int n;
                cin >> n;
                vector<string> vec(n);
                for (int i = 0; i < n; i++) {
                    cin >> vec[i];
                }
                long long int evalp;
                cin >> evalp;
                Polynomial<string> poly(vec);
                Poly_eval<string> pe(poly, evalp);
                cout << pe.evalstringspecial() << endl;
            } else if (p == "float") {
                long long int n;
                cin >> n;
                vector<long double> vec(n);
                for (int i = 0; i < n; i++) {
                    cin >> vec[i];
                }
                long long int evalp;
                cin >> evalp;
                Polynomial<long double> poly(vec);
                Poly_eval<long double> pe(poly, evalp);
                cout<<fixed<<setprecision(6);
                cout << pe.eval() << endl;
            }
        }
        if (t == 3) //case for t==3
        {
            string s;
            cin >> s;
            if (s == "integer")
            {
                long long int deg;
                cin >> deg;
                vector<long long int> coeff(deg, 0);
                for (size_t i = 0; i < static_cast<size_t>(deg); i++) 
                {
                    cin >> coeff[i];
                }
                Polynomial<long long int> P(coeff);
                Polynomial_Diff<long long int> pd(P);
                Polynomial <long long int> ans1 = pd.pdiff();
                vector <long long int> ans=ans1.getCoefficients();
                for (size_t i = 0; i < ans.size(); i++)  
                {
                    cout << ans[i] << ' ';
                }
                cout << endl;
            }
            if (s == "float")
            {
                long long int deg;
                cin >> deg;
                vector<long double> coeff(deg, 0);
                for (size_t i = 0; i < static_cast<size_t>(deg); i++) 
                {
                    cin >> coeff[i];
                }
                Polynomial<long double> P(coeff);
                Polynomial_Diff<long double> pd(P);
              
                Polynomial <long double> ans1 = pd.pdiff();
                vector <long double>ans=ans1.getCoefficients();
                cout<<fixed<<setprecision(6);
                for (size_t i = 0; i < ans.size(); i++) 
                {
                    cout << ans[i] << ' ';
                }
                cout << endl;
            }
        }
    }
    return 0;
}
