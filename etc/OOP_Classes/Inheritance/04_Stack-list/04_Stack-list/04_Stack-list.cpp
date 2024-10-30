#include "stdafx.h"

// linklist.cpp
// ���������� ����� � ���� ���������� ������
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////
struct link   // ���� ������� ������
{
  int data;   // ��������� ������
  link* next; // ��������� �� ��������� ���������
};
///////////////////////////////////////////////////////////
class linklist // ���� ��� ��������� ������
{
  private:
    link* first;
  public:
    linklist ( )            // ����������� ��� ����������
      { first = NULL; }     // ������� �������� ���� ���

    void push ( int d ); // ���������� ��������
	void display ( );       // ����� ������
};
///////////////////////////////////////////////////////////
void linklist::push ( int d ) // ���������� ��������
{
  link* newlink = new link;      // �������� ������
  newlink->data = d;             // ���������� ������
  newlink->next = first;         // ���������� �������� first
  first = newlink;               // first ������ ��������� �� ����� �������
}
///////////////////////////////////////////////////////////
void linklist::display ( )
{
  link* current = first;           // �������� � ������� ��������
  while( current )                 // ���� ���� ������
  {
    cout << current->data << endl; // ������� ������
    current = current->next;       // ��������� � ���������� ��������
  }
}


///////////////////////////////////////////////////////////
int main ( )
{
  linklist li;       // ������� ����������-������

  li.push ( 25 ); // ��������� ���� ��������� �����
  li.push ( 36 );
  li.push ( 49 );
  li.push ( 64 );

  li.display ( );    // ���������� ������

  return 0;
}

