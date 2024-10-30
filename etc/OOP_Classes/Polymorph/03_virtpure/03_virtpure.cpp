// 03_virtpure.cpp : Defines the entry point for the console application.
//



// virtpure.cpp
  // ������ ����������� �������
  #include <iostream>
 
  using namespace std;
  class Base                   //������� �����
    {
    public:
      virtual void show() = 0; //������ �����������
                               //�������
    };
  //////////////////////////////////////////////////
  class Derv1 : public Base    //����������� ����� 1
    {
    public:
      void show()  
        { cout << "Derv1\n"; }
    };
  //////////////////////////////////////////////////
  class Derv2 : public Base    //����������� ����� 2
    {
    public:
      void show()
        { cout << "Derv2\n"; }
    };
  /////////////////////////////////////////////////
  int main()
    {
  // Base bad;                 //���������� ������� ������
                               //�� ������������ ������
    Base* arr[2];              //������ ���������� ��
                               //������� �����
    Derv1 dv1;                 //������ ������������ ������ 1
    Derv2 dv2;                 //������ ������������ ������ 2
    
    arr[0] = &dv1;             //������� ����� dv1 � ������
    arr[1] = &dv2;             //������� ����� dv2 � ������

    arr[0]->show();            //��������� ������� show()
    arr[1]->show();            //��� ������ ���������

    return 0;
    }



