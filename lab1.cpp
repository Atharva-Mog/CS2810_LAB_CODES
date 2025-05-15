#include<bits/stdc++.h>
    using namespace std;

    class Book{

        public:
        string booktitle;
        string author;

        Book(string a,string b,string c,int d,int e)  //parameterized constructor
        {
            this->booktitle=a;
            this->author=b;
            this->isbn=c;
            this->copiesavailable=d;
            this->totalcopies=e;
        }

        Book()                                  //default constructor
        {
            this->booktitle="UnknownTitle";
            this->author="UnknownAuthor";
            this->isbn="ISBN";
            this->copiesavailable=0;
            this->totalcopies=5;

        }

        Book(Book &t,string isbncode)              //copy constructor
        {
            this->booktitle=t.booktitle;
            this->author=t.author;
            this->isbn=isbncode;
            this->copiesavailable=t.copiesavailable;
            this->totalcopies=t.totalcopies;
        }

        private:
        string isbn;
        int copiesavailable;
        int totalcopies;
        


        public:

        string getisbn()            //getisbn
        {
            return this->isbn;
        }

        int getcopiesavailable()    //getcopiesavailable
        {
            return this->copiesavailable;
        }

        int gettotalcopies()          //gettotalcopies
        {

            return this->totalcopies;

        }
        
        bool updatecopies(int count)        //updatecopies
        {
            int num1=this->copiesavailable;
            int num2=this->totalcopies;
           // int num3=min(num1,num2);
            if(num1+count<0)
            {
                cout<<"Invalid request! Count becomes negative"<<endl;
                return false;
            }
            
                this->copiesavailable+=count;
                this->totalcopies+=count;
            
            return true;
        }


        bool borrowbook()       //borrowbook,book perspective
        {
            if(this->copiesavailable>0)
            {
                this->copiesavailable-=1;
                return true;
            }
            cout<<"Invalid request! Copy of book not available"<<endl;      
            return false;
        }


        bool returnbook()       //return book, book perspective
        {
            if(this->copiesavailable<this->totalcopies)
            {
                this->copiesavailable++;
                return true;
            }
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
        }

        void printdetails()   //print details of the book
        {
            cout<<this->booktitle<<' '<<this->author<<endl;
        }
    };


    class Member
    {
        private:
        string memberid;
        string name;
        map <string,int> borrowedbook;
        int borrowlimit;
        int currentborrow;      //this is to keep track of how many boooks the member has borrowed so far

        public:
        Member(string a,string b,int c=3)   //both functionalities implemented in the same constuctor
        {
            this->memberid=a;
            this->name=b;
            this->borrowlimit=c;
            this->currentborrow=0;   //initialising current borrow to zero
        }


        string getmember()                  //function to get memberid
        {
            return this->memberid;
        }

        string getname()            //function to get name
        {
            return this->name;
        }

        /*void bookborrowvalueonly(string isbn)
        {
            this->currentborrow+=1;
        }*/

        bool bookborrow(string isbn)        //borrowbook from member perspective
        {
            if(this->currentborrow<this->borrowlimit)   //found an error, debugging done
            {
            
                this->currentborrow++;
                this->borrowedbook[isbn]++;
                return true;
            }
            cout<<"Invalid request! Borrow limit exceeded"<<endl;
            return false;
        }

        bool returnbook(string isbn)            //return book from member perpespective
        {
            if(this->borrowedbook.find(isbn)!=this->borrowedbook.end() && this->borrowedbook[isbn]>0)
            {

                    this->borrowedbook[isbn]--;
                    this->currentborrow--;
                    if(borrowedbook[isbn]==0)
                    {
                        borrowedbook.erase(isbn);
                    }
                    return true;
            }
            cout<<"Invalid request! Book not borrowed"<<endl;
            return false;
        }

        void printdetails()
        {
            auto it=this->borrowedbook.begin();
            while(it!=this->borrowedbook.end() && it->second > 0)
            {
                cout<<this->memberid<<' '<<this->name<<' '<<it->first<<' '<<it->second<<endl;
                it++;
            }
        }

    };


    class Library
    {
        private:
        vector <Book> listofbooks;
        //map  <string,Book> lbooks;  //for O(1) finding
        vector <Member> regmembers;
    // map <string,Member> rmem;  //for O(1) finding
        public:


        bool addBook( Book &b)
        {
            auto it=listofbooks.begin();
            while(it!=listofbooks.end())
            {
                if(it->getisbn()==b.getisbn())
            { 
                cout<<"Invalid request! Book with same isbn already exists"<<endl;
                return false;
            }
            it++;
            }
            listofbooks.push_back(b);
        // lbooks[b.getisbn()]=b;
            return true;
            
        } 

        bool registermember(Member &m)
        {
            auto it=regmembers.begin();
            while(it!=regmembers.end())
            {
                if(it->getmember()==m.getmember())
            { 
                cout<<"Invalid request! Member with same id already exists"<<endl;  //needs to be fixed, debugging done
                return false;
            }
            it++;
            }
            regmembers.push_back(m);
        // lbooks[b.getisbn()]=b;
            return true;

        }


        bool borrowBook(string memberid,string isbn)
        {
            auto it=listofbooks.begin();
            for(;it!=listofbooks.end();it++)
            {
                if(it->getisbn()==isbn)
                break;
            }
            auto gt=regmembers.begin();
            for(;gt!=regmembers.end();gt++)
            {
                if(gt->getmember()==memberid)
                
                    break;
                
            }
            if(it->borrowbook())
            {
                if(gt->bookborrow(isbn))
                {
                    return true;
                }
                it->returnbook();
            }
           
            return false;
        }

        bool returnBook(string memberid,string tisbn)
        {
            auto it=listofbooks.begin();
            for(;it!=listofbooks.end();it++)
            {
                if(it->getisbn()==tisbn)
                break;
            }
            auto gt=regmembers.begin();
            for(;gt!=regmembers.end();gt++)
            {
                if(gt->getmember()==memberid)
                {
                    break;
                }
            }
            if(it->returnbook())
            {
                if(gt->returnbook(tisbn))
                {
                    return true;
                }
                else
                {
                    it->borrowbook();
                }
            }
            return false;
        }    
        

        void printlibrarydetails()
        {
            auto it=listofbooks.begin();
            while(it!=listofbooks.end())
            {
                cout<<it->booktitle<<' '<<it->author<<' '<<it->getcopiesavailable()<<endl;
                it++;
            }
            auto gt=regmembers.begin();
            while(gt!=regmembers.end())
            {
                cout<<gt->getmember()<<' '<<gt->getname()<<endl;
                gt++;
            }
        }

    Book* findBook(const std::string &isbn)
    {
        for (auto &book : listofbooks) // Iterate over books
        {
            if (book.getisbn() == isbn) 
            {
                return &book; // Return pointer to the found book
            }
        }
        return nullptr; // Return nullptr if no book is found
    }

    Member* findMember(const std::string &memberId)
    {
        for (auto &member : regmembers)
        {
            if (member.getmember() == memberId)
            {
                return &member; // Return pointer to the found member
            }
        }
        return nullptr; // Return nullptr if not found
    }




    };

    int main()
    {

        Library L;
        string s;
        while(true)
        {
            cin>>s;
            if(s=="Book")
            {
                string t;
                cin>>t;
                if(t=="None")
                {
                        Book b1=Book();
                        L.addBook(b1);
                }   
                else if(t=="ExistingBook")
                {
                    string s1,s2;
                    cin>>s1>>s2;
                    //auto it=L.
                    Book *b1=L.findBook(s1);
                    Book b2=Book(*b1,s2);
                    L.addBook(b2);
                }
                else
                {
                    string a,b;
                    int c,d;
                    cin>>a>>b>>c>>d;
                    Book x(t,a,b,c,d);
                    L.addBook(x);
                }
            }
            else if(s=="UpdateCopiesCount")
            {
                string a;
                int b;
                cin>>a>>b;
                Book *b1=L.findBook(a);
                (b1)->updatecopies(b);
                
                
            }
        else if(s=="Member")
        {
                string t;
                cin>>t;
                if(t=="NoBorrowLimit")
                {
                    string s,p;
                    cin>>s>>p;
                    Member a=Member(s,p);
                    L.registermember(a);
                }
                else
                {
                    string n;
                    int g;
                    cin>>n>>g;
                    Member a=Member(t,n,g);
                    L.registermember(a);
                }

        }
        else if(s=="Borrow")
        {
            string s,p;
            cin>>s>>p;
        // Member *x=L.findMember(s);
            //x->bookborrow(p);       
            L.borrowBook(s,p);

        }
        else if(s=="Return")
        {
            string s,p;
            cin>>s>>p;
        //  Member *x=L.findMember(s);
        // x->returnbook(p);    
        L.returnBook(s,p);
        }
        else if(s=="PrintBook")
        {
            string isbn;
            cin>>isbn;
            Book *b1=L.findBook(isbn);
            b1->printdetails();
        }
        else if(s=="PrintMember")
        {
            string memberid;
            cin>>memberid;
            Member *m1=L.findMember(memberid);
            m1->printdetails();
        }
        else if(s=="PrintLibrary")
        {
            L.printlibrarydetails();
        }
        else
        {
            break;
        }

    }
    }