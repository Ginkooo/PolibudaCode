  #include <iostream>
  #include <iomanip>
  #include <math.h>

  using namespace std;


  float func_cos(float arg)
  {
      return pow(cos(arg), 2) + 1.0;
  }

  float func_pi(float arg)
  {
    return 1/(1+arg*arg);
  }




  float zadanie1(float a, float b, float eps)
  {
      float dystans = b - a;
      int ilosc_kwadratow = dystans/eps;
      if (ilosc_kwadratow * eps < dystans)
        ilosc_kwadratow++;
      int n = ilosc_kwadratow + 1;
      float granice[n];
      float temp = a;
      granice[0] = temp;
      int i = 1;
      while(true)
      {
        if (temp+eps>=b)
        {
          granice[i] = b;
          break;
        }
        temp += eps;
        granice[i] = temp;
        i++;
      }

      float suma = 0;
      for (int i = 0; i<n-1; i++)
      {
        suma += (granice[i+1]-granice[i])/2*(func_cos(granice[i])+func_cos(granice[i+1]));
      }

      return suma;

  }

  float zadanie3(float a, float b, float eps)
  {
      float dystans = b - a;
      int ilosc_kwadratow = dystans/eps;
      if (ilosc_kwadratow * eps < dystans)
        ilosc_kwadratow++;
      int n = ilosc_kwadratow + 1;
      float granice[n];
      float temp = a;
      granice[0] = temp;
      int i = 1;
      while(true)
      {
        if (temp+eps>=b)
        {
          granice[i] = b;
          break;
        }
        temp += eps;
        granice[i] = temp;
        i++;
      }
      float suma = 0;
      for (int i = 0; i<n-1; i++)
      {
        suma += (granice[i+1]-granice[i])/2*(func_pi(granice[i])+func_pi(granice[i+1]));
      }

      suma *= 2;

      return suma;

  }

  float zadanie4(float a, float b, float eps)
  {
      float dystans = b - a;
      int ilosc_kwadratow = dystans/eps;
      if (ilosc_kwadratow * eps < dystans)
        ilosc_kwadratow++;
      int n = ilosc_kwadratow + 1;
      float granice[n];
      float temp = a;
      granice[0] = temp;
      int i = 1;
      while(true)
      {
        if (temp+eps>=b)
        {
          granice[i] = b;
          break;
        }
        temp += eps;
        granice[i] = temp;
        i++;
      }


      float suma = 0;
      for (int i = 0; i<n-1; i++)
      {
        suma += (granice[i+1]-granice[i])/6*(func_pi(granice[i])+4*func_pi((granice[i+1] + granice[i])/2)+func_pi(granice[i+1]));
      }

      suma *= 2;

      return suma;

  }


  int main()
  {
    cout << "Podaj epsilon: ";
    float eps;
    cin >> eps;
    cout << zadanie1(0, 2*3.14, eps) << endl;
    cout << zadanie3(-1, 1, eps) << endl;
    cout << zadanie4(-1, 1, eps) << endl;
  }
