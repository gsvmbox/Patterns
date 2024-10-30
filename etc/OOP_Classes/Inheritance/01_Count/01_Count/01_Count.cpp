
#include "stdafx.h"


// counten2.cpp
// ������������ � ����������� �������
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////
class Counter
{
  protected:                         // �� ������� ������������ private
    unsigned int count;              // �������
  public:
    Counter ( ) : count ( )          // ����������� ��� ����������
      { }
    Counter ( int c ) : count ( c )  // ����������� � ����� ����������
      { }
    unsigned int get_count ( ) const // ��������� ��������
      { return count; }
    Counter operator++ ( )           // �������� ����������
      { return Counter ( ++count ); }
};
///////////////////////////////////////////////////////////
class CountDown : public Counter
{
  public:
    CountDown ( ) : Counter ( )        // ����������� ��� ����������
      { }
    CountDown ( int c ) : Counter ( c )// ����������� � ����� ����������
      { }
    CountDown operator-- ( )           // �������� ����������
      { return CountDown ( --count ); }
};
///////////////////////////////////////////////////////////
int main ( )
{
  CountDown c1;                            // ���������� ������ CountDn
  CountDown c2 ( 100 );

  cout << "\nc1 = " << c1.get_count ( ); // ������� �������� �� �����
  cout << "\nc2 = " << c2.get_count ( );

  ++c1; ++c1; ++c1;                      // ����������� c1
  cout << "\nc1 = " << c1.get_count ( ); // ���������� ���������

  --c2; --c2;                            // ��������� c2
  cout << " c2 = " << c2.get_count ( );   // ���������� ���������

  CountDown c3 = --c2;                     // ������� ���������� c3 �� ������ c2
  cout << "\nc3 = " << c3.get_count ( ); // ���������� ��������

  cout << endl;


  return 0;
}

