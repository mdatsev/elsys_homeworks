#include <iostream>
using namespace std;

class Rational
{
  public:
    Rational(const int numerator = 0, const int denominator = 1)
        : num_(numerator), den_(denominator)
    {
        if (denominator == 0)
            throw "Can't divide by 0";
        simplify();
    }
    long get_numerator() const
    {
        return num_;
    }
    long get_denominator() const
    {
        return den_;
    }
    Rational &add(const Rational &r)
    {
        long lcm_ = lcm(den_, r.den_);
        expand(lcm_ / den_);
        num_ += r.expanded(lcm_ / r.den_).num_;
        return simplify();
    }
    Rational &sub(const Rational &r)
    {
        return add(-r);
    }
    Rational operator-() const
    {
        return Rational(-num_, den_);
    }
    Rational &operator+=(const Rational &r)
    {
        return add(r);
    }
    Rational &operator-=(const Rational &r)
    {
        return sub(r);
    }
    Rational &mul(const Rational &r)
    {
        num_ *= r.num_;
        den_ *= r.den_;
        return simplify();
    }
    Rational &div(const Rational &r)
    {
        return mul(Rational(r.den_, r.num_));
    }
    Rational &operator*=(const Rational &r)
    {
        return mul(r);
    }
    Rational &operator/=(const Rational &r)
    {
        return div(r);
    }

    friend istream &operator>>(istream &stream, Rational &r)
    {
        char p1, // '('
            d,   // '/'
            p2;  // ')'
        int num, den;
        stream >> p1 >> num >> d >> den >> p2;
        if (p1 != '(' || d != '/' || p2 != ')' || !cin.good())
            throw "Invalid format";
        if (den == 0)
            throw "Can't divide by 0";
        r.num_ = num;
        r.den_ = den;
        return stream;
    }
    friend ostream &operator<<(ostream &stream, Rational &r)
    {
        stream << '(' << r.num_ << '/' << r.den_ << ')' << '\n';
        return stream;
    }

  private:
    long num_, den_;
    Rational &simplify()
    {
        long gcd_ = gcd(num_, den_);
        num_ /= gcd_;
        den_ /= gcd_;
        if (den_ < 0)
            expand(-1);
        return *this;
    }
    long gcd(long a, long b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    long lcm(long a, long b)
    {
        return (a * b) / gcd(a, b);
    }
    void expand(long number)
    {
        den_ *= number;
        num_ *= number;
    }
    Rational expanded(long number) const
    {
        Rational result = *this;
        result.expand(number);
        return result;
    }
};

Rational operator+(const Rational &r1, const Rational &r2)
{
    return Rational(r1).add(r2);
}

Rational operator-(const Rational &r1, const Rational &r2)
{
    return Rational(r1).sub(r2);
}

Rational operator*(const Rational &r1, const Rational &r2)
{
    return Rational(r1).mul(r2);
}

Rational operator/(const Rational &r1, const Rational &r2)
{
    return Rational(r1).div(r2);
}

int main()
{
    while (1)
    {
        cout << "> ";
        char c;
        cin >> c;
        if (c == 'q')
            break;
        else
            cin.putback(c);
        Rational result;
        cin >> result;
        while (1)
        {
            char op;
            cin >> op;
            if (op == '=')
            {
                cout << result;
                break;
            }
            Rational next;
            cin >> next;
            switch (op)
            {
            case '+':
                result += next;
                break;
            case '-':
                result -= next;
                break;
            case '*':
                result *= next;
                break;
            case '/':
                result /= next;
                break;
            }
        }
    }
}