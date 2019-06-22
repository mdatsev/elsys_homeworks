#include <iostream>
using namespace std;

class Rational
{
  public:
    Rational(int num, int den)
        : numerator_(num), denominator_(den)
    {
        simplify();
    }
    Rational() {}
    friend istream &operator>>(istream &stream, Rational &r)
    {
        char c;
        stream >> c >> r.numerator_ >> c >> r.denominator_ >> c;
        return stream;
    }
    friend ostream &operator<<(ostream &stream, Rational &r)
    {
        if (r.denominator_ < 0)
        {
            r.numerator_ *= -1;
            r.denominator_ *= -1;
        }
        stream << '(' << r.numerator_ << '/' << r.denominator_ << ')' << '\n';
        return stream;
    }

    friend Rational operator+(const Rational &r1, const Rational &r2)
    {
        Rational result(r1);
        Rational temp(r2);
        int toadd = temp.numerator_ * result.denominator_;
        result.numerator_ *= temp.denominator_;
        result.denominator_ *= temp.denominator_;
        result.numerator_ += toadd;
        result.simplify();
        return result;
    }

    friend Rational operator-(const Rational &r1, const Rational &r2)
    {
        return Rational(r1) + Rational(-r2.numerator_, r2.denominator_);
    }

    friend Rational operator*(const Rational &r1, const Rational &r2)
    {
        Rational result(r1);
        result.numerator_ *= r2.numerator_;
        result.denominator_ *= r2.denominator_;
        result.simplify();
        return result;
    }

    friend Rational operator/(const Rational &r1, const Rational &r2)
    {
        return Rational(r1) * Rational(r2.denominator_, r2.numerator_);
    }

  private:
    int numerator_, denominator_;
    void simplify()
    {
        int gcd_ = gcd(numerator_, denominator_);
        numerator_ /= gcd_;
        denominator_ /= gcd_;
    }
    int gcd(int a, int b)
    {
        while (a != 0 && b != 0) // until either one of them is 0
        {
            int c = b;
            b = a % b;
            a = c;
        }
        return a + b; // either one is 0, so return the non-zero value
    }
};

int main()
{
    while (1)
    {
        cout << "> ";
        char ch;
        cin >> ch;
        if (ch == 'q')
            break;
        else
            cin.putback(ch);
        Rational result;
        cin >> result;
        while (1)
        {
            cin >> ch;
            if (ch == '=')
            {
                cout << result;
                break;
            }
            Rational next;
            cin >> next;
            if (ch == '+')
                result = result + next;
            else if (ch == '-')
                result = result - next;
            else if (ch == '*')
                result = result * next;
            else if (ch == '/')
                result = result / next;
        }
    }
}