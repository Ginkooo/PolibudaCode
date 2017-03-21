#include <iostream>
#include <fstream>
using namespace std;

struct point
{
    double y1;
    double y2;
    double y1der;
    double y2der;
};

int main() {
    double deltaT = 0.1;
	double t = 10;
	int n = t / 0.1 + 1;
	ofstream csv ("euler.csv", ios::out | ios::app);
	csv << "y1; y2\n";
	point point[n];
	point[0].y1 = 1;
	point[0].y2 = 1;
	point[0].y1der = - (1 + 1);
	point[0].y2der = 1 - 1;
	for (int i = 1; i < n; i++)
	{
	     point[i].y1 = point[i-1].y1 + point[i-1].y1der * deltaT;
	     point[i].y2 = point[i-1].y2 + point[i-1].y2der * deltaT;
	     point[i].y1der = - (point[i].y1 + point[i].y2);
	     point[i].y2der = point[i].y1 - point[i].y2;
	}
	for (int i = 0; i < n; i++)
	{
	    csv << point[i].y1 << "; " << point[i].y2 << endl;
	}
	csv.close();
	return 0;
}
