
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Message
{
private:
    string message;
public:
    Message(string message)
    {
        this->message = message;
    }
    string getMessage()
    {
        return this->message;
    }
};
class Observer
{
    //вызов update() чтобы проинформировать всех наблюдателей об изменениях 
public:
    virtual void update(Message* m) = 0;
};
class Subject
{
public:
    //вызов attach() чтобы добавить наблюдателей в список наблюдателей
    virtual void attach(Observer* observer) = 0;
    //вызов detach() чтобы удалить наблюдателей из списка наблюдателей
    virtual void detach(Observer* observer) = 0;
    //вызов notify()публиковать все изменения, внесенные издателем
    virtual void notify(Message* message) = 0;
};
//конкретный издатель
class ConcreteSubject : public Subject
{
private:
    vector<Observer*> observers = vector<Observer*>();
public:
    void attach(Observer* observer)
    {
        observers.push_back(observer);
    }
    void detach(Observer* observer)
    {
        vector<Observer*>::iterator itr = find(observers.begin(), observers.end(), observer);
        int observerIndexToBeRemoved = distance(observers.begin(), itr);
        observers.erase(observers.begin() + observerIndexToBeRemoved);
    }
    void notify(Message* message)
    {
        for (auto observer : observers)
        {
            observer->update(message);
        }
    }
};
//конкретные подписчики
class ObserverA : public Observer
{
public:
    void update(Message* m)
    {
        cout << "observerA: " + m->getMessage() << endl;
    }
};
class ObserverB : public Observer
{
public:
    void update(Message* m)
    {
        cout << "observerB: " + m->getMessage() << endl;
    }
};
class ObserverC : public Observer
{
public:
    void update(Message* m)
    {
        cout << "observerC: " + m->getMessage() << endl;
    }
};
class Demo
{
public:
    static void main(vector<string>& args)
    {
        ObserverA* a = new ObserverA();
        ObserverB* b = new ObserverB();
        ObserverC* c = new ObserverC();
        ConcreteSubject* publisher = new ConcreteSubject();
        publisher->attach(a);
        publisher->attach(b);
        publisher->notify(new Message("First update\n"));
        publisher->attach(c);
        publisher->detach(b);
        publisher->notify(new Message("Second update\n"));
    }
};
int main(int argc, char** argv) {
    vector<string> parameter(argv + 1, argv + argc);
    Demo::main(parameter);
    return 0;
};
