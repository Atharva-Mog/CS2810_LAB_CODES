#include <bits/stdc++.h>
using namespace std;

class qns
{
public:
    bool overheatshut = false; // overheatshut and destroy are parameters initialised to false
    bool destroy = false;
    qns(int a = 1000, int b = 500, int c = 300, int d = 0) // both parametrized and default constructors are part of this
    {
        this->powerlevel = min(a, 5000);
        this->durability = b;
        this->energystorage = c;
        this->heatlevel = max(d,0);
        
    }

    qns(const qns &x) // copy constructor
    {
        this->powerlevel = x.powerlevel;
        this->durability = x.durability;
        this->energystorage = x.energystorage;
        this->heatlevel = x.heatlevel;
        heatlevel = max(0, heatlevel);
        powerlevel = min(5000, powerlevel);

    }

    qns &operator+(qns &q2) // overloading +
    {
        this->powerlevel += q2.energystorage;
        this->durability += q2.durability;
        this->energystorage += q2.powerlevel;
        heatlevel = max(0, heatlevel);
        powerlevel = min(5000, powerlevel);

        return *this;
    }

    qns &operator-(int x) // overloading -
    {
        this->durability -= x;
        this->energystorage += x;
        this->heatlevel += x;
        heatlevel = max(0, heatlevel);
        powerlevel = min(5000, powerlevel);
        checkdurability(); // suit is destroyed if d<=0
        checkheatlevel();
        return *this;
    }

    qns &operator*(int x) // overloading *
    {
        this->powerlevel = this->powerlevel + ((this->powerlevel) * x / 100);
        this->energystorage += 5 * x;
        this->heatlevel += x;
        heatlevel = max(0, heatlevel);
        powerlevel = min(5000, powerlevel);
        checkheatlevel(); // check heat level

        return *this;
    }

    qns &operator/(int x) // overloading /
    {
        this->durability += x;
        this->heatlevel -= x;
        heatlevel = max(0, heatlevel);
        powerlevel = min(5000, powerlevel);
        checkheatlevel(); // check heat level
        return *this;
    }

    void boostpower(int factor) // function overloading for boostpower using * operator
    {
        (*this) * factor;
        return;
    }

    void boostpower(qns &othersuit) // function overloading for boostpower using + operator
    {
        (*this) + othersuit;
        return;
    }

    bool operator==(const qns &q1) // overloading equality operator
    {
        return this->powerlevel == q1.powerlevel && this->durability == q1.durability;
    }

    bool operator<(const qns &q1) // overloading less than operator
    {
        return (this->powerlevel + this->durability) < (q1.powerlevel + q1.durability);
    }

    int getpowerlevel() const
    {
        return this->powerlevel;
    }
    int getdurability() const
    {
        return this->durability;
    }
    int getheatlevel() const
    {
        return this->heatlevel;
    }
    int getenergystorage() const
    {
        return this->energystorage;
    }
    void setpowerlevel(int x)
    {
        this->powerlevel = x;
    }
    void setdurability(int x)
    {
        this->durability = x;
    }
    void setheatlevel(int x)
    {
        this->heatlevel = x;
    }
    void setenergystorage(int x)
    {
        this->energystorage = x;
    }

    void checkheatlevel() // Adding additional functions to check if the constraints of the problem are satisfied
    {
        if (this->heatlevel > 500)
        {
            this->overheatshut = true;
        }
        if (this->heatlevel < 0)
        {
            this->heatlevel = 0;
        }
    }

    void checkdurability()
    {
        if (this->durability <= 0)
        {
            this->destroy = true;
        }
    }

    void checktotalpowerlevel()
    {
        if (this->heatlevel > 5000)
        {
            this->powerlevel = 5000;
        }
    }

private: // private attributes declared here
    int powerlevel;
    int durability;
    int energystorage;
    int heatlevel;
};

class avenger // avenger class
{
public:
    avenger(string a, qns &b, int c) // constructor for the class avenger
        : name(a), personalquantumsuit(b), attackstrength(c)
    {
    }

