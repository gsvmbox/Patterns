#include <iostream>
#include <array>
using namespace std;

/**
 * Интерфейс Посетителя объявляет набор методов посещения, соответствующих
 * классам компонентов. Сигнатура метода посещения позволяет посетителю
 * определить конкретный класс компонента, с которым он имеет дело.
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

/**
 * Интерфейс Компонента объявляет метод accept, который в качестве аргумента
 * может получать любой объект, реализующий интерфейс посетителя.
 */

class Component {
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

/**
 * Каждый Конкретный Компонент должен реализовать метод accept таким образом,
 * чтобы он вызывал метод посетителя, соответствующий классу компонента.
 */
class ConcreteComponentA : public Component {
    /**
     * visitConcreteComponentА => ConcreteComponentА
     */
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    /**
     * Конкретные Компоненты могут иметь особые методы, не объявленные в их
     * базовом классе или интерфейсе. Посетитель всё же может использовать эти
     * методы, поскольку он знает о конкретном классе компонента.
     */
    string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public Component {
    /**
     *  visitConcreteComponentB => ConcreteComponentB
     */
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    string SpecialMethodOfConcreteComponentB() const {
        return "B";
    }
};

/**
 * Конкретные Посетители реализуют несколько версий одного и того же алгоритма,
 * которые могут работать со всеми классами конкретных компонентов.
 *
 */
class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};
/**
 * Клиентский код может выполнять операции посетителя над любым набором
 * элементов, не выясняя их конкретных классов. Операция принятия направляет
 * вызов к соответствующей операции в объекте посетителя.
 */
void ClientCode(array<const Component*, 2> components, Visitor* visitor) {
    // ...
    for (const Component* comp : components) {
        comp->Accept(visitor);
    }
    // ...
}

int main() {
    setlocale(LC_ALL, "Russian");
    array<const Component*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
    cout << "Клиентский код работает со всеми Посетителями через общий интерфейс Visitor:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    cout << "\n";
    cout << "Это позволяет одному и тому-же клментскому коду работать с разными Посетителями:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}