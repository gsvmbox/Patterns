#include<iostream>
#include <unordered_map>
using namespace std;


// Паттерн Прототип
//
// Назначение: Позволяет копировать объекты, не вдаваясь в подробности их
// реализации.

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

/**
 * Пример класса, имеющего возможность клонирования. 
 */

class Prototype {
protected:
    string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}
    Prototype(string prototype_name)
        : prototype_name_(prototype_name) {
    }
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float prototype_field) {
        this->prototype_field_ = prototype_field;
        cout << "Вызван метод из " << prototype_name_ << " со значением поля : " << prototype_field << endl;
    }
};

/**
 * ConcreteProtype1 является подклассом Prototype и реализует метод Clone
 * В этом примере все поля класса Prototype копируются через конструктор инициализации. 
 *Если среди полей есть указатели, нужно реализовать конструктор копирования, 
 **/

class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {
    }

    /**
     * Метод Clone возвращает указатель на новую реплику ConcreteРrotype1,
     * таким образом, клиент (который вызывает метод clone) 
     *несет ответственность за освобождение  памяти
     */
    Prototype* Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
    }
    Prototype* Clone() const override {
        return new ConcretePrototype2(*this);
    }
};

/**
 * В PrototypeFactory  есть два конкретных прототипа, по одному для каждого конкретного класса
 * Рrototype, поэтому каждый раз, когда нужно создать новый экземпляр, можно использовать существующие
 * и клонировать их.
 */

class PrototypeFactory {
private:
    unordered_map<Type, Prototype*, hash<int>> prototypes_;

public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("ПРОТОТИП_1 ", 50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("ПРОТОТИП_2 ", 60.f);
    }

    /**
     * Освобождение памяти, занятой клонами
     */

    ~PrototypeFactory() {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    /**
     * Необходимор указать желаемый тип прототипа, и 
     и метод создаст объект на основе  указанного типа.
     */
    Prototype* CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory) {
    cout << "Создаем Прототип 1\n";

    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    cout << "\n";

    cout << "Создаем Прототип 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(25);

    delete prototype;
}

int main() {
    setlocale(LC_ALL, "Russian");
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}