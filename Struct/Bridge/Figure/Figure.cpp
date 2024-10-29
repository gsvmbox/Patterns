#include <iostream>
#include <Windows.h>
using namespace std;

/**
 * Реализация устанавливает интерфейс для всех классов реализации. Он не должен
 * соответствовать интерфейсу Абстракции. На практике оба интерфейса могут быть
 * совершенно разными. Как правило, интерфейс Реализации предоставляет только
 * примитивные операции, в то время как Абстракция определяет операции более
 * высокого уровня, основанные на этих примитивах.
 */

class Color {
public:
    virtual ~Color() {}
    virtual string SetColor() const = 0;
};

/**
 * Каждая Конкретная Реализация соответствует определённой платформе и реализует
 * интерфейс Реализации с использованием API этой платформы.
 */
class Red : public Color {
public:
    string SetColor() const override {
        HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | 0);
        return "Красного цвета\n";
    }
};
class Blue : public Color {
public:
    string SetColor() const override {
        HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | 0);
        return "Синего цвета\n";
    }
};

/**
 * Абстракция устанавливает интерфейс для «управляющей» части двух иерархий
 * классов. Она содержит ссылку на объект из иерархии Реализации и делегирует
 * ему всю настоящую работу.
 */

class Figure {
    /**
     * @var Implementation
     */
protected:
    Color* implementation_;

public:
    Figure(Color* implementation) : implementation_(implementation) {
    }

    virtual ~Figure() {
    }

    virtual string Operation() const  {
        return "Фигура \n" +
            this->implementation_->SetColor();
    }
};
/**
 * Можно расширить Абстракцию без изменения классов Реализации.
 */
class Circle : public Figure {
public:
    Circle(Color* implementation) : Figure(implementation) {
    }
    string Operation() const override {
        return "Окружность \n" +
            this->implementation_->SetColor();
    }
};

class Triangle : public Figure {
public:
    Triangle(Color* implementation) : Figure(implementation) {
    }
    string Operation() const override {
        return "Треугольник \n" +
            this->implementation_->SetColor();
    }
};

/**
 * За исключением этапа инициализации, когда объект Абстракции связывается с
 * определённым объектом Реализации, клиентский код должен зависеть только от
 * класса Абстракции. Таким образом, клиентский код может поддерживать любую
 * комбинацию абстракции и реализации.
 */
void ClientCode(const Figure& abstraction) {
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
    Color* implementation = new Red;
    Figure* abstraction = new Figure(implementation);
    ClientCode(*abstraction);
    cout << endl;
   // delete implementation;
    //delete abstraction;

    implementation = new Blue;
    abstraction = new Circle(implementation);
    ClientCode(*abstraction);
    cout << endl;
   // delete implementation;
   // delete abstraction;

    implementation = new Red;
    abstraction = new Triangle(implementation);
    ClientCode(*abstraction);
    cout << endl;
   // delete implementation;
   // delete abstraction;

    implementation = new Blue;
    abstraction = new Triangle(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, 15 | 0);

    return 0;
}