#include <iostream>
#include <iomanip>

using namespace std;

void quicksort(float x[], float y[], int l, int p)
{
    float t=x[(l+p)/2], typ, typ1;
    int i=l, j=p, w;
    do
    {
        while(x[i]<t && i<j) i=i+1;
        while(x[j]>t && i<j) j=j-1;
        if (i<=j)
        {
            typ=x[i];
            typ1=y[i];
            x[i]=x[j];
            y[i]=y[j];
            x[j]=typ;
            y[j]=typ1;
            i++;
            j--;
        }
    }while(j>=i);
    w=i;
    if (l<j) quicksort(x, y, l, j);
    if (i<p) quicksort(x, y, w, p);
}
bool zal1(float x[], float y[], int n)
{
    int i=0, koniec=0, kon=0;
    while(kon!=1)
    {
        if(x[i]==x[i+1]) koniec=2;
        else i++;
        if(i==(n-1) || x[i]==x[i+1]) kon=1;
    }
    if(koniec==2)
    {
        cout << "Powtarzaja sie x" << endl;
        return false;
    }
    return true;
}
bool zal2(float x[], float y[], int n, float xs)
{
    int koniec=0;
    while(koniec!=2)
    {
        if(xs>=x[0]&&xs<=x[n-1])
        {
            koniec=2;
        }
        else
        {
            cout << "Argument nie jest zawarty w zbiorze podanych argumentow" << endl;
            return false;
        }
        return true;
    }
}


float newtonuj(int n, float xs[], float ys[], float x)
{
    n++;
    float tab[n][n];
    for (int i = 0; i < n; i++)
    {
        tab[i][0] = xs[i];
        tab[i][1] = ys[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 2; j < n; j++)
        {
            tab[i][j] = 0;
        }
    }
    
    for (int j=2; j<n; j++)
    {
        for (int i=0;i<(n-1)-j+1;i++)
        {
            tab[i][j] = (tab[i+1][j-1]-tab[i][j-1])/(tab[i+1+(j-2)][0]-tab[i][0]);
        }
    }
    
    
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 2; j < n; j++)
        {
            cout << setw(5) << tab[i+1][j-1] << "-" << tab[i][j-1]<<"/"<<tab[i+1+(j-2)][0]<<"-"<<tab[i][0] << " = " << tab[i][j];
        }
        cout << endl;
    }
    
    float suma = tab[0][0];
    float iloczyn = 1;
    
    for (int i = 2; i < n; i++)
    {
        iloczyn = 1;
        cout << suma << endl;
        iloczyn *= tab[0][i];
        cout << "Ilprzedfor: " << iloczyn << endl;
        for (int j = 0; j < (i - 1); j++)
        {
            iloczyn *= x-tab[j][0];
            cout << "Il: " << x << " - " << tab[j][0] << endl;
        }
        suma+=iloczyn;
    }
    

    
    return suma;
        
}
    

int main()
{
    cout << "Ile elementow tablicy?: ";
    int n;
    cin >> n;
    cout << "Podaj x: ";
    float x;
    cin >> x;
    float xs[n];
    float ys[n];
    for(int i=0;i<n;i++)
    {
        cout << "Podaj x" << endl;
        cin >> xs[i];
        cout << "Podaj y" << endl;
        cin >> ys[i];
    }
    int l=0, p=n-1;
    quicksort(xs, ys, l, p);
    if (!(zal1(xs,ys,n) && zal2(xs,ys,n,x)))
        return 1;
    float wynik = newtonuj(n, xs, ys , x);
    cout << "Wartosc funkcji w punkcie " << x << " wynosi okolo: " << wynik << endl;
}
    