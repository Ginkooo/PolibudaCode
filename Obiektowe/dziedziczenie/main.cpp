#include <iostream>

using namespace std;

class Animal
{

private:

  string name;

public:

  Animal(string name)
  {
    this->name = name;
  }

  void setName(string name)
  {
    this->name = name;
  }

  const string toString() const
  {
    return this->getAnimalKind() + this->name;
  }

  virtual const string getAnimalKind() const
  {
    return "Zwierzatko: ";
  }

};

class Dog : public Animal
{

public:

  Dog(string name) : Animal(name) {};

  void bark()
  {
    cout << "Hau hau!";
  }

  void shakeHands()
  {
    cout << "Daje lape";
  }

  const string getAnimalKind() const
  {
    return "Pies szczeka: ";
  }

};

class AnimalShelter
{

private:

  Animal *animals[100];
  int topIdx = -1;
public:

  Animal* getAnimalAtIndex(int idx)
  {

    if(idx > this->topIdx)
    {
      return NULL;
    }

    return this->animals[idx];
  }

  void captureAnimal(Animal* animal)
  {
    this->topIdx++;
    this->animals[topIdx] = animal;
  }

};


void ex1()
{
  Animal animal("Henryk");
  cout << animal.toString() << endl;
  const Animal& refAnimal = animal;
  cout << refAnimal.toString() << endl;
}

void ex2()
{
  Dog dog("Stefan");
  cout << dog.toString() << endl;
  dog.bark();
  cout << endl;
  dog.shakeHands();
  cout << endl;
}

void ex3()
{
  Animal animal("Henryk");
  cout << animal.toString() << endl;

  Dog dog("Stefan");
  cout << dog.toString() << endl;
  dog.bark();
  cout << endl;
  dog.shakeHands();
  cout << endl;
}

void ex4()
{

  // Nie mam pojęcia jak to zrobić

  // Dog* dog = new Dog("Stefan");
  // Animal* animal = new Animal("Zenon");
  // Dog* ptrDog1 = dog;
  // Dog* ptrDog2 = dynamic_cast<Dog*>(animal);
  // cout << ptrDog1->toString() << endl;
  // cout << ptrDog2->toString() << endl;
  //
  // Dog& refDog1 = dog;
  // Dog& refDog2 = dynamic_cast<Dog&>(animal);
  // cout << refDog1.toString() << endl;
  // cout << refDog2.toString() << endl;
}

void ex6()
{
  Animal* dog1 = new Dog("Henio");
  Animal* dog2 = new Dog("Henio1");
  Animal* dog3 = new Dog("Henio4");
  Animal* dog4 = new Dog("Henio2");
  AnimalShelter animalShelter;
  animalShelter.captureAnimal(dog1);
  animalShelter.captureAnimal(dog2);
  animalShelter.captureAnimal(dog3);
  animalShelter.captureAnimal(dog4);
  cout << animalShelter.getAnimalAtIndex(1)->toString();
}

//Już mi się nie chce

int main()
{
  // ex1();
  // ex2();
  // ex3();
  ex6();
}
