#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#pragma warning(disable : 4996)//Для ctime()
using namespace std;

/**
 * Интерфейс Снимка предоставляет способ извлечения метаданных снимка, таких как
 * дата создания или название. Однако он не раскрывает состояние Создателя.
 */
class Memento {
public:
    virtual ~Memento() {}
    virtual string GetName() const = 0;
    virtual string date() const = 0;
    virtual string state() const = 0;
};

/**
 * Конкретный снимок содержит инфраструктуру для хранения состояния Создателя.
 */
class ConcreteMemento : public Memento {
private:
    string state_;
    string date_;

public:
    ConcreteMemento(string state) : state_(state) {
        this->state_ = state;
        time_t now = time(0);
        this->date_ = ctime(&now);
    }
    /**
     * Создатель использует этот метод, когда восстанавливает своё состояние.
     */
    string state() const override {
        return this->state_;
    }
    /**
     * Остальные методы используются Опекуном для отображения метаданных.
     */
    string GetName() const override {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    string date() const override {
        return this->date_;
    }
};

/**
 * Создатель содержит некоторое важное состояние, которое может со временем
 * меняться. Он также объявляет метод сохранения состояния внутри снимка и метод
 * восстановления состояния из него.
 */
class Originator {
    /**
     * @var string Для удобства состояние создателя хранится внутри одной
     * переменной.
     */
private:
    string state_;

    string GenerateRandomString(int length = 10) {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(string state) : state_(state) {
        cout << "Originator: Начальное состояние: " << this->state_ << "\n";
    }
    /**
     * Бизнес-логика Создателя может повлиять на его внутреннее состояние. Поэтому
     * клиент должен выполнить резервное копирование состояния с помощью метода
     * save перед запуском методов бизнес-логики.
     */
    void DoSomething() {
        cout << "Originator:В результате выполнения работы\n";
        this->state_ = this->GenerateRandomString(30);
        cout << "Originator: мое состояние изменилось на: " << this->state_ << "\n";
    }

    /**
     * Сохраняет текущее состояние внутри снимка.
     */
    Memento* Save() {
        return new ConcreteMemento(this->state_);
    }
    /**
     * Восстанавливает состояние Создателя из объекта снимка.
     */
    void Restore(Memento* memento) {
        this->state_ = memento->state();
        cout << "Originator: Мое состояние изменилось на: " << this->state_ << "\n";
    }
};

/**
 * Опекун не зависит от класса Конкретного Снимка. Таким образом, он не имеет
 * доступа к состоянию создателя, хранящемуся внутри снимка. Он работает со
 * всеми снимками через базовый интерфейс Снимка.
 */
class Caretaker {
    /**
     * @var Memento[]
     */
private:
    vector<Memento*> mementos_;

    /**
     * @var Originator
     */
    Originator* originator_;

public:
    Caretaker(Originator* originator) : originator_(originator) {
    }

    ~Caretaker() {
        for (auto m : mementos_) delete m;
    }

    void Backup() {
        cout << "\nCaretaker: Сохранение состояния Originator ...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() {
        if (!this->mementos_.size()) {
            return;
        }
        Memento* memento = this->mementos_.back();
        this->mementos_.pop_back();
        cout << "Caretaker: Восстановление состояния к: " << memento->GetName() << "\n";
        try {
            this->originator_->Restore(memento);
        }
        catch (...) {
            this->Undo();
        }
    }
    void ShowHistory() const {
        cout << "Caretaker: Список Снимков:\n";
        for (Memento* memento : this->mementos_) {
            cout << memento->GetName() << "\n";
        }
    }
};
/**
 * Клиентский код.
 */

void ClientCode() {
    Originator* originator = new Originator("Готов к работе.");
    Caretaker* caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    this_thread::sleep_for(chrono::milliseconds(2000));
    caretaker->Backup();
    originator->DoSomething();
    this_thread::sleep_for(chrono::milliseconds(2000));
    caretaker->Backup();
    originator->DoSomething();
    cout << "\n";
    caretaker->ShowHistory();
    cout << "\nClient: Откат к предыдущему состоянию\n\n";
    caretaker->Undo();
    cout << "\nClient: Ееще откат\n\n";
    caretaker->Undo();
    cout << "\nClient: Ееще откат\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(NULL)));
    ClientCode();
    return 0;
}