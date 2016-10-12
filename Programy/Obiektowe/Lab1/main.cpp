#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>

using namespace std;

struct Pracownik
{
    string imie;
    string nazwisko;
    double stawkaGodzinowa;
    int liczbaGodzin;
    string dataZatrudnienia;
};

void zadanie2()
{
    int inputformat = 0;
    int number;
    int outputformat = 0;
    cout << "Podaj zapis wpisywanej liczby. 1: Dziesiętny, 2: Ósemkowy, 3: Hexa, 4: Automatycznie wykryj: ";
    cin >> inputformat;
    switch(inputformat)
    {
    case 1:
        cin >> setbase(10);
        break;
    case 2:
        cin >> setbase(8);
        break;
    case 3:
        cin >> setbase(16);
        break;
    case 4:
        cin >> setbase(0);
        break;
    default:
        cout << "żle";
        return;
    }

    cout << "Podaj liczbę: ";
    cin >> number;
    cout << "Podaj format wyjsciowy. 1: Dziesiętny, 2: Ósemkowy, 3: Hexa: ";
    cin >> outputformat;
    switch(outputformat)
    {
    case 1:
        cout << setbase(10);
        break;
    case 2:
        cout << setbase(8);
        break;
    case 3:
        cout << setbase(16);
        break;
    default:
        cout << "żle";
        return;
    }
    cout << number << endl;
}

void zadanie3()
{
    int n;
    string _imie, _nazwisko, _data;
    int _liczbaGodzin;
    double _stawka;
    vector<Pracownik> pracownicy; //Równie dobrze może być zwyczajna tablica struktur zamiast tego.
    cout << "Podaj ilość pracownikow: ";
    cin >> n;
    for (int i = 0; i<n; i++)
    {
        cout << "Podaj imie pracownika " << i << ": ";
        cin >> _imie;
        cout << "Podaj nazwisko pracownika " << i << ": ";
        cin >> _nazwisko;
        cout << "Podaj liczbe godzin pracownika " << i << ": ";
        cin >> _liczbaGodzin;
        cout << "Podaj stawke pracownika " << i << ": ";
        cin >> _stawka;
        cout << "Podaj date zatrudnienia pracownika " << i << ": ";
        cin >> _data;

        Pracownik temp;
        temp.imie = _imie;
        temp.nazwisko = _nazwisko;
        temp.liczbaGodzin = _liczbaGodzin;
        temp.dataZatrudnienia = _data;
        temp.stawkaGodzinowa = _stawka;

        pracownicy.push_back(temp);
    }

    cout << "\n\n\n";

    cout << setw(10) << "Imie " <<setw(10)<< "Nazwisko " <<setw(10)<< "Data zatrudnienia " <<setw(10)<< "Stawka godzinowa " <<setw(10)<< "Liczba godzin " << endl;
    for (int i=0; i<pracownicy.size(); i++)
    {
        cout << setw(10) << pracownicy.at(i).imie << setw(10) << pracownicy.at(i).nazwisko << setw(10) << pracownicy.at(i).dataZatrudnienia << setw(10) << pracownicy.at(i).stawkaGodzinowa << setw(10) << pracownicy.at(i).liczbaGodzin << endl;

    }
}


void zadanie5()
{
    int number;
    cout << "Podaj liczbę w systemie dziesiętnym: ";
    cin >> number;
    int temp = number;
    int n;
    while ( temp != 1)
    {
        temp /= 2;
        n++;
    }
    n++;

    short bits[n];

    int s;
    int wynik = number;
    for (int i = 0; i<n; i++)
    {

        int reszta = wynik % 2;
        wynik /=2;
        bits[i] = reszta;
    }

    for (int i=n-1; i>=0; i--)
    {
        cout << bits[i];
    }

}

void zadanie4()
{
    int choice;
    ifstream fileInput("file.txt");
    string firstName, lastName, employmentDate;
    double hourlyRate;
    int hoursAmount;
    vector<Pracownik> pracownicy;
    stringstream stringStream;

    cout << "Wybierz format wyswietlanych danych 1: polski, 2: amerykański: ";
        cin >> choice;
        switch(choice)
        {
            case 1: cout.imbue(locale("pl_PL.utf8"));
                    break;
            case 2: cout.imbue(locale("en_US.utf8"));
                    break;
            default: cout << "Źle" << endl;
                     return;
        }

        string line;

    if (fileInput.is_open())
    {
        getline(fileInput, line);
        while(!fileInput.eof())
        {
            getline(fileInput, line);
            stringStream << line;
            stringStream >> firstName >> lastName >> employmentDate >> hourlyRate >> hoursAmount;
            Pracownik pracownik = { firstName, lastName, hourlyRate, hoursAmount, employmentDate };
            pracownicy.push_back(pracownik);
        }
    }
    fileInput.close();

    cout << line;

    for (int i=0; i<pracownicy.size(); i++)
    {
        cout << setw(10) << pracownicy.at(i).imie << setw(10) << pracownicy.at(i).nazwisko << setw(10) << pracownicy.at(i).dataZatrudnienia << setw(10) << pracownicy.at(i).stawkaGodzinowa << setw(10) << pracownicy.at(i).liczbaGodzin << endl;

    }
}

int main(int argc, char *argv[])
{

    //zadanie2();
    //zadanie3();
    //zadanie4();
    zadanie5();

    cin >> argc;

    return 0;
}
