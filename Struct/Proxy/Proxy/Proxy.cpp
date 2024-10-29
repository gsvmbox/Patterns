#include <iostream>
#include <chrono>
#include <thread>
#pragma warning(disable : 4996)

using namespace std;

/**
 * Интерфейс Субъекта объявляет общие операции как для Реального Субъекта, так и
 * для Заместителя. Пока клиент работает с Реальным Субъектом, используя этот
 * интерфейс, ему можно передать  заместителя вместо реального субъекта.
 */
class Subject {
public:
    virtual void Request() const = 0;
};
/**
 * Реальный Субъект реализует логику предметной области. 
 */
class RealSubject : public Subject {
public:
    void Request() const override {
        cout << "RealSubject: Получен запрос.\n";
    }
};
/**
 * Интерфейс Заместителя идентичен интерфейсу Реального Субъекта.
 */
class Proxy : public Subject {
    /**
     * @var RealSubject
     */
private:
    RealSubject* real_subject_;
   
    bool CheckAccess() const {
        // Например проверка прав доступа.
        cout << "Proxy: Проверка прав доступа к сервису.\n";
        return true;
    }
    void LogAccess() const {//логирование обращений клиентов
        time_t now = time(0);
        char* dt = ctime(&now);// convert now to string form
        cout << "Proxy: Регистрация времени обращения к сервису: " << dt << endl;
    }

    /**
     * Заместитель хранит ссылку на объект класса РеальныйСубъект. Клиент может
     * либо лениво загрузить его, либо передать Заместителю.
     */
public:
    Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {
    }

    ~Proxy() {
        delete real_subject_;
    }
    /**
     * Наиболее распространёнными областями применения паттерна Заместитель
     * являются ленивая загрузка, кэширование, контроль доступа, ведение журнала и
     * т.д. Заместитель может выполнить одну из этих задач, а затем, в зависимости
     * от результата, передать выполнение одноимённому методу в связанном объекте
     * класса Реального Субъект.
     */
    
    void Request() const override {
        if (this->CheckAccess()) {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

/**
 * Клиентский код должен работать со всеми объектами (как с реальными, так и
 * заместителями) через интерфейс Субъекта, чтобы поддерживать как реальные
 * субъекты, так и заместителей. В реальной жизни, однако, клиенты в основном
 * работают с реальными субъектами напрямую. В этом случае, для более простой
 * реализации паттерна, можно расширить заместителя из класса реального
 * субъекта.
 */
void ClientCode_1(const Subject& subject) {
    // ...
    this_thread::sleep_for(chrono::milliseconds(1000));
    subject.Request();
    // ...
}

void ClientCode_2(const Subject& subject) {
    // ...
    this_thread::sleep_for(chrono::milliseconds(2000));
    subject.Request();
    // ...
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Client: Выполненение клиентского кода на реальном сервисе:\n";
    RealSubject* real_subject = new RealSubject;
    ClientCode_1(*real_subject);
    cout << "\n";
    cout << "Client: Выполнение клиентсокго кода чере Заместителя (Прокси):\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode_1(*proxy);
    cout << "Client: Выполнение клиентсокго кода чере Заместителя (Прокси):\n";
    ClientCode_2(*proxy);
   
    delete real_subject;
    delete proxy;
  
    return 0;
}