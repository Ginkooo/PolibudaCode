#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Array2D
{
private:
  int width;
  int height;
  int size;
  float* values;
  string name;

  int getIndex(int row, int column)
  {
    return column + row * this->width;
  }

  float getValueAtIndex(int index)
  {
    return this->values[index];
  }

public:
  Array2D(int height, int width, string name)
  {
    this->height = height;
    this->width = width;
    this->size = width * height;
    this->name = name;
    this->values = new float[this->size];
  }

  Array2D (const Array2D& toCopy)
  {
    this->values = new float[toCopy.size];
    this->height = toCopy.height;
    this->width = toCopy.width;
    this->size = toCopy.size;
    this->name = "Copied from " + toCopy.name;

    for (int i=0; i<toCopy.size; i++)
    {
      this->values[i] = toCopy.values[i];
    }

  }

  void setName(string name)
  {
    this->name = name;
  }

  void setValue(int row, int column, float value)
  {
    int index = getIndex(row, column);

    this->values[index] = value;
  }

  float getValue(int row, int column)
  {
    int index = getIndex(row, column);

    return this->values[index];
  }

  const Array2D add(const Array2D& toAdd)
  {
    cout << &*this << endl << flush;
    Array2D ret = Array2D(*this);
    ret.setName("Addition result");

    for (int i=0; i<this->size; i++)
    {
      ret.values[i] = this->values[i] + toAdd.values[i];
    }

    return ret;
  }

  const Array2D multiply(const Array2D& toAdd)
  {

    Array2D ret = Array2D(*this);
    ret.setName("Addition result");

    for (int i=0; i<this->size; i++)
    {
      ret.values[i] = this->values[i] * toAdd.values[i];
    }

    return ret;
  }

  const ostream& display(ostream& stream)
  {

    stream << this->name << "\n";

    int j = 0;

    for (int i=0; i<this->size; i++)
    {
      stream << setw(5) << this->values[i];

      j++;

      if (j==this->width)
      {
        stream << "\n";
        j = 0;
      }

    }

    return stream;
  }

};

int main()
{
  Array2D arr1(4,6, "myArray1");
  arr1.setValue(2, 3, 8.5);
  arr1.setValue(0, 5, 2);
  Array2D copied(arr1);
  copied.setValue(2, 3, 1);
  copied.setValue(0, 4, 3);
  copied.display(cout);
  arr1.display(cout);

  cout << flush;





  return 0;
}
