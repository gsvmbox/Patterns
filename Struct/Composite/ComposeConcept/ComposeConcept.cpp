#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;
/**
 * Базовый класс Компонент объявляет общие операции как для простых, так и для
 * сложных объектов структуры.
 */
class Component {
    /**
     * @var Component
     */
protected:
    Component* parent_;
    /**
     * При необходимости базовый Компонент может объявить интерфейс для установки
     * и получения родителя компонента в древовидной структуре. Он также может
     * предоставить некоторую реализацию по умолчанию для этих методов.
     */
public:
    virtual ~Component() {}
    void SetParent(Component* parent) {
        this->parent_ = parent;
    }
    Component* GetParent() const {
        return this->parent_;
    }
    /**
     * В некоторых случаях целесообразно определить операции управления потомками
     * прямо в базовом классе Компонент. Таким образом,  не нужно будет
     * предоставлять конкретные классы компонентов клиентскому коду, даже во время
     * сборки дерева объектов. Недостаток такого подхода в том, что эти методы
     * будут пустыми для компонентов уровня листа.
     */
    virtual void Add(Component* component) {}
    virtual void Remove(Component* component) {}
    /**
     * Можно предусмотреть метод, который позволит клиентскому коду понять,
     * может ли компонент иметь вложенные объекты.
     */
    virtual bool IsComposite() const {
        return false;
    }
    /**
     * Базовый Компонент может сам реализовать некоторое поведение по умолчанию
     * или поручить это конкретным классам, объявив метод, содержащий поведение
     * абстрактным.
     */
    virtual string Operation() const = 0;
};
/**
 * Класс Лист представляет собой конечные объекты структуры. Лист не может иметь
 * вложенных компонентов.
 *
 * Обычно объекты Листьев выполняют фактическую работу, тогда как объекты
 * Контейнера лишь делегируют работу своим подкомпонентам.
 */
class Leaf : public Component {
public:
    string Operation() const override {
        return "Лист";
    }
};
/**
 * Класс Контейнер содержит сложные компоненты, которые могут иметь вложенные
 * компоненты. Обычно объекты Контейнеры делегируют фактическую работу своим
 * детям, а затем «суммируют» результат.
 */
class Composite : public Component {
    /**
     * @var \SplObjectStorage
     */
protected:
    list<Component*> children_;

public:
    /**
     * Объект контейнера может как добавлять компоненты в свой список вложенных
     * компонентов, так и удалять их, как простые, так и сложные.
     */
    void Add(Component* component) override {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    /**
     * Have in mind that this method removes the pointer to the list but doesn't
     * frees the
     *     memory, you should do it manually or better use smart pointers.
     */
    void Remove(Component* component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override {
        return true;
    }
    /**
     * Контейнер выполняет свою основную логику следующим образом: Он проходит
     * рекурсивно через всех своих детей, собирая и суммируя их результаты.
     * Поскольку потомки контейнера передают эти вызовы своим потомкам и так
     * далее, в результате обходится всё дерево объектов.
     */
    string Operation() const override {
        string result;
        for (const Component* c : children_) {
            if (c == children_.back()) {
                result += c->Operation();
            }
            else {
                result += c->Operation() + "+";
            }
        }
        return "Ветка(" + result + ")";
    }
};
/**
 * Клиентский код работает со всеми компонентами через базовый интерфейс.
 */
void ClientCode(Component* component) {
    // ...
    cout << "РЕЗУЛЬТАТ: " << component->Operation();
    // ...
}

/**
 * Благодаря тому, что операции управления потомками объявлены в базовом классе
 * Компонента, клиентский код может работать как с простыми, так и со сложными
 * компонентами, вне зависимости от их конкретных классов.
 */
void ClientCode2(Component* component1, Component* component2) {
    // ...
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    cout << "РЕЗУЛЬТАТ: " << component1->Operation();
    // ...
}

/**
 * Таким образом, клиентский код может поддерживать простые компоненты-листья...
 */

int main() {
    setlocale(LC_ALL, "Russian");
    Component* simple = new Leaf;
    cout << "Клиент: Добавлен простой компонент:\n";
    ClientCode(simple);
    cout << "\n\n";
    /**
     * ...а также сложные контейнеры.
     */

    Component* tree = new Composite;
    Component* branch1 = new Composite;

    Component* leaf_1 = new Leaf;
    Component* leaf_2 = new Leaf;
    Component* leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component* branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    cout << "Клиент: Добавлен составной объект:\n";
    ClientCode(tree);
    cout << "\n\n";

    cout << "Клиент: Работа с простыми и составными объектами:\n";
    ClientCode2(tree, simple);
    cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}