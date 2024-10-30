

#include "stdafx.h"


// staken.cpp
// перегрузка функций базового и производного классов
#include <iostream>

using namespace std;
#include <process.h>      // для exit ( )
///////////////////////////////////////////////////////////
class Stack
{
  protected:              // Замечание: использовать private нельзя
    enum { MAX = 3 };     // размер стека
    int st[ MAX ];        // данные, хранящиеся в стеке
    int top;              // индекс последнего элемента в стеке
  public:
    Stack ( )            // конструктор
      { top = -1; }
    void push ( int var ) // помещение числа в стек
      { st[ ++top ] = var; }
    int pop ( )           // извлечение числа из стека
      { return st[ top-- ]; }
};
///////////////////////////////////////////////////////////
class Stack2 : public Stack
{
  public:
    void push ( int var )      // помещение числа в стек
      {
        if ( top >= MAX-1  )  // если стек полон, то ошибка
          { cout << "\nError stack is ful"; exit ( 1 ); }
        Stack::push ( var );   // вызов функции push класса Stack
      }
    int pop ( )                // извлечение числа из стека
      {
        if ( top < 0 )         // если стек пуст, то ошибка
          { cout << "\nError stack is empty\n"; exit ( 1 ); }
        return Stack::pop ( ); // вызов функции pop класса Stack
      }
};
///////////////////////////////////////////////////////////
int main ( )
{
  Stack2 s1;

  s1.push ( 11 );
  s1.push ( 22 );
  s1.push ( 33 );

  cout << endl << s1.pop ( ); 
  cout << endl << s1.pop ( ); 
  cout << endl << s1.pop ( ); 
//  cout << endl << s1.pop ( ); 
  cout << endl << s1.Stack::pop ( );  //обращение к методу базового класса
  cout << endl;


  return 0;
}



