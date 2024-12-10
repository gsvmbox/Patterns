#include <iostream>
#include <typeinfo> 
#define PI 3.14
using namespace std;
 
class Circle;
class Square;
class Rectangle;

class ShapeVisitor
{
public:
    virtual void visit(Circle* circle) = 0;
    virtual void visit(Square* square) = 0;
    virtual void visit(Rectangle* rectangle) = 0;
};

//Element
//Интерфейс Shape с одним методом accept(), который принимает ShapeVisitor в качестве аргумента
class Shape
{
public:
    virtual void accept(ShapeVisitor* visitor)=0;
};

//Concrete Elements
//Конкретные элементы Circle, Square и Rectangle, которые реализуют интерфейс Shape и переопределяют метод accept
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double radius)
    {
        this->radius = radius;
    }

    double getRadius()
    {
        return radius;
    }

    void accept(ShapeVisitor* visitor) 
    {
        visitor->visit(this);
    }
};

class Square : public Shape
{
private:
    double length;

public:
    Square(double length)
    {
        this->length = length;
    }

    double getLength()
    {
        return length;
    }

    void accept(ShapeVisitor* visitor)
    {
        visitor->visit(this);
    }
};

class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    Rectangle(double length, double width)
    {
        this->length = length;
        this->width = width;
    }

    double getLength()
    {
        return length;
    }

    double getWidth()
    {
        return width;
    }

    void accept(ShapeVisitor* visitor)
    {
        visitor->visit(this);
    }
};

//Visitor
//Интерфейс ShapeVisitor с методами visit(), объявленными для всех классов фигур Square, Circle и Rectangle


//Concrete Visitors
//Конкретные посетители являются AreaVisitor и PerimeterVisitor, 
// которые реализуют интерфейс Посетителя и переопределяют все его методы visit()
class AreaVisitor : public ShapeVisitor
{
private:
    double area;

public:
    void visit(Circle* circle)
    {
        area = PI * pow(circle->getRadius(), 2);
    }

    void visit(Square* square)
    {
        area = 2 * square->getLength();
    }

    void visit(Rectangle* rectangle)
    {
        area = rectangle->getLength() * rectangle->getWidth();
    }

    double get()
    {
        return this->area;
    }
};

class PerimeterVisitor : public ShapeVisitor
{
private:
    double perimeter;

public:
    void visit(Circle* circle)
    {
        perimeter = 2 * PI * circle->getRadius();
    }

    void visit(Square* square)
    {
        perimeter = 4 * square->getLength();
    }

    void visit(Rectangle* rectangle)
    {
        perimeter = 2 * (rectangle->getLength() + rectangle->getWidth());
    }

    double get()
    {
        return this->perimeter;
    }
};

//Клиентская часть , ответственная за создание конкретных объектов visitor и 
// передачу их методу accept() конкретного элемента

int main() { 
    setlocale(LC_ALL, "Russian");
    Shape* shapes[] = { new Circle(10), new Square(10), new Square(5), new Rectangle(10, 4)};
   
    AreaVisitor* areaVisitor = new AreaVisitor();
    PerimeterVisitor* perimeterVisitor = new PerimeterVisitor();

    for (auto shape : shapes)
    {
        shape->accept(areaVisitor);
        double perimeter = areaVisitor->get();
        std::cout << "Площадь фигуры " << typeid(*shape).name() << " равна: " << perimeter << endl;
    }
    
    std::cout << "--------------------------------------------" << std::endl;

     for (auto shape : shapes)
     {
         shape->accept(perimeterVisitor);
         double perimeter = perimeterVisitor->get();
         std::cout << "Периметр фигуы " << typeid(*shape).name()<<" равен: " << perimeter<<endl;
     }

     for (auto shape : shapes) {
         delete shape;
     }
     delete areaVisitor;
     delete perimeterVisitor;

    return 0;
};
