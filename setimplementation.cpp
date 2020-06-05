// Program to implement a set data structure(containing string data) using a hash table.

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;

int randnum;

int logbase2(int n)
{
        int i = 1, j = 2;
        while(n > j)
        {
                j *= 2;
                ++i;
        }
        return i;
}

int hashfunction(string x)
{
        int k = randnum, l = x.length();
        for(int i = 0 ; i < l ; ++i)
                k = ((k << 5) + k) + x[i];
        return k;
}

class StaticSet
{
        public :
        int size, filled;
        string *hashtable;

        StaticSet()
        {
                hashtable = NULL;
        }

        int myhash(string k, int i)
        {
                return abs((hashfunction(k) + i) % size);
        
        }

        void insertintoset(string i)
        {
                int j = 0;
                while (hashtable[myhash(i, j)] != "NULL" && hashtable[myhash(i, j)] != "ImDeleted")
                        j += 1;
                hashtable[abs(myhash(i, j))] = i;
                filled += 1;
        }

        void printtable()
        {
                cout << "\nTable : {";
                if(hashtable[0] != "NULL")
                        cout << "\"" << hashtable[0] << "\"";
                else
                        cout << hashtable[0];
                for(int i = 1 ; i < size ; ++i)
                {
                        cout << ", ";
                        if(hashtable[i] != "NULL")
                                cout << "\"" << hashtable[i] << "\"";
                        else
                                cout << hashtable[i];
                }
                cout << "}";
        }

        void printset()
        {
                if(filled != 0)
                {
                        cout << "\nSet   : {";
                        int i = 0;
                        while(hashtable[i] == "NULL" || hashtable[i] == "ImDeleted")
                                ++i;
                        cout << "\"" << hashtable[i] << "\"";
                        ++i;
                        while(i < size)
                        {
                                if(hashtable[i] != "NULL" && hashtable[i] != "ImDeleted")
                                        cout << ", \"" << hashtable[i] << "\"";
                                ++i;
                        }
                        cout << "}";
                }
                else
                        cout << endl << "Empty Set";
        }

        int iselementof(string x)
        {
                int j = 0;
                while (j < size && hashtable[myhash(x, j)] != "NULL" && hashtable[myhash(x, j)] != x)
                        j += 1;
                if (j < size && hashtable[myhash(x, j)] == x)
                        return myhash(x,j);
                else
                        return -1;
        }

        void is_empty()
        {
                if(filled == 0)
                        cout << endl << "Set is empty";
                else
                        cout << endl << "Set is not empty";
        }

        int cardinality()
        {
                return filled;
        }

        string *enumerate()
        {
                string *temp;
                temp = new string[filled];
                int i, j = 0;
                for(i = 0 ; i < size ; ++i)
                        if(hashtable[i] != "NULL" && hashtable[i] != "ImDeleted")
                        {        
                                temp[j] = hashtable[i];
                                ++j;
                        }
                return temp;
        }

        void build(string *x, int s)
        {
                size = pow(2, logbase2(s));
                filled = 0;
                if(hashtable != NULL)
                        delete[] hashtable;
                hashtable = new string[size];
                for(int i = 0 ; i < size ; ++i)
                        hashtable[i] = "NULL";
                for(int i = 0 ; i < s ; ++i)
                        if(iselementof(x[i]) == -1)
                                insertintoset(x[i]);
        }
};

class DynamicSet : public StaticSet
{
        public:
        void create()
        {
                size = 2;
                filled = 0;
                if(hashtable != NULL)
                        delete[] hashtable;
                hashtable = new string[size];
                for(int i = 0 ; i < size ; ++i)
                        hashtable[i] = "NULL";
        }

        void add(string x)
        {
                if(size == filled)
                {
                        //rehashing
                        string *old = enumerate();
                        delete[] hashtable;
                        size *= 2;
                        filled = 0;
                        hashtable = new string[size];
                        for(int i = 0 ; i < size ; ++i)
                                hashtable[i] = "NULL";
                        for(int i = 0 ; i < (size  / 2) ; ++i)
                                if(iselementof(old[i]) == -1)
                                        insertintoset(old[i]);
                }
                if(iselementof(x) == -1)
                        insertintoset(x);
        }

        void remove(string i)
        {
                int index = iselementof(i);
                cout << endl;
                if (index != -1)
                {
                        hashtable[index] = "ImDeleted";
                        filled -= 1;
                        cout << i << " deleted successfully!";
                }
                else
                        cout << i << " not found!";
        }
};

StaticSet Union(StaticSet A, StaticSet B)
{
        string *u1, *u2, *u;
        u1 = A.enumerate();
        u2 = B.enumerate();
        int n1 = A.cardinality(), n2 = 0, i, j;
        for(i = 0 ; i < B.cardinality() ; ++i)
                if(A.iselementof(u2[i]) == -1)
                        ++n2;
        u = new string[(n1 + n2)];
        for(i = 0 ; i < n1 ; ++i)
                u[i] = u1[i];
        j = i;        
        for(i = 0 ; i < B.cardinality() ; ++i)
                if(A.iselementof(u2[i]) == -1)
                {
                        u[j] = u2[i];
                        ++j;
                }
        StaticSet C;
        C.build(u, (n1 + n2));
        delete[] u1;
        delete[] u2;
        delete[] u;
        return C;
}

