

#include "stdafx.h"


//vertdest.cpp
//���� ������������� � ����������� ������������
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////
class Base
   {
   public:
    //  ~Base()                 //������������� ����������
   virtual ~Base()         //����������� ����������
         { cout << "Base deleted\n"; }
      };
///////////////////////////////////////////////////////////
class Derv : public Base
  {
   public:
      ~Derv()
         { cout << "Derv deleted\n"; }
	   };
///////////////////////////////////////////////////////////
int main()
   {
   Base* pBase = new Derv;
   delete pBase;
   return 0;
   }


