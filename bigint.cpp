// Program to store 1024bit number and doing basic operations like addition, subtraction and multiplication on them.
// By sgrmshrsm7

#include <iostream>
#include <string.h>

#define MAXDIGIT 310
#define RESULTDIGIT 620

using namespace std;

void reversestring(char s[])
{
        int l = strlen(s), i;
        char temp;
        for(i = 0 ; i < l / 2 ; ++i)
        {
                temp = s[i];
                s[i] = s[l - i - 1];
                s[l - i - 1] = temp;
        }
}

void removeminus(char s[])
{
        int l = strlen(s) - 1, i;
        for(i = 0 ; i < l ; ++i)
                s[i] = s[i + 1];
        s[i] = '\0';
}

void addminus(char s[])
{
        int l = strlen(s), i;
        for(i = l ; i > 0 ; --i)
                s[i] = s[i - 1];
        s[l + 1] = '\0';
        s[0] = '-';
}

void addinteger(char a[], char b[], char r[])
{
        reversestring(a);
        reversestring(b);
        int l1 = strlen(a), l2 = strlen(b), i, m, carry = 0, t;
        m = max(l1, l2);
        for(i = 0 ; i < m ; ++i)
        {
                t = carry;
                if(i < l1)
                        t = t + a[i] - '0';
                if(i < l2)
                        t = t + b[i] - '0';
                r[i] = '0' + (t % 10);
                carry = t / 10;
        }
        if(carry != 0)
        {
                r[i] = carry + '0';
                r[i + 1] = '\0';
        }
        else r[i] = '\0';
        reversestring(r);
}

void subtractinteger(char a[], char b[], char r[])
{
        int l1 = strlen(a), l2 = strlen(b), i, carry = 0, t, greaternum = 1;
        if(l1 < l2)
                greaternum = 2;
        else if(l1 == l2)
        {
                i = 0;
                while(i < l1 && a[i] == b[i])
                        ++i;
                if(i < l1 && a[i] < b[i])
                        greaternum = 2;
        }
        reversestring(a);
        reversestring(b);
        if(greaternum == 2)
                swap(a, b);
        l1 = strlen(a);
        l2 = strlen(b);
        for(i = 0 ; i < l1 ; ++i)
        {
                t = carry + a[i] - '0';
                if(i < l2)
                        t = t - b[i] + '0';
                if(t < 0)
                {
                        r[i] = '0' + t + 10;
                        carry = -1;
                }
                else
                {
                        r[i] = '0' + t;
                        carry = 0;
                }
        }
        if(greaternum == 2)
        {
                swap(a, b);
                r[i] = '-';
                r[i + 1] = '\0';
        }
        else r[i] = '\0';
        reversestring(r);
}

void multiplyinteger(char a[], char b[], char r[])
{
        int l1 = strlen(a), l2 = strlen(b), i, j, k, carry, t;
        reversestring(a);
        reversestring(b);
        char temp[RESULTDIGIT];
        strcpy(r, "0");
        for(j = 0 ; j < l2 ; j++)
        {
                carry = 0;
                for(i = 0 ; i < l1 ; i++)
                {
                        t = (a[i] - '0') * (b[j] - '0') + carry;
                        temp[i] = (t % 10) + '0';
                        carry = t / 10;
                }
                if(carry != 0)
                {
                        temp[i] = carry + '0';
                        ++i;
                }
                temp[i] = '\0';
                reversestring(temp);
                for(k = 0 ; k < j ; k++)
                {
                        temp[i] = '0';
                        ++i;
                }
                temp[i] = '\0';
                addinteger(temp, r, r);
        }
}

int main()
{
        char num1[MAXDIGIT], num2[MAXDIGIT], result[RESULTDIGIT];
        int choice;
        char c = 'y';
        while(c == 'y')
        {
                cout << "Enter first number : ";
                cin >> num1;
                cout << "Enter second number : ";
                cin >> num2;
                cout << "Press 1 for addition\nPress 2 for subtraction\nPress 3 for multiplication\nEnter choice : ";
                cin >> choice;
                switch (choice)
                {
                        case 1: cout << "(" << num1 << ") + (" << num2 << ") = ";
                                if(num1[0] == '-' && num2[0] == '-')
                                {
                                        removeminus(num1);
                                        removeminus(num2);
                                        addinteger(num1, num2, result);
                                        addminus(result);
                                }
                                else if(num1[0] == '-')
                                {
                                        removeminus(num1);
                                        subtractinteger(num2, num1, result);
                                }
                                else if(num2[0] == '-')
                                {
                                        removeminus(num2);
                                        subtractinteger(num1, num2, result);
                                }
                                else
                                        addinteger(num1, num2, result);
                                cout << result;
                                break;
                        case 2: cout << "(" << num1 << ") - (" << num2 << ") = ";
                                if(num1[0] == '-' && num2[0] == '-')
                                {
                                        removeminus(num1);
                                        removeminus(num2);
                                        subtractinteger(num2, num1, result);
                                }
                                else if(num1[0] == '-')
                                {
                                        removeminus(num1);
                                        addinteger(num2, num1, result);
                                        addminus(result);
                                }
                                else if(num2[0] == '-')
                                {
                                        removeminus(num2);
                                        addinteger(num1, num2, result);
                                }
                                else
                                        subtractinteger(num1, num2, result);
                                cout << result;
                                break;
                        case 3: cout << "(" << num1 << ") * (" << num2 << ") = ";
                                if(num1[0] == '-' && num2[0] == '-')
                                {
                                        removeminus(num1);
                                        removeminus(num2);
                                        multiplyinteger(num1, num2, result);
                                }
                                else if(num1[0] == '-')
                                {
                                        removeminus(num1);
                                        multiplyinteger(num1, num2, result);
                                        addminus(result);
                                }
                                else if(num2[0] == '-')
                                {
                                        removeminus(num2);
                                        multiplyinteger(num1, num2, result);
                                        addminus(result);
                                }
                                else
                                        multiplyinteger(num1, num2, result);
                                cout << result;
                                break;
                        default: cout << "Invalid choice!";
                }
                cout << "\nEnter y to continue : ";
                cin >> c;
        }
        return 0;
}
