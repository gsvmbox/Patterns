/**
 * Паттерн Наблюдатель
 * Назначение: Создаёт механизм подписки, позволяющий одним объектам следить и
 * реагировать на события, происходящие в других объектах.
 *
 *  Субъекта также называют Издателем, а Наблюдателя  называют Подписчиком.
 * Также глаголы «наблюдать», «слушать» или «отслеживать» обычно означают одно и то же.
 */

#include <iostream>
#include <list>
#include <string>
using namespace std;

class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Update(const string& message_from_subject) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

/**
 * Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его
 * изменениях.
 */

class Subject : public ISubject {
private:
    list<IObserver*> list_observer_;
    string message_;
public:
    virtual ~Subject() {
       cout << "Издатель завершил работу.\n";
    }

    /**
     * Методы управления подпиской.
     */
    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
       list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator++)->Update(message_);
           // ++iterator;
        }
    }

    void CreateMessage(std::string message = "Пусто") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
       cout << "Всего " << list_observer_.size() << " подписчика в списке.\n";
    }

    /**
     * Обычно логика подписки – только часть того, что делает Издатель. Издатели
     * часто содержат некоторую важную бизнес-логику, которая запускает метод
     * уведомления всякий раз, когда должно произойти что-то важное (или после
     * этого).
     */
    void SomeBusinessLogic() {
        this->message_ = "Изменение сообщения";
        Notify();
       cout << "Выполнена какая-то работа\n";
    }

};

class Observer : public IObserver {
private:
    string message_from_subject_;
    Subject& subject_;
    static int static_number_;
    int number_;
public:
    Observer(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
       cout << "Это Подписчик \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
       cout << "Подписчик \"" << this->number_ << "\" завершил работу.\n";
    }

    void Update(const string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
       cout << "Подписчик \"" << number_ << "\" удален из спмска.\n";
    }
    void PrintInfo() {
       cout << "Подписчик \"" << this->number_ << "\": получил новое сообщение --> " << this->message_from_subject_ << "\n";
    }

};

int Observer::static_number_ = 0;

void ClientCode() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World!");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("Начинаем работу!");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("Работа сделана, домой!");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ClientCode();
    return 0;
}