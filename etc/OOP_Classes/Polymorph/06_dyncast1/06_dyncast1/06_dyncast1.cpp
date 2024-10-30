/*Существует возможность узнать информацию о классе объекта  и даже изменить этот класс
во время выполнения программы. Эти возможности используются когда порожденный класс 
получен в результате сложного наследования и необходимо выполнить модификацию объекта 
(приведение к типу) вверх или вниз по иерархии. Для того, чтобы использовать динамический подход,
базовый класс должен быть полиморфным, т.е. содержать хотя-бы одну виртуальную функцию.
Необходимо активировать механизм RTTI (Run-Time Type Information) путем включения заголовочного файла typeinfo.h*/


#include "stdafx.h"


//dyncast1.cpp
//динамическое приведение типов для проверки типа объекта
//RTTI должен быть включен
#include <iostream>
#include <typeinfo>          //для dynamic_cast

using namespace std;

///////////////////////////////////////////////////////////
class Base
  { 
  virtual void virtFunc()    //для dynamic cast
    {  }
  };
class Derv1 : public Base
  {  };
class Derv2 : public Base
  {  };
///////////////////////////////////////////////////////////
//проверка, указывает ли pUnknown на Derv1
/*Оператор dynamic_cast пытается привести указатель неизвестного типа к pUnknown к типу Derv1.
Если результат ненулевой, значит pUnknown указывал на объект класса Derv1.*/
bool isDerv1(Base* pUnknown) //неизвестный подкласс базового
  {
  Derv1* pDerv1;
  if( pDerv1 = dynamic_cast<Derv1*>(pUnknown) )
     {cout<<pDerv1<<" "<<pUnknown<<" ";
    return true;   }
  else  {cout<<pDerv1<<" "<<pUnknown<<" ";
    return false;     }
  }
//---------------------------------------------------------
int main()
  {
  Derv1* d1 = new Derv1;
  Derv2* d2 = new Derv2;

  if( isDerv1(d1) )
    cout << "d1 is object of Derv1\n";
  else
    cout << "d1 is not Derv1 object\n";

  if( isDerv1(d2) )
    cout << "d2 is object of Derv1\n";
  else
    cout << "d2 is not Derv1 object\n";


  return 0;
  }

 

