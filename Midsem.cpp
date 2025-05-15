#include<bits/stdc++.h>
using namespace std;

#define ll long long 





/*class Comparator // functor to sort the array
{
public:
    bool Operator(){b=1;}

    bool operator()(Employee * a, Employee *c)
    {
        if(b==1)
        {
            if((*a).getexp()==(*c).getexp())
    {
        return (*a).getempid()<(*c).getempid();
    }
    return (*a).getexp()<(*c).getexp();
        }
        if(b==2)
        {
            if((*a).getage()==(*c).getage())
    {
        return (*a).getempid()<(*c).getempid();
    }
    return (*a).depth<(*c).depth;
        }
        if(b==3)
        {

        }
    }
    void changeb(int k)
    {
        b=k;
    }
private:
int b;

}; */


class Employee
{
    public:
    Employee(ll a,ll b,ll c,ll d)
    {
        this->empid=a;
        this->age=b;
        this->experience=c;
        this->boss=d;
        this->depth=0;

    }
    void addchild(Employee * n)
    {
        children.push_back(n);
    }
    void maptoparent(Employee *n)
    {
        parent=n;
    }
    long long getboss()
    {
        return boss;
    }
    long long getempid()
    {
        return empid;
    }
    long long getexp()
    {
        return experience;
    }
    long long getage()
    {
        return age;
    }
    vector <Employee *> getchildren()
    {
        return children;
    }
    void printdetails()
    {
        cout<<empid<<' '<<age<<' '<<experience<<' '<<boss<<endl;
        cout<<"children:";
        for(int i=0;i<children.size();i++)
        {
            cout<<(*children[i]).empid<<' ';

        }
        cout<<endl;
        cout<<endl;
    }
    ll depth;
    private:

    ll empid;
    ll age;
    ll experience;
    ll boss;
   
    vector <Employee *> children;
    Employee * parent;
};

bool sorti(Employee *a,Employee *c)
{
    if((*a).getage()==(*c).getage())
    {
        return (*a).getempid()<(*c).getempid();
    }
    return (*a).getage()<(*c).getage();
}


long long bfs(Employee *e,map <long long,Employee *> &mp)
{
    map <long long,bool> visited;
    auto it=mp.begin();
    while(it!=mp.end())
    {
       visited[it->first]=false;
       it++;
    }
    visited[(*e).getempid()]=true;
    queue <Employee *> q;
    q.push(e);
    long long sum=0;
    long long times=0;
    vector <Employee *> res;
    while(!q.empty())
    {
        Employee *curr=q.front();
        q.pop();
        //curr->printdetails();
        //sum+=curr->getexp();
        res.push_back(curr);
        vector <Employee *> childin=curr->getchildren();
        for(int i=0;i<curr->getchildren().size();i++)
        {
            
            if(!visited[childin[i]->getempid()])
            {
                q.push(childin[i]);
                //sum+=childin[i]->getexp();
                visited[childin[i]->getempid()]=true;
            }
        }
    }
    for(int i=0;i<res.size();i++)
    {
        sum+=res[i]->getexp();
        
    }
    long long ans2=sum/res.size();
    return ans2;
}
void bfs2(Employee *e,map <long long,Employee *> &mp)
{
    map <long long,bool> visited;
    auto it=mp.begin();
    while(it!=mp.end())
    {
       visited[it->first]=false;
       it++;
       it->second->depth=0;
    }
    visited[(*e).getempid()]=true;
    queue <Employee *> q;
    q.push(e);
    
    while(!q.empty())
    {
        Employee *curr=q.front();
        q.pop();
        vector <Employee *> childin=curr->getchildren();
        for(int i=0;i<curr->getchildren().size();i++)
        {
            
            if(!visited[childin[i]->getempid()])
            {
                if(childin[i]!=e)
                {
                childin[i]->depth=curr->depth+1;
                }
                q.push(childin[i]); 
                visited[childin[i]->getempid()]=true;
            }
        }
    }
}

