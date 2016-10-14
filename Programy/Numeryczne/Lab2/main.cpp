#include <iostream>

using namespace std;

float lagrange(float x[], float y[], float arg)
{
    int pointsCount = sizeof(x) / sizeof(*x);
    float il;
    float ret = 0;
    for (int i = 0; i < pointsCount; i++)
    {
        il = 1;
        for (int j = 0; j < pointsCount; j++)
        {
            if (j != i)
            {
                il*=((arg-x[j])/(x[i]-x[j]));
            }
        }

        ret += il*y[i];
    }

    return ret;

}

int main()
{
    float x[] = { 1, 3, 4, 6 };
    float y[] = { -1, -9, 13, -59 };
    float pkt;
    cout << "Podaj punkt, w którym chcesz wyliczyć przybliżoną wartość funkcji: ";
    cin >> pkt;

    cout << "Przybliżona wartość wynosi: " << lagrange(x, y, pkt);

}
