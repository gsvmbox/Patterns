/*При восходящем приведении типов производится попытка изменить объект порожденного класса на объект базового класса.
При этом получается унаследованная из базового класса часть объекта порожденного. Восходящее приведение типов
целесообразно использовать, когда нужно получить базовую составляющую объекта.
При нисходящем приведении переносится ссылка на объект порожденного класса из указателя 
базового класса в указатель порожденного*/



//dyncast2.cpp
//Тестирование динамического приведения типов
//RTTI должен быть включен
#include <iostream>
#include <typeinfo>          //для dynamic_cast

using namespace std;
///////////////////////////////////////////////////////////
class Base
  {
  protected:
    int ba;
  public:
    Base() : ba(0)
      {  }
    Base(int b) : ba(b)
      {  }    
    virtual void virtFunc()  //для нужд dynamic_cast
      {  }
    void show()
      { cout << "Base: ba=" << ba << endl; }
  };
///////////////////////////////////////////////////////////
class Derv :  public Base
  {
  private:
    int da;
  public:
    Derv(int b, int d) : da(d)
      { ba = b; }
    void show()
      { cout << "Derv: ba=" << ba << ", da=" << da << endl; }
  };
////////////////////////////////////////////////////////////////
int main()
  {
  Base* pBase = new Base(10);     //указатель на Base
  Derv* pDerv = new Derv(21, 22); //указатель на Derv

  //приведение к базовому типу: восхождение  по дереву –
  //указатель поставлен на подобъект Base класса Derv
  pBase->show();
  pDerv->show();
  pBase = dynamic_cast<Base*>(pDerv);
  pBase->show();                  //"Base: ba=21"
  cout<<endl;

  pBase = new Derv(31, 32);       //обычное нисходящее
   //приведение типов -- pBase должен указывать на Derv)
  pBase->show();
  pDerv = dynamic_cast<Derv*>(pBase);
  pDerv->show();                  //"Derv: ba=31, da=32"

  return 0;
  }

 

