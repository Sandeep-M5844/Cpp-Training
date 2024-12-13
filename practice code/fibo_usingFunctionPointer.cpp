//Fiboonocii series using call back function pointer



// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;


void fibo(int n)
{
    int a = 0;
    int b = 1;
    int c = a + b;
    if (n == 1)
    {
        cout << "1";
    }
    else if (n == 0) { cout << "0"; }
    int count = 2;
    cout << a << " " << b;
    while (count <= n)
    {
        c = a + b;
        a = b;
        b = c;
        cout << " " << c;
        count++;

    }

}
void fib(int n, void (*fun_fabb)(int))
{
    fun_fabb(n);
}
int main()
{
    fib(10, fibo);
    return 0;
}