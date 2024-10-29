#include <iostream>
using namespace std;

/**
 * Подсистема может принимать запросы либо от фасада, либо от клиента напрямую.
 * В любом случае, для Подсистемы Фасад – это еще один клиент, и он не является
 * частью Подсистемы.
 */
class Subsystem1 {
public:
    string Operation1() const {
        return "Subsystem1: Подсистема_1 готова!\n";
    }
    // ...
    string OperationN() const {
        return "Subsystem1: Действие_1-N выполнено\n";
    }

    string OperationAlt() const {
        return "Subsystem1: Выполнена альтернативная операция-1\n";
    }
};
/**
 * Некоторые фасады могут работать с разными подсистемами одновременно.
 */
class Subsystem2 {
public:
    string Operation1() const {
        return "Subsystem2: Подсистема_2 готова!\n";
    }
    // ...
    string OperationZ() const {
        return "Subsystem2: Действие_2-Z выполнено\n";
    }

    string OperationAlt() const {
        return "Subsystem2: Выполнена альтернативная операция-2\n";
    }
};

/**
 * Класс Фасада предоставляет простой интерфейс для сложной логики одной или
 * нескольких подсистем. Фасад делегирует запросы клиентов соответствующим
 * объектам внутри подсистемы. Фасад также отвечает за управление их жизненным
 * циклом. Все это защищает клиента от нежелательной сложности подсистемы.
 */
class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
    /**
     * В зависимости от потребностей вашего приложения вы можете предоставить
     * Фасаду существующие объекты подсистемы или заставить Фасад создать их
     * самостоятельно.
     */
public:
    /**
     * In this case we will delegate the memory ownership to Facade Class
     */
    Facade(Subsystem1* subsystem1, Subsystem2* subsystem2) {
        this->subsystem1_ = subsystem1;
        this->subsystem2_ = subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    /**
     * Методы Фасада удобны для быстрого доступа к сложной функциональности
     * подсистем. Однако клиенты получают только часть возможностей подсистемы.
     */
    string OperationA() {
        string result = "Facade (Фасад) инициализирует подсистемы:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade (Фасад) делегирует подсистемам выполнение действий:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }

    string OperationB() {
        string result = "Facade (Фасад) инициализирует подсистемы:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade (Фасад) делегирует подсистемам выполнение действий:\n";
        result += this->subsystem1_->OperationAlt();
        result += this->subsystem2_->OperationAlt();
        return result;
    }
};

/**
 * Клиентский код работает со сложными подсистемами через простой интерфейс,
 * предоставляемый Фасадом. Когда фасад управляет жизненным циклом подсистемы,
 * клиент может даже не знать о существовании подсистемы. Такой подход позволяет
 * держать сложность под контролем.
 */
void ClientCode(Facade* facade) {
    // ...
    cout << facade->OperationA()<<endl;
    cout << facade->OperationB();
    // ...
}
/**
 * В клиентском коде могут быть уже созданы некоторые объекты подсистемы. В этом
 * случае может оказаться целесообразным инициализировать Фасад с этими
 * объектами вместо того, чтобы позволить Фасаду создавать новые экземпляры.
 */

int main() {
    setlocale(LC_ALL, "Russian");
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;

    return 0;
}