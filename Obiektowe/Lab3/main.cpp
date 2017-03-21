#include <iostream>
#include <math.h>

#define PI 3.14


using namespace std;

class Kolo
{
private:
    float promien;
    int kolor;
public:
    Kolo(float promien, int kolor)
    {
        this->promien = promien;
        this->kolor = kolor;
    }

    Kolo(float promien) : Kolo(promien, 0) {}
    Kolo() : Kolo(1, 0) {}

    float ObliczPole()
    {
        return PI * pow(promien, 2);
    }

    float OdliczObwod()
    {
        return 2*PI*promien;
    }

    void UstawPromien(float promien)
    {
        this->promien = promien;
    }

    void UstawKolor(int kolor)
    {
        this->kolor = kolor;
    }

    float GetPromien()
    {
        return this->promien;
    }

    float GetKolor()
    {
        return this->kolor;
    }

};

class Punkt
{
private:
    float x, y;
public:
    Punkt(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float GetX()
    {
        return x;
    }

    float GetY()
    {
        return y;
    }



    void Wektor()
    {
        cout << "[" << x << ", " << y << "]";
    }

    float Odleglosc()
    {
        return sqrt(pow(x-0, 2)+pow(y-0, 2));
    }


    int Cwiartka()
    {
        return (x > 0) && (y > 0) ? 1 : 0;
        return (x > 0) && (y < 0) ? 4 : 0;
        return (x < 0) && (y > 0) ? 2 : 0;
        return (x < 0) && (y < 0) ? 3 : 0;
    }

    bool OsX()
    {
        return y == 0 ? true : false;
    }

    bool OsY()
    {
        return x == 0 ? true : false;
    }

    static float OdlegloscMiedzyPunktami(Punkt punkt1, Punkt punkt2)
    {
        return sqrt(pow(punkt1.GetX() - punkt2.GetY(), 2)+pow(punkt1.GetY()-punkt2.GetY(), 2));
    }



};




int main(int argc, char *argv[])
{
    Punkt p1(3, 4);
    Punkt p2(4,4);
    Punkt p3(0,0);
    Punkt p4(1,0);

    cout << Punkt::OdlegloscMiedzyPunktami(p1, p4) << endl;

    cout << "\n\n\n\n\n";

    /* Obiekty na stosie
     *
     * Kolo k1;
        Kolo k2;
        if (k1.ObliczPole() < k2.ObliczPole())
            cout << "Pole k2 jest wieksze";
        else
            cout << "Pole k1 jest wieksze";
        k1.UstawKolor(2);
        k2.UstawKolor(2);
    */

    //Obiekty na stercie:
    Kolo *k1 = new Kolo(3, 2);
    Kolo *k2 = new Kolo(5, 4);

    if (k1->ObliczPole() < k2->ObliczPole())
        cout << "Pole k2 jest wieksze";
    else
        cout << "Pole k1 jest wieksze";
    k1->UstawKolor(2);
    k2->UstawKolor(2);
}
