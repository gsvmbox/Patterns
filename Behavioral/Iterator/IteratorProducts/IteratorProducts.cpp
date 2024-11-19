#include <iostream>
#include <string>
#include <list>
using namespace std;
//Добавление карточек товаров и работа с ними при помощи итераторов
// 
//класс товаров Products
class Product {
private:
    string product_name;
    int quantity;
public:
    //конструктор инициализации товаров
    Product(string _product_name, int _quantity) {
        product_name = _product_name;
        quantity = _quantity;
    }

    //Вывод информации о товарах
    string toString() {
        return "Наименование товара: " + product_name + ", Количество: " + to_string(quantity);
    }
};

//Контейнер для хрангения карточек товаров и работы с ними при помощи итераторов
template <typename Container>
class Iterator {
private:
    //Указатель на объект карточки товара
    Container* containerData;

    //Объявление итератора
    list<Product>::iterator iter;

public:
    //Конструктор для инициализации итератора устанавливает указатель на первый элемент контейнера
    Iterator(Container* _containerData) {
        containerData = _containerData;

        iter = containerData->cartList.begin();
    }

    //Проверка наличия ссылки на следующий элемент коллекции
    bool hasNext() {
        return (iter != containerData->cartList.end());
    }

    //Переключенеи итератора на следующий элемент, возврат текущего элемента
    list<Product>::iterator next() {
        return iter++;
    }
};

template <typename Container>
class Iterator_2 {
private:
    //Указатель на объект карточки товара
    Container* containerData;

    //Объявление итератора
    list<Product>::iterator iter;

public:
    //Конструктор для инициализации итератора устанавливает указатель на первый элемент контейнера
    Iterator_2(Container* _containerData) {
        containerData = _containerData;

        iter = containerData->cartList.begin();
    }

    //Проверка наличия ссылки на следующий элемент коллекции
    bool hasNext() {
        return (iter != containerData->cartList.end());
    }

    //Переключенеи итератора на следующий элемент, возврат текущего элемента
    list<Product>::iterator next() {
        iter++;
        return iter++;
    }
};

class Cart {
private:
    //Вспомогательный контейнер для хранения карточек товаров
    list<Product> cartList;

public:
    //Метод добавления товара (в список)
    void addProduct(Product a) {
        cartList.push_back(a);
    }

    //Создание итератора
    Iterator<Cart>* createIterator() {
        return new Iterator<Cart>(this);
    }

    Iterator_2<Cart>* createIterator_2() {
        return new Iterator_2<Cart>(this);
    }

    //Чтобы иметь возможность исполдьзовать объекты классов Iterator
    friend class Iterator<Cart>;
    friend class Iterator_2<Cart>;
};

int main() {
    setlocale(LC_ALL, "Russian");
    //Создание карточек
   Cart cartProducts;

    //Создание товаров
    Product a("Мышь", 4), b("Монитор", 5), c("SSD", 8), d("Клавиатура", 2);

    //Добавление товаров
    cartProducts.addProduct(a);
    cartProducts.addProduct(b);
    cartProducts.addProduct(c);
    cartProducts.addProduct(d);

    //Создание итератора для карточек
    Iterator<Cart>* it = cartProducts.createIterator();
    Iterator_2<Cart>* it_2 = cartProducts.createIterator_2();

    //Работа с коллекцией
    cout << "***Базовый Итератор***" << endl;
    while (it->hasNext()) {
        cout << it->next()->toString() << endl;
    }
    //Работа с альтернативным итератором
    cout <<endl<< "***Итератор для четных позиций товара***" << endl;
    while (it_2->hasNext()) {
        cout << it_2->next()->toString() << endl;
    }
    //Работа со встроенным итератором контейнера list
    cout << endl << "***Итератор контейнера list***" << endl;
    list<Product> cards;
    cards.push_back(a);
    cards.push_back(b);
    cards.push_back(c); 
    cards.push_back(d);
    for (auto iter = cards.begin(); iter != cards.end(); iter++)
    {
        cout << iter->toString() << endl;
    }

    return 0;
}