DynamicSet Union(DynamicSet A, DynamicSet B)
{
        DynamicSet C;
        C.create();
        string *temp;
        temp = A.enumerate();
        C.build(temp, A.cardinality());
        string *u;
        u = B.enumerate();
        for(int i = 0 ; i < B.cardinality() ; ++i)
                if(C.iselementof(u[i]) == -1)
                        C.add(u[i]);
        delete[] u;
        return C;
}

StaticSet Intersection(StaticSet A, StaticSet B)
{
        string *i, *j;
        i = A.enumerate();
        int n = 0, l, m = 0;
        for(l = 0 ; l < A.cardinality() ; ++l)
                if(B.iselementof(i[l]) != -1)
                        ++n;
        j = new string[n];
        for(l = 0 ; l < A.cardinality() ; ++l)
                if(B.iselementof(i[l]) != -1)
                {
                        j[m] = i[l];
                        ++m;
                }
        StaticSet C;
        C.build(j, n);
        delete[] j;
        return C;
}

DynamicSet Intersection(DynamicSet A, DynamicSet B)
{
        DynamicSet C;
        C.create();
        string *j;
        j = A.enumerate();
        for(int i = 0 ; i < A.cardinality() ; ++i)
                if(B.iselementof(j[i]) != -1)
                        C.add(j[i]);
        return C;
}

StaticSet Difference(StaticSet A, StaticSet B)
{
        string *i, *j;
        i = A.enumerate();
        int n = 0, l, m = 0;
        for(l = 0 ; l < A.cardinality() ; ++l)
                if(B.iselementof(i[l]) == -1)
                        ++n;
        j = new string[n];
        for(l = 0 ; l < A.cardinality() ; ++l)
                if(B.iselementof(i[l]) == -1)
                {
                        j[m] = i[l];
                        ++m;
                }
        StaticSet C;
        C.build(j, n);
        delete[] j;
        return C;
}

DynamicSet Difference(DynamicSet A, DynamicSet B)
{
        DynamicSet C;
        C.create();
        string *j;
        j = A.enumerate();
        for(int i = 0 ; i < A.cardinality() ; ++i)
                if(B.iselementof(j[i]) == -1)
                        C.add(j[i]);
        return C;
}

int Subset(StaticSet A, StaticSet B)
{
        int ss = 1;
        string *j;
        j = A.enumerate();
        for(int i = 0 ; i < A.cardinality() && ss != 0 ; ++i)
                if(B.iselementof(j[i]) == -1)
                        ss = 0;
        return ss;
}

int Subset(DynamicSet A, DynamicSet B)
{
        int ss = 1;
        string *j;
        j = A.enumerate();
        for(int i = 0 ; i < A.cardinality() && ss != 0 ; ++i)
                if(B.iselementof(j[i]) == -1)
                        ss = 0;
        return ss;
}

