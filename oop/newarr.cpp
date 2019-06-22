#include <cstdlib>
#include <iostream>
using namespace std;

class Foo
{
    int bar_;

  public:
    Foo() : bar_(6)
    {
        cout << "init" << endl;
    }
    Foo(int b, int c) : bar_(b + c)
    {
        cout << "init" << endl;
    }
    int get_bar()
    {
        return bar_;
    }
};

int main()
{
    Foo *ptr = new Foo();
    Foo *arr = new Foo[3]{{2, 3}, {3, 3}, {4, 3}};
    cout << arr[0].get_bar() << endl;
    cout << arr[1].get_bar() << endl;
    cout << arr[2].get_bar() << endl;
    delete ptr;
    return 0;
}