#include<iostream>
using namespace std;
/**
 * Интерфейс Продукта объявляет операции, которые должны выполнять все
 * конкретные продукты.
 */

class Product {
public:
    virtual ~Product() {}
    virtual string Operation() const = 0;
};

/**
 * Конкретные Продукты позволяют получить  различные реализации через общий интерфейс Продукта.
 */
class ConcreteProduct1 : public Product {
public:
    string Operation() const override {
        return "{ConcreteProduct1}";
    }
};
class ConcreteProduct2 : public Product {
public:
    string Operation() const override {
        return "{ConcreteProduct2}";
    }
};

/**
 * Класс Создатель объявляет фабричный метод, который должен возвращать объект
 * класса Продукт. Подклассы Создателя обычно предоставляют реализацию этого
 * метода.
 */

class Creator {
    /**
     * Создатель может также обеспечить реализацию
     * фабричного метода по умолчанию.
     */
public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;
    /**
     * Основная обязанность Создателя НЕ заключается в создании продуктов. 
     *Обычно он реализует некоторую базовую логику пердметной области (бинес-логику), 
     которая основана на объектах Продуктов, возвращаемых
     * фабричным методом. Подклассы могут косвенно изменять эту бизнес-логику,
     * переопределяя фабричный метод и возвращая из него другой тип продукта.
     */

    string SomeOperation() const {
        // Вызываем фабричный метод, чтобы получить объект-продукт.
        Product* product = this->FactoryMethod();
        // Далее, работаем с этим продуктом.
        string result = "Создатель: Работаю с продуктом: " + product->Operation();
        delete product;
        return result;
    }
};

/**
 * Конкретные Создатели переопределяют фабричный метод для того, чтобы изменить
 * тип результирующего продукта.
 */
class ConcreteCreator1 : public Creator {
    /**
     * Сигнатура метода по-прежнему использует тип
     * абстрактного продукта, хотя фактически из метода возвращается конкретный
     * продукт. Таким образом, Создатель может оставаться независимым от
     * конкретных классов продуктов.
     */
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

/**
 * Клиентский код работает с экземпляром конкретного создателя, хотя и через его
 * базовый интерфейс. Пока клиент продолжает работать с создателем через базовый
 * интерфейс, ему можно передать  любой подкласс создателя.
 */
void ClientCode(const Creator& creator) {
    // ...
    cout << "Клиент: Не имею информации о классе Создателя, но могу работать с его продуктами.\n";
    cout << creator.SomeOperation() << endl;
    // ...
}

/**
 * Приложение выбирает тип создателя в зависимости от конфигурации или среды.
 */

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Приложение: Запущен ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    cout << endl;
    cout << "Приложение: Запущен ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}