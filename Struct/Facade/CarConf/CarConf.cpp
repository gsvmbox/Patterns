#include <iostream>
using namespace std;

/**
 * Подсистема может принимать запросы либо от фасада, либо от клиента напрямую.
 * В любом случае, для Подсистемы Фасад – это еще один клиент, и он не является
 * частью Подсистемы.
 */
class Brand {//подсистема выбора бренда
public:
    string Brand_1() const {
        return "Brand:ОЧЕНЬ_ХОРОШИЙ\n";
    }
    // ...
    string Brand_2() const {
        return "Brand:ХОРОШИЙ\n";
    }

    string Brand_3() const {
        return "Brand:ЧТОБЫ_ЕХАЛ\n";
    }
};
/**
 * Некоторые фасады могут работать с разными подсистемами одновременно.
 */
class Engine {//подсистема выбора типа двигателя
public:
    string EType(int t) const {
        if (t == 0) return "Дизель\n";
        else if (t == 1) return "Бензин\n";
        else if (t == 2) return "Гибрид\n";
    }
    // ...
   
    string EPower(int t) const {
        if (t == 0) return "125 л.с.\n";
        else if (t == 1) return "150 л.с.\n";
        else if (t == 2) return "250 л.с.\n";
    }
};

class Wheels {//подсистема выбора типа колес
public:
    string WType(bool t) const {
        if (t) return "Литые\n";
        else  return "Штампованные\n";
    }
    // ...

    string WDia(int t) const {
        if (t == 0) return "16''\n";
        else if (t == 1) return "18''\n";
        else if (t == 2) return "20''\n";
    }
};

/**
 * Класс Фасада предоставляет простой интерфейс для сложной логики одной или
 * нескольких подсистем. Фасад делегирует запросы клиентов соответствующим
 * объектам внутри подсистемы. Фасад также отвечает за управление их жизненным
 * циклом. Все это защищает клиента от нежелательной сложности подсистемы.
 */
class Facade {//конфигуратор автомобиля
protected:
    Brand* subsystem1_;
    Engine* subsystem2_;
    Wheels* subsystem3_;
    /**
     * В зависимости от потребностей  приложения  можно предоставить
     * Фасаду существующие объекты подсистемы или заставить Фасад создать их
     * самостоятельно.
     */
public:
    /**
     * Фасад создает объекты подсистем
     */
    Facade(Brand* subsystem1, Engine* subsystem2, Wheels* subsystem3) {
        this->subsystem1_ = subsystem1;
        this->subsystem2_ = subsystem2;
        this->subsystem3_ = subsystem3;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
        delete subsystem3_;
    }
    /**
     * Методы Фасада удобны для быстрого доступа к сложной функциональности
     * подсистем. Однако клиенты получают только часть возможностей подсистемы.
     */
    string LuxCar() {
        string result = "Luxary автомобиль:\n";
        result += this->subsystem1_->Brand_1();
        result += this->subsystem2_->EType(2);
        result += this->subsystem2_->EPower(2); 
        result += this->subsystem3_->WType(1);
        result += this->subsystem3_->WDia(2);
       
        return result;
    }

    string BusinessCar() {
        string result = "Business автомобиль:\n";
        result += this->subsystem1_->Brand_2();
        result += this->subsystem2_->EType(0);
        result += this->subsystem2_->EPower(1);
        result += this->subsystem3_->WType(1);
        result += this->subsystem3_->WDia(1);
        return result;
    }

    string BasicCar() {
        string result = "Low-cost автомобиль:\n";
        result += this->subsystem1_->Brand_3();
        result += this->subsystem2_->EType(1);
        result += this->subsystem2_->EPower(0);
        result += this->subsystem3_->WType(0);
        result += this->subsystem3_->WDia(0);
        return result;
    }
};

/**
 * Клиентский код работает со сложными подсистемами через простой интерфейс,
 * предоставляемый Фасадом. Когда фасад управляет жизненным циклом подсистемы,
 * клиент может даже не знать о существовании подсистемы. Такой подход позволяет
 * держать сложность под контролем.
 */
void ClientCode(Facade* facade) {//Конфигурацию подсистем можно изменять не меняя клиентский код
    // Выбор конфогурации автомобиля
    cout << facade->LuxCar() << endl;
    cout << facade->BusinessCar() << endl;
    cout << facade->BasicCar();
    // ...
}
/**
 * В клиентском коде могут быть уже созданы некоторые объекты подсистемы. В этом
 * случае может оказаться целесообразным инициализировать Фасад с этими
 * объектами вместо того, чтобы позволить Фасаду создавать новые экземпляры.
 */

int main() {
    setlocale(LC_ALL, "Russian");
    Brand* subsystem1 = new Brand;
    Engine* subsystem2 = new Engine;
    Wheels* subsystem3 = new Wheels;
    Facade* facade = new Facade(subsystem1, subsystem2, subsystem3);
    ClientCode(facade);

    delete facade;

    return 0;
}