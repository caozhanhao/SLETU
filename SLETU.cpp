// SLETU : System of linear equations in two unknowns (二元一次方程组)
// author : caozhanhao

#include <iostream>
#include <array>
#include "Fraction.h"
using namespace std;
array<Fraction,3> cut(string e)
{
    Fraction a,b,c;
    int c1 = e.find("x");
    int c2 = e.find("y");
    if(e[0] == 'x' || e[c1 - 1] == '1' || e[c1 - 1] == '+' || e[c1 - 1] == '-')
    {
        if(e[0] == 'x' || e[c1 - 1] == '1' || e[c1 - 1] == '+')
            a = {1,1};
        else{
                if(e[c1 - 1] == '-')
                    a = {-1,1};
            }
    }
    else
    {
        string s_a = e.substr(0,c1);
        a = to_Fraction(s_a);
    }
    if(e[c2 - 1] == '+' || e[c2 - 1] == '1' || e[c2 - 1] == '-')
    {
        if(e[c2 - 1] == '+' || e[c2 - 1] == '1')
            b = {1,1}; 
        else
        {
            if(e[c2 - 1] == '-')
                b = {-1,1};
        }
    }
    else
    {
        string s_b = e.substr(c1 + 2,c2 - c1 - 2);
        b = to_Fraction(s_b);
        if(e[c1 + 1] == '-')
            b.opposite();
    }
    string s_c = e.substr(c2 + 2,e.size() - c2 - 1);
    c = to_Fraction(s_c);
    return {a,b,c};
}
array<Fraction,6> get_num(string e1,string e2)
{
    array<Fraction,6> num;
    array<Fraction,3> e1_a = cut(e1);
    array<Fraction,3> e2_a = cut(e2);
    num[0] = e1_a[0];
    num[1] = e1_a[1];
    num[2] = e1_a[2];
    num[3] = e2_a[0];
    num[4] = e2_a[1];
    num[5] = e2_a[2];
    return num;
}
array<Fraction,2> sletu(array<Fraction,6> num)
{
    Fraction m = num[3] / num[0];
    Fraction i = num[4] - m * num[1]; 
    Fraction j = num[5] - m * num[2];
    Fraction y = j / i;
    Fraction x = (num[2] - num[1] * y )/ num[0];
    return {x,y}; 
}
int main()
{
    string e1,e2;
    cout << "请输入形如 ax + by = c 的两个方程" << endl;
    cout << "方程1: ";
    getline(cin,e1);
    cout << "方程2: ";
    getline(cin,e2);
    array<Fraction,2> result = sletu(get_num(e1,e2));
    cout << result[0] << endl << result[1] << endl;
}