    avenger() {}

    void attack(avenger &enemy) // attack function
    {
        int num = this->attackstrength;
        enemy.personalquantumsuit - num;
    }

    void upgradesuit(qns &q1) // upgrade suit function, parameter passed, + overloaded function is going to be used
    {
        this->personalquantumsuit + q1;
    }

    void repair(int x) // repair function
    {
        this->personalquantumsuit / x;
    }

    void printstatus() // print function
    {
        cout << this->name << ' ' << this->personalquantumsuit.getpowerlevel() << ' ' << this->personalquantumsuit.getdurability() << ' ' << this->personalquantumsuit.getenergystorage() << ' ' << this->personalquantumsuit.getheatlevel() << endl;
    }

    qns &getquantumsuit()
    {
        return this->personalquantumsuit;
    }

    string getname() const
    {
        return this->name;
    }

private: // private attributes of the class avenger
    string name;
    qns personalquantumsuit;
    int attackstrength;
};

class battle
{
public:
    map<string, avenger> heroesmap;
    map<string, avenger> enemiesmap;

    void startbattle()
    {
        while (true)
        {
            string p;
            cin >> p;
            if (p == "Attack")
            {
                string s1, s2;
                cin >> s1 >> s2;
                int index1=-1;
                int index2=-1;
                avenger *a1;
                avenger *a2;
                for(int i=0;i<int(heroes.size());i++)
                {
                    if(s1==heroes[i].getname())
                    {
                        index1=i;
                        a1=&heroes[i];
                    }
                    if(s2==heroes[i].getname())
                    {
                        index2=i;
                        a2=&heroes[i];
                    }
                    
                }
                for(int i=0;i<int(enemies.size());i++)
                {
                    if(s1==enemies[i].getname())
                    {
                        index1=i;
                        a1=&enemies[i];
                    }
                    if(s2==enemies[i].getname())
                    {
                        index2=i;
                        a2=&enemies[i];
                    }
                    
                }
                if ((*a1).getquantumsuit().getdurability() > 0 && (*a1).getquantumsuit().getheatlevel() < 500 && (*a2).getquantumsuit().getdurability() > 0)
                    {
                        (*a1).attack(*a2);
                        this->modifybattlelog(s1 + " attacks " + s2);

                        if ((*a2).getquantumsuit().getdurability() <= 0)
                        {
                            string q = s2 + " suit destroyed";
                            this->modifybattlelog(q);
                        }
                        else if ((*a2).getquantumsuit().getheatlevel() > 500)
                        {
                            string r = s2 + " suit overheated";
                            this->modifybattlelog(r);
                        }
                    }
            }
                
                /*if (this->heroesmap.find(s1) != this->heroesmap.end())
                {
                    int index1 = -1;
                    int index2 = -1;

                    for (int i = 0; i < int(this->getheroes().size()); i++)
                    {
                        if (s1 == this->getheroes()[i].getname())
                        {
                            index1 = i;
                        }
                    }
                    for (int i = 0; i < int(this->getenemies().size()); i++)
                    {
                        if (s2 == this->getenemies()[i].getname())
                        {
                            index2 = i;
                        }
                    }
                    auto &hero = this->getheroes()[index1];
                    auto &enemy = this->getenemies()[index2];
                    if (hero.getquantumsuit().getdurability() > 0 && hero.getquantumsuit().getheatlevel() < 500 && enemy.getquantumsuit().getdurability() > 0)
                    {
                        hero.attack(enemy);
                        this->modifybattlelog(s1 + " attacks " + s2);

                        if (enemy.getquantumsuit().getdurability() <= 0)
                        {
                            string q = s2 + " suit destroyed";
                            this->modifybattlelog(q);
                        }
                        else if (enemy.getquantumsuit().getheatlevel() > 500)
                        {
                            string r = s2 + " suit overheated";
                            this->modifybattlelog(r);
                        }
                    }
                }
                else
                {
                    int index1 = -1;
                    int index2 = -1;
                    for (int i = 0; i < int(this->getheroes().size()); i++)
                    {
                        if (s2 == this->getheroes()[i].getname())
                        {
                            index1 = i;
                        }
                    }
                    for (int i = 0; i < int(this->getenemies().size()); i++)
                    {
                        if (s1 == this->getenemies()[i].getname())
                        {
                            index2 = i;
                        }
                    }
                    auto &hero = this->getheroes()[index1];
                    auto &enemy = this->getenemies()[index2];
                    if (enemy.getquantumsuit().getdurability() > 0 && enemy.getquantumsuit().getheatlevel() < 500 && hero.getquantumsuit().getdurability() > 0)
                    {
                        string x = s1 + " attacks " + s2;
                        enemy.attack(hero);
                        this->modifybattlelog(x);

                        if (hero.getquantumsuit().getdurability() <= 0)
                        {
                            string q = s2 + " suit destroyed";
                            this->modifybattlelog(q);
                        }
                        else if (hero.getquantumsuit().getheatlevel() > 500)
                        {
                            string r = s2 + " suit overheated";
                            this->modifybattlelog(r);
                        }
                    }
                }
            }*/
            else if (p == "Repair")
            {
                string s1;
                int x;
                cin >> s1 >> x;
                for (int i = 0; i < int(this->getheroes().size()); i++)
                {
                    if (s1 == this->getheroes()[i].getname())
                    {
                        qns &h = this->getheroes()[i].getquantumsuit();
                        h / x;
                    }
                }
                for (int i = 0; i < int(this->getenemies().size()); i++)
                {
                    if (s1 == this->getenemies()[i].getname())
                    {
                        qns &h = this->getenemies()[i].getquantumsuit();
                        h / x;
                    }
                }
                string a = s1 + " repaired";
                this->modifybattlelog(a);
            }
            else if (p == "BoostPowerByFactor")
            {
                string s1;
                int x;
                cin >> s1 >> x;
                int report = 0;
                for (int i = 0; i < int(this->getheroes().size()); i++)
                {
                    if (s1 == this->getheroes()[i].getname())
                    {
                        qns &h = this->getheroes()[i].getquantumsuit();
                        h.boostpower(x);
                        if (h.getheatlevel() > 500)
                            report = 1;
                    }
                }
                for (int i = 0; i < int(this->getenemies().size()); i++)
                {
                    if (s1 == this->getenemies()[i].getname())
                    {
                        qns &h = this->getenemies()[i].getquantumsuit();
                        h.boostpower(x);
                        if (h.getheatlevel() > 500)
                            report = 1;
                    }
                }
                string a = s1 + " boosted";

                this->modifybattlelog(a);
                if (report)
                {
                    string d = s1 + " suit overheated";

                    this->modifybattlelog(d);
                }
            }
            else if (p == "BoostPower")
            {
                string s1;
                int p, d, e, h;
                cin >> s1;
                cin >> p >> d >> e >> h;
                qns q(p, d, e, h);
                for (int i = 0; i < int(this->getheroes().size()); i++)
                {
                    if (s1 == this->getheroes()[i].getname())
                    {
                        auto &it = this->getheroes()[i].getquantumsuit();
                        it.boostpower(q);
                    }
                }
                for (int i = 0; i < int(this->getenemies().size()); i++)
                {
                    if (s1 == this->getenemies()[i].getname())
                    {
                        auto &it = this->getenemies()[i].getquantumsuit();
                        it.boostpower(q);
                    }
                }
                string w = s1 + " boosted";

                this->modifybattlelog(w);
            }
            else if (p == "AvengerStatus")
            {
                string s;
                cin >> s;
                for (int i = 0; i < int(this->getheroes().size()); i++)
                {
                    if (s == this->getheroes()[i].getname())
                    {
                        this->getheroes()[i].printstatus();
                    }
                }
                for (int i = 0; i < int(this->getenemies().size()); i++)
                {
                    if (s == this->getenemies()[i].getname())
                    {
                        this->getenemies()[i].printstatus();
                    }
                }
            }
            else if (p == "Upgrade")
            {
                string s;
                cin >> s;
                if (this->getsuits().size() != 0)
                {
                    for (int i = 0; i < int(this->getheroes().size()); i++)
                    {
                        if (s == this->getheroes()[i].getname())
                        {
                            this->getheroes()[i].getquantumsuit() + this->getsuits().front();
                            this->getsuits().pop();
                        }
                    }
                    for (int i = 0; i < int(this->getenemies().size()); i++)
                    {
                        if (s == this->getenemies()[i].getname())
                        {
                            this->getenemies()[i].getquantumsuit() + this->getsuits().front();
                            this->getsuits().pop();
                        }
                    }
                    string x = s + " upgraded";

                    this->modifybattlelog(x);
                }
                else
                {
                    string x = s + " upgrade Fail";
                    this->modifybattlelog(x);
                }
            }
            else if (p == "End")
            {
                break;
            }
            else if (p == "PrintBattleLog")
            {
                this->printbattlelog();
            }
            else if (p == "BattleStatus")
            {
                if (this->result() == 1)
                {
                    cout << "heroes are winning" << endl;
                }
                else if (this->result() == 0)
                {
                    cout << "tie" << endl;
                }
                else
                {
                    cout << "enemies are winning" << endl;
                }
            }
        }
    }
    void printbattlelog()
    {
        for (const auto &log : this->battlelog)
        {
            cout << log << endl;
        }
    }

