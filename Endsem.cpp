#include<bits/stdc++.h>
using namespace std;


class Event
{
    public:
    Event(int a,int b,int event_type)
    {
        start_time=a;
        endtime=b;

    }
    void set_net_profit(double profit)
    {
        net_profit=profit;
    }

    void virtual calculateprofit()=0;
    public:
    int start_time;
    int endtime;
    int event_type;
    double net_profit;
};
class Concert:public Event
{
    public:
    Concert(int start,int end,int ticket_price,int ticket_sold,int artiste_fee,int logic_cost):Event(start,end,1)
    {
        ticketprice=ticket_price;
        ticketsold=ticket_sold;
        artistfee=artiste_fee;
        logisticcost=logic_cost;
    }
    void calculateprofit()
    {
        revenue=0.82*(ticketprice*ticketsold);
        long long cost=logisticcost+artistfee;
        double profit=revenue-cost;
        if(profit>2*cost)
        {
            net_profit=0.7*profit;
        }
        else
        {
            net_profit=profit;
        }

    }
    double getnetprofit()
    {
        return net_profit;
    }


    private:
    int ticketprice;
    int ticketsold;
    int artistfee;
    int logisticcost;
    double revenue;
    double net_profit;
};
class TheaterShow:public Event
{
    public:

    TheaterShow(int Start,int End,int BasePrice,int TotalSeats,int VenueCost):Event(Start,End,2)
    {
        base_price_ticket=BasePrice;
        total_seats=TotalSeats;
        venue_cost=VenueCost;
    }
    void calculateprofit()
    {
        revenue=0.25 *total_seats* (2 *base_price_ticket) + 0.75 * total_seats*base_price_ticket;
        revenue=0.82*revenue;
        popcorn_revenue=0.25 *total_seats*150; //popcorn revenue 

        double profit=revenue+popcorn_revenue-venue_cost;
        net_profit=profit;

    }
    double getnetprofit()
    {
        return net_profit;
    }

    private:
    int base_price_ticket;
    int total_seats;
    int venue_cost;
    double revenue;
    double net_profit;
    double popcorn_revenue;
    

};
class Wedding:public Event
{
    public:
    Wedding(int Start,int End,int  BaseAmount,int  DecorationCost,int  GuestCount,int VenueCost):Event(Start,End,3)
    {
        base_amt=BaseAmount;
        decoration_cost=DecorationCost;
        guest_count=GuestCount;
        venue_cost=VenueCost;
    }

    void calculateprofit()
    {
        if(guest_count>200)
        {
            total_venue_cost=venue_cost*3;

        }
        if(guest_count<=200)
        {
            total_venue_cost=venue_cost;
        }
        if(guest_count>100)
        {
            catering_cost=70*guest_count;
        }
        if(guest_count<=100)
        {
            catering_cost=100*guest_count;
        }
        net_profit=base_amt -total_venue_cost-decoration_cost -catering_cost; 

    }
    double getnetprofit()
    {
        return net_profit;
    }

    private:
    int base_amt;
    int decoration_cost;
    int guest_count;
    int venue_cost;
    int catering_cost;
    double net_profit;
    int total_venue_cost;
};

//function to sort the events as per end time
bool custom_comp(Event *a,Event *b)
{
    if(a->endtime==b->endtime)
    {
        return a->start_time<b->start_time;
    }
    return a->endtime<b->endtime;
}

