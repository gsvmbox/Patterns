#include <iostream>
#include <string>
#include <typeinfo> //для получения информации о типах RTTI 
using namespace std;
/**
 * Интерфейс Посредника предоставляет метод, используемый компонентами для
 * уведомления посредника о различных событиях. Посредник может реагировать на
 * эти события и передавать исполнение другим компонентам.
 */
class BaseComponent;
class Mediator {
public:
    virtual void Notify(BaseComponent* sender,string event) const = 0;
};

/**
 * Базовый Компонент обеспечивает базовую функциональность хранения экземпляра
 * посредника внутри объектов компонентов.
 */
class BaseComponent {
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) {
    }
    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
    virtual void virtFunc() {}  //для нужд dynamic_cast

};

/**
 * Конкретные Компоненты реализуют различную функциональность. Они не зависят от
 * других компонентов. Они также не зависят от каких-либо конкретных классов
 * посредников.
 */
class Component1 : public BaseComponent {
public:
    void DoA() {
       cout << "Компонент 1 выполняет A.\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB() {
       cout << "Компонент 1 выполняет B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent {
public:
    void DoC() {
       cout << "Компонент 2 выполняет C.\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD() {
       cout << "Компонент 2 выполняет D.\n";
        this->mediator_->Notify(this, "D");
    }
};

/**
 * Конкретные Посредники реализуют совместное поведение, координируя отдельные
 * компоненты.
 */
class ConcreteMediator : public Mediator {
private:
    Component1* component1_;
    Component2* component2_;
   

public:
    ConcreteMediator(Component1* c1, Component2* c2) : component1_(c1), component2_(c2) {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this); 
    }
    void Notify(BaseComponent* sender,string event) const override {
           
        if (event == "A") {
           cout << "Посредник реагирует на A и запускает следующие операции:\n";
           this->component2_->DoC();
           dynamic_cast<Component1*>(sender)->DoB(); //или так, используя нисхоящее приведение типов
           cout << typeid(*sender).name() << endl;
        }
        if (event == "D") {
           cout << "Посредник реагирует на D и запускает следующие операции:\n";
            this->component1_->DoB();
            this->component2_->DoC();
            dynamic_cast<Component2*>(sender)->DoC(); //или так, используя нисхоящее приведение типов 
            cout << typeid(*sender).name() << endl;
        }
    }
};

/**
 * Клиентский код.
 */

void ClientCode() {
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
   cout << "Клиент запускает операцию A.\n";
    c1->DoA();
   cout << "\n";
   cout << "Клиент запускает операцию D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ClientCode();
    return 0;
}