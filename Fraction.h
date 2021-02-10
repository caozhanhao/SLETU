#ifndef FRACTION_H
#define FRACTION_H
#include<iostream>
struct Fraction 
{
    friend std::ostream &operator<<(std::ostream &os,const Fraction &item);
    friend std::istream &operator>>(std::istream &is,Fraction &item);
    friend bool operator==(const Fraction &item1,const Fraction &item2);
    friend bool operator!=(const Fraction &item1,const Fraction &item2);
    friend Fraction operator+(const Fraction &item1,const Fraction &item2);
    friend Fraction operator-(const Fraction &item1,const Fraction &item2);
    friend Fraction operator*(const Fraction &item1,const Fraction &item2);
    friend Fraction operator/(const Fraction &item1,const Fraction &item2);
    friend void rfcd(Fraction &item1,Fraction &item2);

    int numerator;
    int denominator;
    
    Fraction &operator=(const Fraction &item)
    {
        numerator = item.numerator;
        denominator = item.denominator;
        return *this;
    }
    bool is_positive() const
    {
        return (denominator > 0 && numerator > 0) || (denominator < 0 && numerator < 0);
    }
    Fraction reciprocal()
    {
        std::swap(numerator,denominator);
        return *this;
    }
    Fraction reduction()
    {
        int smaller = std::min(abs(numerator),abs(denominator));
        for(int i = 2;i <= smaller;i++)
        {
            if(numerator % i == 0 && denominator % i == 0)
            {
                numerator /= i;
                denominator /= i;
                i--;
            }
        }
        return *this;
    }
    Fraction opposite()
    {
        numerator = -numerator;
        return *this;
    }
};
std::ostream &operator<<(std::ostream &os,const Fraction &item)
{
    if(item.numerator == 0)
        os << "0";
    else
    {
        if(!item.is_positive())
            os << "-";
        if(item.denominator == 1 || item.denominator == -1)
            os << abs(item.numerator);
        else
            os << abs(item.numerator) << "/" << abs(item.denominator);
    }
    return os;
}
std::istream &operator>>(std::istream &is,Fraction &item)
{
    int numerator,denominator;
    is >> numerator >> denominator;
    if(is)
    {
        item.numerator = numerator;
        item.denominator = denominator;
    }
    else 
        item = Fraction();
    return is;
}
bool operator==(const Fraction &item1,const Fraction &item2)
{
    return item1.numerator == item2.numerator && 
           item1.denominator == item2.denominator;
}
bool operator!=(const Fraction &item1,const Fraction &item2)
{
    return !(item1 == item2);
}
Fraction operator+(const Fraction &item1,const Fraction &item2)
{
    Fraction result;
    if(item1.denominator == item2.denominator)
    {
        result.denominator = item1.denominator;
        result.numerator = item1.numerator + item2.numerator;
        result.reduction();
        return result;
    }
    else
    {
        Fraction temp1 = item1;
        Fraction temp2 = item2;
        rfcd(temp1,temp2);
        result.denominator = temp1.denominator;
        result.numerator = temp1.numerator + temp2.numerator;
        result.reduction();
        return result;
    }
}
Fraction operator-(const Fraction &item1,const Fraction &item2)
{
    Fraction opposite = item2;
    opposite.opposite();
    return (item1 + opposite);
}
Fraction operator*(const Fraction &item1,const Fraction &item2)
{
    Fraction result;
    result.numerator = item1.numerator * item2.numerator;
    result.denominator = item1.denominator * item2.denominator;
    result.reduction();
    return result;
}
Fraction operator/(const Fraction &item1,const Fraction &item2)
{
    Fraction reciprocal = item2;
    reciprocal.reciprocal();
    return (item1 * reciprocal);
}
void rfcd(Fraction &item1,Fraction &item2)  //reduction of fractions to a common denominator
{
    int smaller = std::min(abs(item1.denominator),abs(item2.denominator));
    for(int i = smaller;i <= abs(item1.denominator * item2.denominator);i++)
    {
        if(i % item1.denominator == 0 && i % item2.denominator == 0)
        {
            item1.numerator *= (i / item1.denominator);
            item2.numerator *= (i / item2.denominator);
            item1.denominator = item2.denominator = i;
            break;
        }
    }
}
Fraction to_Fraction(std::string s)
{
    int i = s.find("/");
    Fraction f;
    if(i != -1)
    {
        std::string num = s.substr(0,i);
        std::string den = s.substr(i + 1,s.size() - i);
        f = {stoi(num),stoi(den)};
    }
    else
        f = {stoi(s),1};
    return f;
}
Fraction to_Fraction(int i)
{
    return {i,1};
}
#endif

