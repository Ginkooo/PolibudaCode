#include <iostream>
#include <iomanip>

using namespace std;


float zadanie1(float a, float b, float eps)
{
    int i = 0;
    float temp = a;
    while (temp<=b)
    {
        temp += eps;
        i++;
    }

    int n = i;

    float as[n];
    float bs[n];
    temp = a;
    i = 0;
    while(temp < b)
    {
        as[i] = temp;
        temp+=eps;
        if (temp <= b)
            temp = b;
        bs[i]=temp;
    }

    for (i = 0; i<n; i++)
    {
        cout << "a["<<i<<"] = " << as[i] << endl;
        cout << "b["<<i<<"] = " << bs[i] << endl;
    }
}

int main()
{
    float wynik = zadanie1(1, 7, 0.5);  
}
