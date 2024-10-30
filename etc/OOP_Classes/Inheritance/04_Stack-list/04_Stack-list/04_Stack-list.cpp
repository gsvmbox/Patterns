#include "stdafx.h"

// linklist.cpp
// реализация стека в виде связанного списка
#include <iostream>

using namespace std;
///////////////////////////////////////////////////////////
struct link   // один элемент списка
{
  int data;   // некоторые данные
  link* next; // указатель на следующую структуру
};
///////////////////////////////////////////////////////////
class linklist // стек как связынный список
{
  private:
    link* first;
  public:
    linklist ( )            // конструктор без параметров
      { first = NULL; }     // первого элемента пока нет

    void push ( int d ); // добавление элемента
	void display ( );       // показ данных
};
///////////////////////////////////////////////////////////
void linklist::push ( int d ) // добавление элемента
{
  link* newlink = new link;      // выделяем память
  newlink->data = d;             // запоминаем данные
  newlink->next = first;         // запоминаем значение first
  first = newlink;               // first теперь указывает на новый элемент
}
///////////////////////////////////////////////////////////
void linklist::display ( )
{
  link* current = first;           // начинаем с первого элемента
  while( current )                 // пока есть данные
  {
    cout << current->data << endl; // выводим данные
    current = current->next;       // двигаемся к следующему элементу
  }
}


///////////////////////////////////////////////////////////
int main ( )
{
  linklist li;       // создаем переменную-список

  li.push ( 25 ); // добавляем туда несколько чисел
  li.push ( 36 );
  li.push ( 49 );
  li.push ( 64 );

  li.display ( );    // показываем список

  return 0;
}

