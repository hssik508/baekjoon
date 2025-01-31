#include <iostream>
#include <math.h>

using namespace std;

int fib[41]={0};

int main()
{
    int n;
    cin>>n;
    fib[0]=1;
    fib[1]=1;
    for (int i=2; i<=40; i++)
    {
        fib[i]=fib[i-1]+fib[i-2];
    }
    cout<<fib[n];
    return 0;
}