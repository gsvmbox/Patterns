

#include "stdafx.h"

// ambigu.cpp
// демонстрация неопределенности при множественном наследовании
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////
class A
{
  public:
    void show ( ) { cout << "Class A\n"; }
};
class B
{
  public:
    void show ( ) { cout << "Class B\n"; }
};
class C : public A, public B
{
};
class D : public C
{};
///////////////////////////////////////////////////////////
int main ( )
{
  C objC;           // объект класса C
 

// objC.show ( ); // так делать нельзя, программа не скомпилируется(ambigus - двусмысленный,
                  //                                                неопределенный)
  objC.A::show ( ); // так можно
  objC.B::show ( ); // так можно

  D objD;
  objD.B::show();

  return 0;
}


