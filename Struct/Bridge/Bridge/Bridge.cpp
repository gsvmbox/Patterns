#include <iostream>
using namespace std;

/**
 * Реализация устанавливает интерфейс для всех классов реализации. Он не должен
 * соответствовать интерфейсу Абстракции. На практике оба интерфейса могут быть
 * совершенно разными. Как правило, интерфейс Реализации предоставляет только
 * примитивные операции, в то время как Абстракция определяет операции более
 * высокого уровня, основанные на этих примитивах.
 */

class Implementation {
public:
    virtual ~Implementation() {}
    virtual string OperationImplementation() const = 0;
};

/**
 * Каждая Конкретная Реализация соответствует определённой платформе и реализует
 * интерфейс Реализации с использованием API этой платформы.
 */
class ConcreteImplementationA : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationA: Результат работы для реализации A.\n";
    }
};
class ConcreteImplementationB : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationB: Результат работы для реализации B.\n";
    }
};

/**
 * Абстракция устанавливает интерфейс для «управляющей» части двух иерархий
 * классов. Она содержит ссылку на объект из иерархии Реализации и делегирует
 * ему всю настоящую работу.
 */

class Abstraction {
    /**
     * @var Implementation
     */
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) : implementation_(implementation) {
    }

    virtual ~Abstraction() {
    }

    virtual string Operation() const {
        return "Abstraction: Базовая операция:\n" +
            this->implementation_->OperationImplementation();
    }
};
/**
 * Можно расширить Абстракцию без изменения классов Реализации.
 */
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {
    }
    string Operation() const override {
        return "ExtendedAbstraction: Расширенная операция:\n" +
            this->implementation_->OperationImplementation();
    }
};

/**
 * За исключением этапа инициализации, когда объект Абстракции связывается с
 * определённым объектом Реализации, клиентский код должен зависеть только от
 * класса Абстракции. Таким образом, клиентский код может поддерживать любую
 * комбинацию абстракции и реализации.
 */
void ClientCode(const Abstraction& abstraction) {
    // ...
    cout << abstraction.Operation();
    // ...
}
/**
 * Клиентский код должен работать с любой предварительно сконфигурированной
 * комбинацией абстракции и реализации.
 */

int main() {
    setlocale(LC_ALL, "Russian");
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    cout << endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    cout << endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}