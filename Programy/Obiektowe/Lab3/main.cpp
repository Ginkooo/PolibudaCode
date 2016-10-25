#include <iostream>

using namespace std;

float newtonuj(int n, float x, float* xs, float* ys)
{
    float tab2D[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 2; j<n; j++)
            tab2D[i][j] = 0;
    }

    float suma = ys[0];

    for (int i = 0; i < n; i++)
    {
        tab2D[i][0] = xs[i];
        tab2D[i][1] = ys[i];
    }

    for (int i = 0; i < n - (i+1); i++)
    {
        for (int j = 2; j<n-1; j++)
        {
            tab2D[]
        }
    }


    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j<n; j++)
            cout << tab2D[i][j] << " ";
    }
}



int main()
{
    float ys[] = { 1, 0, -1, 0 };
    float xs[] = {-1, 0, 4, 5 };
    float x = 4;
    int n = 4;

    int wynik = newtonuj(n, x, xs, ys);
}
