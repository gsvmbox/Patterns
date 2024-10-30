/*���������� ����������� ������ ���������� � ������ �������  � ���� �������� ���� �����
�� ����� ���������� ���������. ��� ����������� ������������ ����� ����������� ����� 
������� � ���������� �������� ������������ � ���������� ��������� ����������� ������� 
(���������� � ����) ����� ��� ���� �� ��������. ��� ����, ����� ������������ ������������ ������,
������� ����� ������ ���� �����������, �.�. ��������� ����-�� ���� ����������� �������.
���������� ������������ �������� RTTI (Run-Time Type Information) ����� ��������� ������������� ����� typeinfo.h*/


#include "stdafx.h"


//dyncast1.cpp
//������������ ���������� ����� ��� �������� ���� �������
//RTTI ������ ���� �������
#include <iostream>
#include <typeinfo>          //��� dynamic_cast

using namespace std;

///////////////////////////////////////////////////////////
class Base
  { 
  virtual void virtFunc()    //��� dynamic cast
    {  }
  };
class Derv1 : public Base
  {  };
class Derv2 : public Base
  {  };
///////////////////////////////////////////////////////////
//��������, ��������� �� pUnknown �� Derv1
/*�������� dynamic_cast �������� �������� ��������� ������������ ���� � pUnknown � ���� Derv1.
���� ��������� ���������, ������ pUnknown �������� �� ������ ������ Derv1.*/
bool isDerv1(Base* pUnknown) //����������� �������� ��������
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

 

