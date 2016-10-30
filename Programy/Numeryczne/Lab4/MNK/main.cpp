#include <iostream>
#include <iomanip>

#define DEBUG 0

using namespace std;

void mnk(int n, float xs[], float ys[])
{

    /*Tablica zawierająca n równań dla 0 i 1 rzędu, trzeci wymiar tablicy
     *Zawiera współczynniki przy elementach wyraz wolny, a0 i a1 (których wartość na końcu trzeba wyliczyć*/
    float tab3D[2][n][3];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                tab3D[j][i][k] = -1;
            }
        }
    }


    for (int j = 0; j < n; j++)
    {
        tab3D[0][j][0] = ys[j];
        tab3D[0][j][1] = 1.0;
        tab3D[0][j][2] = xs[j];

        tab3D[1][j][0] = ys[j] * xs[j];
        tab3D[1][j][1] = 1.0 * xs[j];
        tab3D[1][j][2] = xs[j] * xs[j];
    }



#if DEBUG

    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << xs[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << ys[i] << " ";
    }


    for (int i = 0; i < 2; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << " ";
            for (int k = 0; k < 3; k++)
            {
                cout << tab3D[i][j][k] << "/";
            }
        }
    }
#endif // DEBUG

    float sum_ww_0, sum_ww_1, sum_a0_0, sum_a0_1, sum_a1_0, sum_a1_1;
    sum_ww_0 = sum_a0_0 = sum_a0_1 = sum_a1_0 = sum_a1_1 = sum_ww_1 = 0;



    for (int j = 0; j < n; j++)
    {
        sum_ww_0 += tab3D[0][j][0];
        sum_ww_1 += tab3D[1][j][0];
        sum_a0_0 += tab3D[0][j][1];
        sum_a0_1 += tab3D[1][j][1];
        sum_a1_0 += tab3D[0][j][2];
        sum_a1_1 += tab3D[1][j][2];
    }
#if DEBUG
    cout << endl << sum_a0_0 << " " << sum_a1_0 << " " << sum_ww_0 << endl;
    cout << sum_a0_1 << " " << sum_a1_1 << " " << sum_ww_1;
#endif // DEBUG

    //Układ Cramera
    /*
    suma00(a) suma10(b) sumww0(e)
    suma01(c) suma11(d) sumww1(f)
    */

    float e = sum_ww_0;
    float f = sum_ww_1;
    float a = sum_a0_0;
    float b = sum_a1_0;
    float c = sum_a0_1;
    float d = sum_a1_1;

    float det = sum_a0_0 * sum_a1_1 - sum_a1_0 * sum_a0_1;
    if (det != 0)
    {
        float a0 = (e * d - b * f) / det;
        float a1 = (a * f - e * c) / det;
        cout << "a0 = " << a0 << endl;
        cout << "a2 = " << a1 << endl;
    }
    else
    {
        cout << "Wyznacznik nie istnieje. Brak rozwiazan, lub wiele rozwiazan" << endl;
    }


}


bool x_nie_powtarzaja_sie(int n, float xs[])
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (xs[i] == xs[j])
                return false;
    return true;
}


bool poprawne(int n, float xs[], float ys[])
{
    if (x_nie_powtarzaja_sie(n, xs))
        return true;
    return false;
}





int main()
{
#if DEBUG
    int n = 5;
    float xs[] = {1, 2, 3, 4 ,5};
    float ys[] = {11, 12, 13, 14, 15};
#elif !DEBUG
    int n;
    cout << "Podaj ilosc punktow: ";
    cin >> n;
    float xs[n];
    float ys[n];
    for (int i = 0; i < n; i++)
    {
        cout << "x[" << i << "] = ";
        cin >> xs[i];
            cout << "y[" << i << "] = ";
        cin >> ys[i];
    }
#endif // DEBUG

    cout << endl;
    if (poprawne(n, xs, ys))
        mnk(n, xs, ys);
    else
        cout << "Wprowadzone dane sa niepoprawne dla tej metody" << endl;
}
