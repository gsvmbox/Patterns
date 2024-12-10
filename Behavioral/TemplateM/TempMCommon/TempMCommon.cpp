#include <iostream>
using namespace std;

/**
 * Абстрактный Класс определяет шаблонный метод, содержащий скелет некоторого
 * алгоритма, состоящего из вызовов (обычно) абстрактных примитивных операций.
 *
 * Конкретные подклассы должны реализовать эти операции, но оставить сам
 * шаблонный метод без изменений.
 */
class AbstractClass {
    /**
     * Шаблонный метод определяет скелет алгоритма.
     */
public:
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
    /**
     * Эти операции уже имеют реализации.
     */
protected:
    void BaseOperation1() const {
        cout << "AbstractClass: Выполнение большей части работы\n";
    }
    void BaseOperation2() const {
        cout << "AbstractClass: Конкретные классы могут переопределить часть операций\n";
    }
    void BaseOperation3() const {
        cout << "AbstractClass: Основная часть работы выполняется абстрактным классом\n";
    }
    /**
     * А эти операции должны быть реализованы в подклассах.
     */
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;
    /**
     * Это «хуки». Подклассы могут переопределять их, но это не обязательно,
     * поскольку у хуков уже есть стандартная (но пустая) реализация. Хуки
     * предоставляют дополнительные точки расширения в некоторых критических
     * местах алгоритма.
     */
    virtual void Hook1() const {}
    virtual void Hook2() const {}
};
/**
 * Конкретные классы должны реализовать все абстрактные операции базового
 * класса. Они также могут переопределить некоторые операции с реализацией по
 * умолчанию.
 */
class ConcreteClass1 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        cout << "ConcreteClass1: Реализация операции RequiredOperation1\n";
    }
    void RequiredOperation2() const override {
        cout << "ConcreteClass1: Реализация операции RequiredOperation2\n";
    }
};
/**
 * Обычно конкретные классы переопределяют только часть операций базового
 * класса.
 */
class ConcreteClass2 : public AbstractClass {
protected:
    void RequiredOperations1() const override {
        cout << "ConcreteClass2: Реализация операции RequiredOperation1\n";
    }
    void RequiredOperation2() const override {
        cout << "ConcreteClass2: Реализация операции RequiredOperation2\n";
    }
    void Hook1() const override {
        cout << "ConcreteClass2: Переопределенная операция (хук) Hook1\n";
    }
};
/**
 * Клиентский код вызывает шаблонный метод для выполнения алгоритма. Клиентский
 * код не должен знать конкретный класс объекта, с которым работает, при
 * условии, что он работает с объектами через интерфейс их базового класса.
 */
void ClientCode(AbstractClass* class_) {
    // ...
    class_->TemplateMethod();
    // ...
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Работа клиента с конкретным классом ConcreteClass1:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    cout << "\n";
    cout << "Работа клиента с конкретным классом ConcreteClass2:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}