    void modifybattlelog(string x)
    {
        this->battlelog.push_back(x);
    }

    int result()
    {
        int sumheroes = 0;
        int sumenemies = 0;
        for (int i = 0; i < heroes.size(); i++)
        {
            if (heroes[i].getquantumsuit().getdurability() > 0)
            {
                sumheroes += (heroes[i].getquantumsuit().getdurability() + heroes[i].getquantumsuit().getpowerlevel());
            }
        }
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].getquantumsuit().getdurability() > 0)
            {
                sumenemies += (enemies[i].getquantumsuit().getdurability() + enemies[i].getquantumsuit().getpowerlevel());
            }
        }
        if (sumheroes > sumenemies)
        {
            return 1;
        }
        else if (sumheroes < sumenemies)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    void fillsuits(int k)
    {
        for (int i = 0; i < k; i++)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            suits.push(qns(a, b, c, d));
        }
    }

    void fillheroes(int n)
    {
        for (int i = 0; i < n; i++)
        {
            string a;
            int b;
            cin >> a >> b;
            if (suits.size() != 0)
            {
                avenger x(a, suits.front(), b); // Construct the avenger object properly
                heroes.push_back(x);
                heroesmap[a] = x; // Store the object in the map using the name as the key
                suits.pop();
            }
            else
            {
                cout << a << " is out of fight" << endl;
            }
        }
    }

    void fillenemies(int m)
    {
        for (int i = 0; i < m; i++)
        {
            string a;
            int b;
            cin >> a >> b;
            if (suits.size() != 0)
            {
                avenger x(a, suits.front(), b); // Construct the avenger object properly
                enemies.push_back(x);
                enemiesmap[a] = x; // Store the object in the map using the name as the key
                suits.pop();
            }
            else
            {
                cout << a << " is out of fight" << endl;
            }
        }
    }

    vector<avenger> &getheroes()
    {
        return this->heroes;
    }

    vector<avenger> &getenemies()
    {
        return this->enemies;
    }

    queue<qns> &getsuits()
    {
        return this->suits;
    }

private:
    vector<avenger> heroes;
    vector<avenger> enemies;
    vector<string> battlelog;
    queue<qns> suits;
};

int main()
{
    int k, m, n;
    cin >> k >> n >> m;
    battle b;
    b.fillsuits(k);
    b.fillheroes(n);
    b.fillenemies(m);

    string s; // s is battlebegin string
    cin >> s;
    b.startbattle();
}