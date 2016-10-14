#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


int sign(float arg)
{
    if (arg == 0) return 0;
    if (arg < 0) return -1;
    if (arg > 0) return 1;
}

void zadanie1()
{
    float a = 1e-16;
    float b = 10;
    float c = 1;
    float x1, x2;
    float delta = b*b-4*a*c;
    if (delta < 0)
    {
        cout << "Nie ma miejsc zerowych" << endl;
        return;
    }
    else if (delta == 0)
    {
        x1 = x2 = -b/(2*a);
    }
    else
    {
        x1 = (-b-sqrt(delta))/(2*a);
        x2 = (-b+sqrt(delta))/(2*a);
    }

    cout << "x1 = " << x1 << ", x2 = " << x2 << endl;

}


void zadanie2()
{


    float a = 1e-16;
    float b = 10;
    float c = 1;
    float x1, x2;
    float delta = b*b-4*a*c;
    x1 = -b/(2*a)+sign(-b/(2*a))*sqrt(pow(b/(2*a), 2) - c/a);
    x2 = c/(a*x1);

    cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
}


float zadanie3a(int n)
{
    if (n == 0) return 0.182321556;
    return (float)1/n-5*zadanie3a(n-1);
}

float zadanie3b(int n)
{
    if (n == 16) return 0.0098;
    return (float)1/(5*n)-(float)1/5*zadanie3b(n+1);
}



int main()
{
    cout << setprecision(8);
    zadanie1();
    cout << endl;
    zadanie2();
    cout << endl;
    for (int n = 0; n <= 16; n++)
    {
        cout << zadanie3a(n) << endl;
    }
    cout << endl << endl;

    for (int n = 1; n <= 16; n++)
    {
        cout << zadanie3b(n) << endl;
    }
}
