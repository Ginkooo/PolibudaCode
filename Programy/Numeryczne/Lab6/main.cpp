#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

//Równanie - f(x) = x^3 - 2*x^2 - 4*x - 7
//Pochodna - f'(x) = 3*x^2 - 4*x - 4

double function(double x)
{
  return pow(x, 3) - 2 * pow(x, 2) - 4 * x - 7;
}

double derivative(double x)
{
  return 3 * pow(x, 2) - 4 * x - 4;
}


double bisekcja(double x0, double x1, double epsilon, double (*function)(double))
{
  if ((function(x0) * function(x1) >= 0) || function(x0) == 0 || function(x1) == 0)
  {
    throw invalid_argument("Root is not between x0 and x1");
  }

  double a = (x0 + x1) / 2.0;

  while(abs(function(a)) >= epsilon)
  {
    a = (x0 + x1) / 2.0;
    if (function(a) == 0)
      return a;
    if (function(a) * function(x0) < 0)
      x1 = a;
    else
      x0 = a;

    if (x1 - x0 < epsilon)
      break;
  }

  return x0;
}

double newton(double x0, double x1, double epsilon, double (*function)(double),
              double (*derivative)(double))
{
  double x_o = x1;
  double x_n = x1;

  do
  {
  x_o = x_n;

    x_n = x_o - function(x_o)/derivative(x_o);
  }
  while(abs(function(x_n)) > epsilon);

  return x_n;
}

int main()
{
  try
  {
    double result = bisekcja(3, 4, pow(10, -3), function);
    cout << "Result is: " << result << endl;
  }
  catch (exception& e)
  {
    cout << e.what() << endl;
  }

  cout << endl << endl;

  cout << "Result is: " << newton(3, 4, pow(10, -3), function, derivative) << endl;

}
