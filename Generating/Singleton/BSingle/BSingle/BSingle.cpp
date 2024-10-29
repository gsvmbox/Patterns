#include "Singleton.h"

#include <iostream>
using namespace std;

int main()
{
 
    Singleton* o1;
    Singleton* o2;
 
    cout << o1->getInstance()<<endl;
    cout << o2->getInstance();
   
}
