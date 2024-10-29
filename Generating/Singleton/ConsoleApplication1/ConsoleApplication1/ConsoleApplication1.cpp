
#include <iostream>
#include "Singleton.h"

using namespace std;

int main()
{
   
    Singleton* o1;
    Singleton* o2;
    Singleton* o3;
    
    cout << o1->getInstance()<<endl;
    cout << o2->getInstance()<<endl;
  
    cout << o3->getInstance()<<endl;

 }

