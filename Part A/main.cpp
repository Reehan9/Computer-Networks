#include <iostream>
#include <cmath>
using namespace std;
int compute(int a, int m, int n)
{
    int res = pow(a,m);
    res = fmod(res,n);
    return res;
}
int main()
{   int p,g;
    cout<<"Enter a prime number and alpha value:"<<endl;
    cin>>p>>g;
    int a, b;
    int A, B;
    a = rand();
    cout<<"The random number chosen by A is:"<<a<<endl;
    A = compute(g, a, p);
    b = rand();
    cout<<"The random number chosen by B is:"<<b<<endl;
    B = compute(g, b, p);
    printf("Yb=%d\n",B);
    int keyA = compute(B, a, p);
    int keyB = compute(A, b, p);
    cout<<"The key of A is "<<keyA<<endl;
    cout<<"The key of B is "<<keyB<<endl;
    return 0;
}