class EventScheduler
{
    public:
    vector <Event *> Eventlist;
    vector <int> index_of_earliestendtime_before_given_index;
    //vector <double> compute_opt_solution;
    void sorter_as_per_endtime()        //this function sorts the events list as per increasing order of endtime
    {
        sort(Eventlist.begin(),Eventlist.end(),custom_comp);
    }
    int computeMaxNonConflicting(int index)
    {
    int32_t left = 0;
    int32_t right = index - 1;
    int32_t answer = -1;
    while (left <= right)
    {
        int32_t mid = left+(right-left)/2;
        if (Eventlist[mid]->endtime <= Eventlist[index]->start_time)
        {
            left = mid + 1;
            answer = mid;
        }
        else
        {
            right = mid - 1;
        }
    }
    return answer;
}
    void fill_earliest_time_index()
    {
        vector <int> vec(Eventlist.size(),-1);  //stores the last index that is before the current one
        for(int i=1;i<Eventlist.size();i++)
        {
            vec[i]=computeMaxNonConflicting(i);
        }
        index_of_earliestendtime_before_given_index=vec;
    }
    void fill_compute_opt()
    {
        vector <double> vec(Eventlist.size(),0);
        vec[0]=Eventlist[0]->net_profit;
        for(int i=1;i<Eventlist.size();i++)
        {
            if(index_of_earliestendtime_before_given_index[i]!=-1)
            {
                vec[i]=max(vec[i-1],Eventlist[i]->net_profit+vec[index_of_earliestendtime_before_given_index[i]]);
            }
            else
            {
                vec[i]=max(vec[i-1],Eventlist[i]->net_profit);
            }
        }
        double maximum=0;
        for(int i=0;i<Eventlist.size();i++)
        {
            maximum=max(maximum,vec[i]);
        }
        cout<<fixed<<setprecision(2)<<maximum<<'\n';
        //cout<<fixed<<setprecision(2)<<vec[Eventlist.size()-1]<<endl;

    }



};

int32_t main()
{
    int n;
    cin>>n;
    EventScheduler  main_event;
    
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        if(x==1)
        {
            int Start, End, TicketPrice,TicketsSold,ArtisteFee,LogisticCost;
            cin>>Start>>End>>TicketPrice>>TicketsSold>>ArtisteFee>>LogisticCost;
            Concert *c=new Concert(Start, End, TicketPrice,TicketsSold,ArtisteFee,LogisticCost);
            Event *e=c;
            c->calculateprofit();
            double net_p=c->getnetprofit();
            e->set_net_profit(net_p);
            main_event.Eventlist.push_back(e);
            //cout<<e->start_time<<' '<<e->endtime<<' '<<e->net_profit<<endl;

        }
        if(x==2)
        {
            int Start,End,BasePrice,TotalSeats,VenueCost;
            cin>>Start>>End>>BasePrice>>TotalSeats>>VenueCost;
            TheaterShow *t=new TheaterShow(Start,End,BasePrice,TotalSeats,VenueCost);
            Event *e=t;
            t->calculateprofit();
            double net_p=t->getnetprofit();
            e->set_net_profit(net_p);
            main_event.Eventlist.push_back(e);
            //cout<<e->start_time<<' '<<e->endtime<<' '<<e->net_profit<<endl;

        }
        if(x==3)
        {
            int Start, End,BaseAmount,DecorationCost,GuestCount,VenueCost;
            cin>>Start>>End>>BaseAmount>>DecorationCost>>GuestCount>>VenueCost; 
            Wedding *w=new Wedding(Start,End,BaseAmount,DecorationCost,GuestCount,VenueCost);
            Event *e=w;
            w->calculateprofit();
            double net_p=w->getnetprofit();
            e->set_net_profit(net_p);
            main_event.Eventlist.push_back(e);
            //cout<<e->start_time<<' '<<e->endtime<<' '<<e->net_profit<<endl;

        }
        
    }
    /*for(int i=0;i<n;i++)
        {
            cout<<main_event.Eventlist[i]->start_time<<' '<<main_event.Eventlist[i]->endtime<<" "<<main_event.Eventlist[i]->net_profit<<endl;
        }*/
        //cout<<endl;
        main_event.sorter_as_per_endtime();
        // for(int i=0;i<n;i++)
        // {
        //     cout<<main_event.Eventlist[i]->start_time<<' '<<main_event.Eventlist[i]->endtime<<" "<<main_event.Eventlist[i]->net_profit<<endl;
        // }  
        main_event.fill_earliest_time_index();
        // for(int i=0;i<n;i++)
        // {
        //     cout<<main_event.index_of_earliestendtime_before_given_index[i]<<endl;
        // }
        main_event.fill_compute_opt();


}