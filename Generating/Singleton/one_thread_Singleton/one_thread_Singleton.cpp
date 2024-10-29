#include<iostream>
#include <thread>
using namespace std;

/**
 * Класс Одиночка предоставляет метод `GetInstance`, который ведёт себя как
 * альтернативный конструктор и позволяет клиентам получать один и тот же
 * экземпляр класса при каждом вызове.
 */
class Singleton
{

    /**
     * Конструктор Одиночки всегда должен быть скрытым, чтобы предотвратить
     * создание объекта через оператор new.
     */

protected:
    Singleton(const string value) : value_(value)
    {
    }

    static Singleton* singleton_;

    string value_;

public:

    /**
     * Одиночки не должны быть клонируемыми.
     */
    Singleton(Singleton& other) = delete;
    /**
     * Для Одиночек не должно работать присваивание.
     */
    void operator=(const Singleton&) = delete;
    /**
     * Это статический метод, управляющий доступом к экземпляру одиночки. При
     * первом запуске, он создаёт экземпляр одиночки и помещает его в
     * статическое поле. При последующих запусках, он возвращает клиенту объект,
     * хранящийся в статическом поле.
     */

    static Singleton* GetInstance(const string& value);
    /**
     * Одиночка должен содержать некоторую бизнес-логику, которая
     * может быть выполнена на его экземпляре.
     */
    void SomeBusinessLogic()
    {
        // ...
    }

    string value() const {
        return value_;
    }
};

Singleton* Singleton::singleton_ = nullptr;;

/**
 * Статические методы определяются вне класса.
 */
Singleton* Singleton::GetInstance(const string& value)
{
    /**
     * При первом вызове GetInstance блокируем код создания указателя на Singleton,
     * проверяем, что указатель имеет значение null, затем  устанавливаем значение.
     * Instance = новый Singleton 
     * опасен в том случае, если два потока экземпляра хотят получить доступ одновременно
     */
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo() {
    // Этот код эмулирует медленную инициализацию.
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("ОДИНОЧКА");
    cout << singleton->value() << "\n";
}

void ThreadBar() {
    // Этот код эмулирует медленную инициализацию.
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("ЕЩЕ ОДИНОЧКА :)");
    cout << singleton->value() << "\n";
}


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Если вы видите одинаковые результаты, - значит объект Singleton создан в одном экземпляре (это хорошо).\n" <<
        "Если вы видите разные результаты, - значит создано 2 объекта Singleton (это плохо).\n\n" <<
        "РЕЗУЛЬТАТ:\n";
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}