long long kthsmallest(long long a, long long k, map <long long,Employee *> &mp)
{
    Employee *e=mp[a];
    map <long long,bool> visited;
    auto it=mp.begin();
    while(it!=mp.end())
    {
       visited[it->first]=false;
       it++;
    }
    visited[(*e).getempid()]=true;
    queue <Employee *> q;
    q.push(e);
    long long sum=0;
    long long times=0;
    vector <Employee *> res;
    while(!q.empty())
    {
        Employee *curr=q.front();
        q.pop();
        //curr->printdetails();
        //sum+=curr->getexp();
        res.push_back(curr);
        vector <Employee *> childin=curr->getchildren();
        for(int i=0;i<curr->getchildren().size();i++)
        {
            
            if(!visited[childin[i]->getempid()])
            {
                q.push(childin[i]);
                //sum+=childin[i]->getexp();
                visited[childin[i]->getempid()]=true;
            }
        }
    }
    if(k>res.size())
    {
        return -1;
    }
    else
    {
        sort(res.begin(),res.end(),sorti);
        long long ans=res[k-1]->getempid();
        return ans;
    }



}




int main()
{
    int n;
    cin>>n;
    Employee * root;
    //map <ll,Employee *> mp;
    map <ll, Employee *> mp;

    vector <Employee *> vec;
    
    int ind=0;
    for(int i=0;i<n;i++)
    {
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        Employee *e=new Employee(a,b,c,d);
        vec.push_back(e);
        mp[a]=e;
        if(a==d)
        {
            ind=i;
        }
        //mp[a]=e;    
    }

    auto it=mp.begin();
   // Employee *root;
    while(it!=mp.end())
    {
        it->second->maptoparent(mp[it->second->getboss()]);
        mp[it->second->getboss()]->addchild(it->second);
        if(it->second->getboss()==it->second->getempid())
        {
            root=it->second;
        }
        it++;   
    }
    /*auto it2=mp.begin();
    while(it2!=mp.end())
    {
       (* (it2->second)).printdetails();
       it2++;
    }*/
    //(*root).printdetails();
    //bfs2(root,mp);

    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int x;
        cin>>x;
        if(x==1)
        {
            long long p;
            cin>>p;
           // Comparator c;
            //c.changeb(p);
            if(p==1)
            {
                long long ans=0;
                for(int i=0;i<vec.size();i++)
                {
                    for(int j=i+1;j<vec.size();j++)
                    {
                        if(vec[i]->getexp()>vec[j]->getexp() && vec[i]->depth<vec[j]->depth)
                        {
                            ans++;
                        }
                        

                    
                    }
                }
                cout<<ans<<endl;
                
            }
            else if(p==2)
            {
                long long ans=0;
                for(int i=0;i<vec.size();i++)
                {
                    for(int j=i+1;j<vec.size();j++)
                    {
                        if(vec[i]->getage()>vec[j]->getage() && vec[i]->depth<vec[j]->depth)
                        {
                            ans++;
                        }
                        

                    
                    }
                }
                cout<<ans<<endl;
            }
            else if(p==3)
            {
                long long ans=0;
                for(int i=0;i<vec.size();i++)
                {
                    for(int j=i+1;j<vec.size();j++)
                    {
                        if(vec[i]->getexp()>vec[j]->getexp() && vec[i]->getage()<vec[j]->getage())
                        {
                            ans++;
                        }
                        

                    
                    }
                }
                cout<<ans<<endl;
            }
            
        }
        if(x==2)
        {
            long long id;
            cin>>id;
            Employee *t=mp[id];
            long long ans=bfs(t,mp);
            cout<<ans<<endl;
        }
        if(x==3)
        {
            long long p;
            cin>>p;
            long long k;
            cin>>k;
            long long ans=kthsmallest(p,k,mp);
            cout<<ans<<endl;
            
        }
    }
}