int main()
{
        srand(time(0));
        randnum = rand();
        int choice, dynamicorstatic = 1, i, n, c1, c2;
        string *a;
        string x;
        DynamicSet A, B, C;
        StaticSet X, Y, Z;
        while(dynamicorstatic != 0)
        {
                cout << "\nEnter 1 for dynamic set, 2 for static set, 0 to exit : ";
                cin >> dynamicorstatic;
                switch(dynamicorstatic)
                {
                        case 1: cout << "\n\n\nDynamic Set";
                                cout << "\nCreating Set1\n";
                                A.create();
                                c2 = 1;
                                while(c2)
                                {
                                        cout << "Enter value for set1 : ";
                                        cin >> x;
                                        A.add(x);
                                        cout << "Enter 1 to add more values, 0 to stop adding : ";
                                        cin >> c2;
                                }
                                c1 = 1;
                                while(c1 != 0)
                                {
                                        cout << "\n\n\nEnter 1 to check a string in the set";
                                        cout << "\nEnter 2 to check whether the set is empty";
                                        cout << "\nEnter 3 to print cardinality of the set";
                                        cout << "\nEnter 4 to print set";
                                        cout << "\nEnter 5 to add an element to set";
                                        cout << "\nEnter 6 to remove an element from set";
                                        cout << "\nEnter 7 to check operations with another set";
                                        cout << "\nEnter any other number to quit";
                                        cout << "\nEnter choice : ";
                                        cin >> c1;
                                        switch(c1)
                                        {
                                                case 1: cout << "\nEnter string to search in set : ";
                                                        cin >> x;
                                                        if(A.iselementof(x) != -1)
                                                                cout << x << " is element of the set";
                                                        else
                                                                cout << x << " is not the element of the set";
                                                        break;
                                                case 2: A.is_empty();
                                                        break;
                                                case 3: cout << "\nCardinality of set = " << A.cardinality();
                                                        break;
                                                case 4: A.printset();
                                                        break;
                                                case 5: cout << "\nEnter the element to add in the set : ";
                                                        cin >> x;
                                                        A.add(x);
                                                        break;
                                                case 6: cout << "\nEnter the element to delete from the set : ";
                                                        cin >> x;
                                                        A.remove(x);
                                                        break;
                                                case 7: cout << "\nCreating Set2\n";
                                                        B.create();
                                                        c2 = 1;
                                                        while(c2)
                                                        {
                                                                cout << "Enter value for set2 : ";
                                                                cin >> x;
                                                                B.add(x);
                                                                cout << "Enter 1 to add more values, 0 to stop adding : ";
                                                                cin >> c2;
                                                        }
                                                        cout << "\nSet 2 created!";
                                                        B.printset();
                                                        choice = 1;
                                                        while(choice)
                                                        {
                                                                cout << "\n\nEnter 1 for Union, 2 for Intersection, 3 for Difference, 4 for Subset or any other number to quit : ";
                                                                cin >> choice;
                                                                switch(choice)
                                                                {
                                                                        case 1: cout << "\n\nUnion : ";
                                                                                C = Union(A, B);
                                                                                C.printtable();
                                                                                C.printset();
                                                                                break;
                                                                        case 2: cout << "\n\nIntersection : ";
                                                                                C = Intersection(A, B);
                                                                                C.printtable();
                                                                                C.printset();
                                                                                break;
                                                                        case 3: cout << "\n\nDifference : ";
                                                                                C = Difference(A, B);
                                                                                C.printtable();
                                                                                C.printset();
                                                                                break;
                                                                        case 4: if(Subset(A, B) == 1)
                                                                                        cout << "Set1 is a subset of Set2";
                                                                                else
                                                                                        cout << "Set1 is not a subset of Set2";
                                                                                break;
                                                                        default: choice = 0;
                                                                }
                                                        }
                                                        break;
                                                default: c1 = 0;
                                        }
                                }
                                break;
                        case 2: cout << "\n\n\nStatic Set";
                                cout << "\nCreating Set1\n";
                                cout << "\nEnter number of elements in Set1 : ";
                                cin >> n;
                                a = new string[n];
                                cout <<"Enter the values : ";
                                for(i = 0 ; i < n ; ++i)
                                        cin >> a[i];
                                X.build(a, n);
                                c1 = 1;
                                while(c1 != 0)
                                {
                                        cout << "\n\n\nEnter 1 to check a string in the set";
                                        cout << "\nEnter 2 to check whether the set is empty";
                                        cout << "\nEnter 3 to print cardinality of the set";
                                        cout << "\nEnter 4 to print set";
                                        cout << "\nEnter 5 to check operations with another set";
                                        cout << "\nEnter any other number to quit";
                                        cout << "\nEnter choice : ";
                                        cin >> c1;
                                        switch(c1)
                                        {
                                                case 1: cout << "\nEnter string to search in set : ";
                                                        cin >> x;
                                                        if(X.iselementof(x) != -1)
                                                                cout << x << " is element of the set";
                                                        else
                                                                cout << x << " is not the element of the set";
                                                        break;
                                                case 2: X.is_empty();
                                                        break;
                                                case 3: cout << "\nCardinality of set = " << X.cardinality();
                                                        break;
                                                case 4: X.printset();
                                                        break;
                                                case 5: cout << "\nCreating Set2\n";
                                                        cout << "\nEnter number of elements in Set2 : ";
                                                        cin >> n;
                                                        a = new string[n];
                                                        cout <<"Enter the values : ";
                                                        for(i = 0 ; i < n ; ++i)
                                                                cin >> a[i];
                                                        Y.build(a, n);
                                                        cout << "\nSet 2 created!";
                                                        Y.printset();
                                                        choice = 1;
                                                        while(choice)
                                                        {
                                                                cout << "\n\nEnter 1 for Union, 2 for Intersection, 3 for Difference, 4 for Subset or any other number to quit : ";
                                                                cin >> choice;
                                                                switch(choice)
                                                                {
                                                                        case 1: cout << "\n\nUnion : ";
                                                                                Z = Union(X, Y);
                                                                                Z.printset();
                                                                                break;
                                                                        case 2: cout << "\n\nIntersection : ";
                                                                                Z = Intersection(X, Y);
                                                                                Z.printset();
                                                                                break;
                                                                        case 3: cout << "\n\nDifference : ";
                                                                                Z = Difference(X, Y);
                                                                                Z.printset();
                                                                                break;
                                                                        case 4: if(Subset(X, Y) == 1)
                                                                                        cout << "Set1 is a subset of Set2";
                                                                                else
                                                                                        cout << "Set1 is not a subset of Set2";
                                                                                break;
                                                                        default: choice = 0;
                                                                }
                                                        }
                                                        break;
                                                default: c1 = 0;
                                        }
                                }
                                break;
                        default: if(dynamicorstatic != 0)
                                        cout << "\nInvalid choice";
                                dynamicorstatic = 0;
                }
        }
        return 0;
}