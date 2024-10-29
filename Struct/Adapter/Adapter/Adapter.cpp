#include<iostream>

using namespace std;
//Адаптер уровня объектов
/**
 * Целевой класс объявляет интерфейс, с которым может работать клиентский код.
 */
class Target {
public:
    virtual ~Target() = default;

    virtual string Request() const {
        return "Интерфейс класса Target.";
    }
};

/**
 * Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс
 * несовместим с существующим клиентским кодом. Адаптируемый класс нуждается в
 * некоторой доработке, прежде чем клиентский код сможет его использовать.
 */
class Adaptee {
public:
    string SpecificRequest() const {
        return "retpadA зереч tegraT матнеилк непутсод eetpadA ассалк сйефретнИ";
    }
};

/**
 * Адаптер делает интерфейс Адаптируемого класса совместимым с целевым
 * интерфейсом.
 */
class Adapter : public Target {
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
    string Request() const override {
        string to_reverse = this->adaptee_->SpecificRequest();
       reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (ПОДКЛЮЧИЛСЯ-СОГЛАСОВАЛ): " + to_reverse;
    }
};

/**
 * Клиентский код поддерживает все классы, использующие целевой интерфейс.
 */
void ClientCode(const Target* target) {
    cout << target->Request();
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Client: Работаю только с объектами Target.\n";
    Target* target = new Target;
    ClientCode(target);
    cout << "\n\n";
    Adaptee* adaptee = new Adaptee;
    cout << "Client: Интерфейс класса Adaptee недоступен.\n";
    cout << "Adaptee: " << adaptee->SpecificRequest();
    
    cout << "\n\n";
    cout << "Client: Умею работать с интерфейсом Adaptee через Adapter.\n";
    Adapter* adapter = new Adapter(adaptee);
    ClientCode(adapter);
    cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}